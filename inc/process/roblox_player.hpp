#pragma once

namespace process {
  class roblox_player : public process::roblox_process {
  public:
    explicit roblox_player() : process::roblox_process("RobloxPlayer") {
      auto module = get_module("/RobloxPlayer");
      if (!module.has_value()) throw std::runtime_error("Couldn't get the main module");
      main_module = module.value();
    }
  };
}