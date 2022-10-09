#pragma once

namespace process {
  struct module_info {
    mach_vm_address_t load_address{ 0 };
    off_t size{ 0 };
  };

  class base_process {
  private:
    pid_t process_id{ 0 };
    mach_port_t task{ 0 };

  public:
    static void for_each_process(const std::function<void(char*, pid_t)>& callback);
    static void list_processes();
    static base_process get_process(pid_t id);

    explicit base_process(pid_t process_id) : process_id(process_id) {
      if (task_for_pid(mach_task_self(), process_id, &task) != KERN_SUCCESS) throw std::runtime_error("base_process constructor failed.");
    }

    std::optional<process::module_info> get_module(const char* name) const;
    [[nodiscard]] mach_msg_type_number_t get_thread_count() const;
    [[nodiscard]] std::uint8_t* read_data(mach_vm_address_t address, off_t size) const;

    template <typename T>
    T read_memory(mach_vm_address_t address, off_t size = sizeof(T)) {
      T buff{ };
      vm_offset_t data;
      mach_msg_type_number_t sz;

      if (vm_read(task, address, size, &data, &sz) == KERN_SUCCESS) {
        buff = *reinterpret_cast<T*>(data);
        vm_deallocate(current_task(), data, sz);
      }

      return buff;
    }

    template <typename T>
    void write_memory(mach_vm_address_t address, T data) {
      vm_write(task, address, reinterpret_cast<vm_offset_t>(&data), sizeof(data));
    }
  };
}