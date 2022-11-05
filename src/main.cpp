#include <main.hpp>

int main(int argc, char** argv) {
  try {
    if (getuid() != 0) throw std::runtime_error("This application has to be ran as root.");

    parameters::parse(argc, argv);

    process::roblox_process* process;
    if (variables::unlock_studio) process = new process::roblox_studio();
    else process = new process::roblox_player();

    process->set_fps_cap(variables::fps_cap);
  }
  catch (std::exception& exception) {
    std::printf("\x1b[91mexception: %s\x1b[0m\n", exception.what());
  }
}
