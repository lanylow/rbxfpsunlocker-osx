#pragma once

namespace process {
  class roblox_studio : public process::roblox_process {
  public:
    explicit roblox_studio() : process::roblox_process("RobloxStudio") {
      auto module = get_module("/RobloxStudio");
      if (!module.has_value()) throw std::runtime_error("Couldn't get the main module");
      main_module = module.value();
    }
  };
}