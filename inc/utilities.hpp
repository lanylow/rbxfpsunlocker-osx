#pragma once

namespace utilities {
  bool compare(const std::uint8_t* data, const std::uint8_t* signature, std::uint32_t size);
  mach_vm_address_t find_signature(void* start, void* end, const char* signature, std::uint32_t size);
  void remove_roblox_signature();
}
