//
//  FPSUnlocker.hpp
//  rbxfpsunlocker-osx
//
//  Created by Seizure Salad and lanylow on 1/31/22.
//

#ifndef FPSUnlocker_hpp
#define FPSUnlocker_hpp

#include <stdio.h>

class fps_unlocker {
public:
    void set_fps_cap(double cap);
    void init_roblox(double cap, bool unlock);
    bool roblox_running();
};

#endif /* FPSUnlocker_hpp */
