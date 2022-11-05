#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <functional>
#include <optional>
#include <unistd.h>

#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <libproc.h>

#include "variables.hpp"
#include "parameters.hpp"
#include "utilities.hpp"

#include "process/base_process.hpp"
#include "process/roblox_process.hpp"
#include "process/roblox_player.hpp"
#include "process/roblox_studio.hpp"

#define VERSION_STRING "2.0.1"
