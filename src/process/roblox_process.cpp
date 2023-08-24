#include <main.hpp>

pid_t process::roblox_process::get_process_id(const char* process_name) {
  pid_t process_id = 0;

  process::base_process::for_each_process([&](char* name, pid_t id) {
    if (std::strcmp(name, process_name) == 0)
      if (process::base_process::get_process(id).get_thread_count() > 10)
        process_id = id;
  });

  if (!process_id) throw std::runtime_error("Roblox is not running.");
  return process_id;
}

mach_vm_address_t process::roblox_process::find_task_scheduler_address(std::uint8_t* data, off_t size) {
  auto address = utilities::find_signature(data, data + size, "\xBF\x48\x03\x00\x00\xE8\x00\x00\x00\x00\x48\x89\xC3\x48\x89\xC7\xE8\x00\x00\x00\x00\x48\x89\x1D\x00\x00\x00\x00", 28);
  if (!address) throw std::runtime_error("Couldn't find the task scheduler signature.\n");
  return (address + *reinterpret_cast<std::uint32_t*>(address + 24) + 28) - reinterpret_cast<mach_vm_address_t>(data);
}

void process::roblox_process::set_fps_cap(int cap) {
  auto task_scheduler = read_memory<mach_vm_address_t>(get_task_scheduler());
  write_memory<double>(task_scheduler + 0x138, static_cast<double>(1.0 / cap));
}

mach_vm_address_t process::roblox_process::get_task_scheduler() {
  auto data = read_data(main_module.load_address, main_module.size);
  auto address = find_task_scheduler_address(data, main_module.size);
  vm_deallocate(current_task(), reinterpret_cast<vm_address_t>(data), main_module.size);
  return main_module.load_address + address;
}
