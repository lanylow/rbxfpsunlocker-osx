//
//  FPSUnlocker_Wrapper.m
//  rbxfpsunlocker-osx
//
//  Created by Seizure Salad and lanylow on 1/31/22.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "FPSUnlockerWrapper.h"
#import "FPSUnlocker.hpp"

#include <stdexcept>

@implementation fps_unlocker_wrapper : NSObject

fps_unlocker fpsunlocker;

void create_notification(NSString* title, NSString* message, NSAlertStyle alert_style) {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:title];
    [alert setInformativeText:message];
    [alert setAlertStyle:alert_style];
    [alert addButtonWithTitle:@"Ok"];
    [alert addButtonWithTitle:@"Go to GitHub"];
    NSModalResponse response = [alert runModal];
    switch (response) {
        case NSAlertFirstButtonReturn:
            break;
        case NSAlertSecondButtonReturn:
            [[NSWorkspace sharedWorkspace]openURL:[NSURL URLWithString:@"https://github.com/lanylow/rbxfpsunlocker-osx"]];
            break;
        default:
            break;
    }
}

- (void) set_fps_cap:(double)cap {
    try {
        fpsunlocker.set_fps_cap(cap);
    } catch (const std::exception& e) {
        create_notification(@"Error!", [NSString stringWithUTF8String:e.what()], NSAlertStyleCritical);
    }
}

- (void) init_roblox:(double)cap :(bool)unlock_fps {
    try {
        fpsunlocker.init_roblox(cap, unlock_fps);
    } catch (const std::exception& e) {
        create_notification(@"Error!", [NSString stringWithUTF8String:e.what()], NSAlertStyleCritical);
    }
}

- (bool) roblox_running {
    return fpsunlocker.roblox_running();
}

@end
