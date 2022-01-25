#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <stdexcept>

#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <libproc.h>

//Created by lanylow and Seizure Salad

struct {
  pid_t id = 0;
  mach_port_t task = 0;
  mach_vm_address_t load_address = 0;
  off_t size = 0;
} roblox;

pid_t get_roblox_process_id() {
  auto proc_cnt = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);

  pid_t ids[proc_cnt];
  bzero(ids, sizeof(ids));
  proc_listpids(PROC_ALL_PIDS, 0, ids, (int)sizeof(ids));

  for (auto i = proc_cnt; i > 0; --i) {
    if (ids[i] == 0) continue;

    char path[PROC_PIDPATHINFO_MAXSIZE];
    bzero(path, sizeof(path));
    proc_pidpath(ids[i], path, sizeof(path));

    char name[256];
    bzero(name, sizeof(name));

    auto pos = strlen(path);
    while (pos >= 0 && path[pos] != '/') pos--;

    strcpy(name, path + pos + 1);
    if (strcmp(name, "RobloxPlayer") == 0) return ids[i];
  }

  return 0;
}

bool init_roblox_struct() {
  roblox.id = get_roblox_process_id();
  if (!roblox.id) return false;

  task_for_pid(mach_task_self(), roblox.id, &roblox.task);
  if (!roblox.task) return false;

  struct task_dyld_info dyld_info;
  mach_msg_type_number_t task_info_cnt = TASK_DYLD_INFO_COUNT;
  mach_vm_address_t address = 0;
  if (task_info(roblox.task, TASK_DYLD_INFO, (task_info_t)&dyld_info, &task_info_cnt) == KERN_SUCCESS) address = dyld_info.all_image_info_addr;

  mach_msg_type_number_t size = sizeof(struct dyld_all_image_infos);
  vm_offset_t read_buffer;
  if (vm_read(roblox.task, address, size, &read_buffer, &size) != KERN_SUCCESS) return false;
  auto image_infos = (struct dyld_all_image_infos *)read_buffer;

  size = 24 * image_infos->infoArrayCount;
  if (vm_read(roblox.task, (mach_vm_address_t)image_infos->infoArray, size, &read_buffer, &size) != KERN_SUCCESS) return false;
  auto info = (struct dyld_image_info*)read_buffer;
  
  for (auto i = 0; i < image_infos->infoArrayCount; i++) {
    size = 1024;
    vm_read(roblox.task, (mach_vm_address_t)info[i].imageFilePath, size, &read_buffer, &size);
    auto path = (char*)read_buffer;

    if (!path) continue;
    if (strstr(path, "/RobloxPlayer") == NULL) continue;

    struct stat st;
    stat(path, &st);

    roblox.load_address = (mach_vm_address_t)info[i].imageLoadAddress;
    roblox.size = st.st_size;
  }

  if (!roblox.load_address || !roblox.size) return false;
  return true;
}

template <typename T>
T read_memory(mach_vm_address_t address, off_t size = sizeof(T)) {
  T buff{};
  vm_offset_t data;
  mach_msg_type_number_t sz;

  if (vm_read(roblox.task, (vm_address_t)address, size, &data, &sz) == KERN_SUCCESS) {
    buff = (T)(*(T*)(data));
    vm_deallocate(current_task(), data, sz);
  }

  return buff;
}

uint8_t* read_data(mach_vm_address_t address, off_t size) {
  vm_offset_t data;
  mach_msg_type_number_t sz;

  if (vm_read(roblox.task, (vm_address_t)address, size, &data, &sz) != KERN_SUCCESS) return nullptr;

  return (uint8_t*)data;
}

template <typename T>
void write_memory(mach_vm_address_t address, T data) {
  vm_write(roblox.task, (vm_address_t)address, (vm_offset_t)&data, sizeof(data));
}

bool compare(uint8_t* data, uint8_t* sig, uint32_t size) {
  for (auto i = 0; i < size; i++)
    if (data[i] != sig[i] && sig[i] != 0x00)
      return false;
  return true;
}

uint8_t* find_sig(void* start, void* end, const char* sig, uint32_t size) {
  for (auto i = (uint8_t*)start; i < (uint8_t*)end - size; i++)
    if (compare(i, (uint8_t*)sig, size))
      return i;
  return 0;
}

mach_vm_address_t find_task_scheduler() {
  auto data = read_data(roblox.load_address, roblox.size);
  auto address = (mach_vm_address_t)find_sig(data, data + roblox.size, "\xBF\xE8\x02\x00\x00\xE8\x00\x00\x00\x00\x48\x89\xC3\x48\x89\xC7\xE8\x00\x00\x00\x00\x48\x89\x1D\x00\x00\x00\x00", 28);

  if (!address) throw std::runtime_error("Couldn't find the task scheduler pattern.\nRoblox updates can cause this.\nCheck the GitHub for any new updates.");

  mach_vm_address_t res = roblox.load_address + ((address + *(uint32_t*)(address + 24) + 28) - (mach_vm_address_t)data);
  vm_deallocate(current_task(), (vm_offset_t)data, roblox.size);

  return res;
}

void set_fps_cap(double cap){
  auto task_sheduler = read_memory<mach_vm_address_t>(find_task_scheduler());
  write_memory<double>(task_sheduler + 0x130, (double)(1.0 / cap));

  printf("FPS cap successfully set to %f\n", cap);
}

int main(int argc, const char * argv[]) {
  int cap;

  system("clear");

  if (getuid() != 0) throw std::runtime_error("This application has to be ran as root.\nUsage: sudo ./rbxfpsunlocker <cap>");

  // Checking if framerate was passed in via argument.
  if (*++argv != NULL) {
    cap = strtoul(*argv, NULL, 0);

    // If supplied argument was not an interger cap will be set to 120.
    if(cap == 0) {
      cap = 120;
    }
  } else cap = 120;
  
  if (!init_roblox_struct()) throw std::runtime_error("Failed to get Roblox process info.\nMake sure Roblox is open and try again.");
  
  printf("macOS Roblox FPS Unlocker\nCurrently in-development, use at your own risk.\nCreated by lanylow and Seizure Salad.");
  
  set_fps_cap(cap);

  return 0;
}