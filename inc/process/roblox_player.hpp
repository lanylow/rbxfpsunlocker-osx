#pragma once

namespace process {
  class roblox_player : public process::roblox_process {
  public:
    explicit roblox_player() : process::roblox_process("RobloxPlayer", "/RobloxPlayer") { }
  };
}