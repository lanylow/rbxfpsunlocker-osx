#pragma once

namespace process {
  class roblox_studio : public process::roblox_process {
  public:
    explicit roblox_studio() : process::roblox_process("RobloxStudio", "/RobloxStudio") { }
  };
}