#include <main.hpp>

void process::base_process::for_each_process(const std::function<void(char*, pid_t)>& callback) {
  auto process_count = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);

  pid_t ids[process_count];
  bzero(ids, sizeof(ids));
  proc_listpids(PROC_ALL_PIDS, 0, ids, static_cast<int>(sizeof(ids)));

  for (auto i = 0; i < process_count; i++) {
    if (ids[i] == 0) continue;

    char path[PROC_PIDPATHINFO_MAXSIZE];
    bzero(path, sizeof(path));
    proc_pidpath(ids[i], path, sizeof(path));

    char name[MAXPATHLEN];
    bzero(name, sizeof(name));

    auto pos = std::strlen(path);
    while (pos > 0 && path[pos] != '/') pos--;

    std::strcpy(name, path + pos + 1);
    callback(name, ids[i]);
  }
}

void process::base_process::list_processes() {
  process::base_process::for_each_process([](char* name, pid_t id) {
    std::printf("%s: id %d\n", name, id);
  });
}

process::base_process process::base_process::get_process(pid_t id) {
  return process::base_process(id);
}

std::optional<process::module_info> process::base_process::get_module(const char* name) const {
  struct task_dyld_info dyld_info{ };
  mach_msg_type_number_t task_info_count = TASK_DYLD_INFO_COUNT;
  mach_vm_address_t address = 0;
  if (task_info(task, TASK_DYLD_INFO, reinterpret_cast<task_info_t>(&dyld_info), &task_info_count) == KERN_SUCCESS) address = dyld_info.all_image_info_addr;

  mach_msg_type_number_t size = sizeof(struct dyld_all_image_infos);
  vm_offset_t read_buffer;
  if (vm_read(task, address, size, &read_buffer, &size) != KERN_SUCCESS) return std::nullopt;
  auto image_infos = reinterpret_cast<struct dyld_all_image_infos*>(read_buffer);

  size = 24 * image_infos->infoArrayCount;
  if (vm_read(task, reinterpret_cast<mach_vm_address_t>(image_infos->infoArray), size, &read_buffer, &size) != KERN_SUCCESS) return std::nullopt;
  auto info = reinterpret_cast<struct dyld_image_info*>(read_buffer);

  for (auto i = 0; i < image_infos->infoArrayCount; i++) {
    size = 1024;
    vm_read(task, reinterpret_cast<mach_vm_address_t>(info[i].imageFilePath), size, &read_buffer, &size);
    auto path = reinterpret_cast<char*>(read_buffer);

    if (!path) continue;
    if (std::strstr(path, name) == nullptr) continue;

    struct stat st{};
    stat(path, &st);

    return std::make_optional(process::module_info{ reinterpret_cast<mach_vm_address_t>(info[i].imageLoadAddress), st.st_size });
  }

  return std::nullopt;
}

mach_msg_type_number_t process::base_process::get_thread_count() const {
  thread_array_t thread_array;
  mach_msg_type_number_t thread_count;

  auto result = task_threads(task, &thread_array, &thread_count);
  if (result != KERN_SUCCESS) throw std::runtime_error("Couldn't get base_process's threads.\n");

  result = vm_deallocate(mach_task_self(), reinterpret_cast<vm_address_t>(thread_array), thread_count * sizeof(*thread_array));
  if (result != KERN_SUCCESS) throw std::runtime_error("Couldn't deallocate thread array.\n");

  return thread_count;
}

std::uint8_t* process::base_process::read_data(mach_vm_address_t address, off_t size) const {
  vm_offset_t data;
  mach_msg_type_number_t sz;
  if (vm_read(task, address, size, &data, &sz) != KERN_SUCCESS) throw std::runtime_error("Couldn't read data.");

  return reinterpret_cast<std::uint8_t*>(data);
}