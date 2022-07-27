//
//  FPSUnlocker_Wrapper.h
//  rbxfpsunlocker-osx
//
//  Created by Seizure Salad and lanylow on 1/31/22.
//

#import <Foundation/Foundation.h>

@interface fps_unlocker_wrapper : NSObject
@end

@interface fps_unlocker_wrapper ()
- (void) set_fps_cap:(double)cap;
- (void) init_roblox:(double)cap :(bool)unlock;
- (bool) roblox_running;
@end
