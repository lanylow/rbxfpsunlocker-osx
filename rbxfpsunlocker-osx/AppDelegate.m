//
//  AppDelegate.m
//  rbxfpsunlocker-osx
//
//  Created by Seizure Salad and lanylow on 1/24/22.
//

//i am so sorry for anyone who has to read this

#import "AppDelegate.h"
#import "FPSUnlockerWrapper.h"

@interface OnlyIntegerValueFormatter : NSNumberFormatter

@end

@implementation OnlyIntegerValueFormatter

- (BOOL)isPartialStringValid:(NSString*)partialString newEditingString:(NSString**)newString errorDescription:(NSString**)error
{
    if([partialString length] == 0) {
        return YES;
    }

    NSScanner* scanner = [NSScanner scannerWithString:partialString];

    if(!([scanner scanInt:0] && [scanner isAtEnd])) {
        NSBeep();
        return NO;
    }

    return YES;
}

@end

@interface AppDelegate ()

@property (strong) IBOutlet NSMenu *menu_bar_item;
@property (strong) NSStatusItem *status_item;
@property bool roblox_player_toggled;
@property bool roblox_studio_toggled; //does nothing yet

@end

@implementation AppDelegate

double cap = 10000.00;

void create_notification(NSString* title, NSString* message, NSAlertStyle alert_style) {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:title];
    [alert setInformativeText:message];
    [alert setAlertStyle:alert_style];
    [alert addButtonWithTitle:@"Ok"];
    [alert addButtonWithTitle:@"Go to GitHub"];
    switch ([alert runModal]) {
        case NSAlertFirstButtonReturn:
            break;
        case NSAlertSecondButtonReturn:
            [[NSWorkspace sharedWorkspace]openURL:[NSURL URLWithString:@"https://github.com/lanylow/rbxfpsunlocker-osx"]];
            break;
        default:
            break;
    }
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    //exit if application is not root in order to use memory editing functions
    if(getuid() != 0){
        //TODO: replace AppleScript with something better
        NSString *currentpath = [[[[NSBundle mainBundle] bundlePath] stringByDeletingPathExtension] stringByDeletingLastPathComponent];
        NSString *contents = [NSString stringWithFormat:@"%@%@/%@", @"#!/usr/bin/osascript\ndo shell script \"sudo \\\"", currentpath, @"rbxfpsunlocker-osx.app/Contents/MacOS/rbxfpsunlocker-osx\\\"\" with administrator privileges"];
        NSLog(@"%@", contents);

        [[NSFileManager defaultManager] createFileAtPath:@"/tmp/elevate.command" contents:[contents dataUsingEncoding:NSUTF8StringEncoding] attributes:nil];

        chmod("/tmp/elevate.command", 0777);

        NSTask *task = [[NSTask alloc] init];
        task.launchPath = @"/tmp/elevate.command";

        [task launch];

        [[NSApplication sharedApplication] terminate:nil];
    }
    
    //set up the status item; couldn't decide whether to use bracket or dot notation lol
    self.status_item = [[NSStatusBar systemStatusBar] statusItemWithLength: -1];
    NSImage *status_item_image = [NSImage imageNamed:@"AppIcon"];
    status_item_image.size = NSMakeSize(18.0, 18.0);
    [self.menu_bar_item setAutoenablesItems:true];
    [self.status_item setMenu:self.menu_bar_item];
    self.status_item.button.image = status_item_image;
    self.status_item.button.toolTip = @"Roblox FPS Unlocker";
    self.roblox_player_toggled = true;
    self.roblox_studio_toggled = true;
    [self.status_item setVisible:true];
    
    [NSApp setActivationPolicy: NSApplicationActivationPolicyAccessory]; // bye bye dock item!
    
    [[[NSWorkspace sharedWorkspace] notificationCenter] addObserverForName:NSWorkspaceDidLaunchApplicationNotification object:nil queue:[NSOperationQueue currentQueue] usingBlock:^(NSNotification *note) {
        NSRunningApplication *frontmostApplication = [[note userInfo] objectForKey:NSWorkspaceApplicationKey];
        if ([[frontmostApplication localizedName]  isEqual: @"Roblox"]) {
            fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
            [fpsunlocker init_roblox: cap :self.roblox_player_toggled];
        }
    }];
    
    //(should) close window after 5 seconds
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^(void){
        [[[NSApplication sharedApplication] mainWindow] close];
    });
}

- (IBAction)menu_lock_unlock:(id)sender {
    NSMenuItem *player_menu_item = (NSMenuItem *)sender;
    if(self.roblox_player_toggled) {
        player_menu_item.title = @"Unlock Roblox Player";
    }
    else {
        player_menu_item.title = @"Lock Roblox Player";
    }
}

- (IBAction)menu_studio_lock_unlock:(id)sender { //does nothing yet
    NSMenuItem *studio_menu_item = (NSMenuItem *)sender;
    if(self.roblox_studio_toggled) {
        studio_menu_item.title = @"Unlock Roblox Studio";
    }
    else {
        studio_menu_item.title = @"Lock Roblox Studio";
    }
}

- (IBAction)menu_visit_github:(id)sender {
    [[NSWorkspace sharedWorkspace]openURL:[NSURL URLWithString:@"https://github.com/lanylow/rbxfpsunlocker-osx"]];
}

- (IBAction)menu_exit:(id)sender {
    [[NSApplication sharedApplication] terminate:nil];
}

//bruh i can't put numbers in the names of the functions

- (IBAction)custom_fps_cap:(id)sender {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:@"Custom FPS Cap"];
    [alert setInformativeText:@"Enter your desired FPS cap"];
    [alert setAlertStyle:NSAlertStyleInformational];
    [alert addButtonWithTitle:@"Ok"];
    [alert addButtonWithTitle:@"Cancel"];
    
    NSTextField *cap_text = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 200, 24)];
    [alert setAccessoryView:cap_text];
    
    NSModalResponse response = [alert runModal];
    switch (response) {
        case NSAlertFirstButtonReturn: {
            [cap_text validateEditing];
            NSNumberFormatter *number_formatter = [[NSNumberFormatter alloc] init];
            [number_formatter setLocale:[NSLocale currentLocale]];
            [number_formatter setNumberStyle:NSNumberFormatterDecimalStyle];
            
            double fps_cap = [[number_formatter numberFromString:[cap_text stringValue]] doubleValue];
            
            if (fps_cap <= 0.0) {
                create_notification(@"Error!", @"Please enter a valid number!", NSAlertStyleCritical);
            }
            else {
                cap = fps_cap;
                fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
                [fpsunlocker set_fps_cap:cap];
                create_notification(@"Success!", [NSString stringWithFormat:@"%@%f", @"Successfully set FPS cap to " , fps_cap], NSAlertStyleInformational);
            }
            
            break;
        }
        case NSAlertSecondButtonReturn:
            break;
        default:
            break;
    }
    
}

//TODO: fix this lol
- (IBAction)no_fps_cap:(id)sender {
    cap = 10000.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)thirty_fps:(id)sender {
    cap = 30;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)sixty_fps:(id)sender {
    cap = 60;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)seventy_five_fps:(id)sender {
    cap = 75.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)one_twenty_fps:(id)sender {
    cap = 120.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)one_fourty_four_fps:(id)sender {
    cap = 144.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)one_sixty_five_fps:(id)sender {
    cap = 165.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)two_fourty_fps:(id)sender {
    cap = 240.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (IBAction)three_sixty_fps:(id)sender {
    cap = 360.00;
    fps_unlocker_wrapper *fpsunlocker = [[fps_unlocker_wrapper alloc] init];
    [fpsunlocker set_fps_cap:cap];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end
