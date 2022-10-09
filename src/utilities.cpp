#include <main.hpp>

bool utilities::compare(const std::uint8_t* data, const std::uint8_t* signature, std::uint32_t size) {
  for (auto i = 0; i < size; i++)
    if (data[i] != signature[i] && signature[i] != 0x00)
      return false;

  return true;
}

mach_vm_address_t utilities::find_signature(void* start, void* end, const char* signature, std::uint32_t size) {
  for (auto i = reinterpret_cast<std::uint8_t*>(start); i < reinterpret_cast<std::uint8_t*>(end) - size; i++)
    if (compare(i, (std::uint8_t*)signature, size))
      return reinterpret_cast<mach_vm_address_t>(i);

  return 0;
}