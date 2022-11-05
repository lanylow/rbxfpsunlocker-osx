#include <main.hpp>

void parameters::print_usage() {
  std::printf("macOS Roblox FPS Unlocker.\n");
  std::printf("Version v%s\n", VERSION_STRING);
  std::printf("\n");
  std::printf("sudo ./rbxfpsunlocker_osx <cap> [-s] [-r]\n");
  std::printf("\n");
  std::printf("<cap>    New FPS cap to be set in Roblox.\n");
  std::printf("         Use '0' to set the FPS cap to unlimited.\n");
  std::printf("\n");
  std::printf("Following options are optional.\n");
  std::printf(" -s      Unlocks FPS in Roblox Studio.\n");
  std::printf(" -r      Remove Roblox signatures.\n");
  std::printf("\n");
}

void parameters::parse(int argc, char** argv) {
  if (argc == 1 || (argc == 2 && std::strcmp(argv[1], "-h") == 0)) {
    parameters::print_usage();
    exit(EXIT_SUCCESS);
  }

  auto argument_pointer = 0;

  auto fps_cap = static_cast<int>(std::strtol(argv[++argument_pointer], nullptr, 0));
  variables::fps_cap = (fps_cap == 0 ? 10000 : fps_cap);

  while (++argument_pointer < argc) {
    auto current_argument = argv[argument_pointer];
    auto current_length = std::strlen(current_argument);
    if (current_length != 2) throw std::runtime_error("Invalid parameters.");

    switch (current_argument[1]) {
      case 's': variables::unlock_studio = true; break;
      case 'r': utilities::remove_roblox_signature(); break;
    }
  }
}
