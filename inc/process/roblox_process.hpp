#pragma once

namespace process {
  class roblox_process : public process::base_process {
  protected:
    process::module_info main_module{0, 0 };

  public:
    static pid_t get_process_id(const char* process_name);

    explicit roblox_process(const char* process_name, const char* module_name) : process::base_process(get_process_id(process_name)) {
      auto module = get_module(module_name);
      if (!module.has_value()) throw std::runtime_error("Couldn't get the main module");
      main_module = module.value();
    }

    virtual mach_vm_address_t find_task_scheduler_address(std::uint8_t* data, off_t size);
    virtual void set_fps_cap(int cap);

    mach_vm_address_t get_task_scheduler();
  };
}