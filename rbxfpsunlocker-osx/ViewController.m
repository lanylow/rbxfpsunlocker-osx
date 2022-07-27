//
//  ViewController.m
//  rbxfpsunlocker-osx
//
//  Created by Seizure Salad and lanylow on 1/24/22.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}

- (IBAction)exit_button_clicked:(id)sender {
    [[NSApplication sharedApplication] terminate:nil];
}


- (IBAction)github_button_clicked:(id)sender {
    [[NSWorkspace sharedWorkspace]openURL:[NSURL URLWithString:@"https://github.com/lanylow/rbxfpsunlocker-osx"]];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
