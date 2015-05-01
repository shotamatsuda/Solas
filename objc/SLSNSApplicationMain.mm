//
//  SLSNSApplicationMain.mm
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//
//  All information contained herein is, and remains the property of takram
//  design engineering and its suppliers, if any. The intellectual and
//  technical concepts contained herein are proprietary to takram design
//  engineering and its suppliers and may be covered by U.S. and Foreign
//  Patents, patents in process, and are protected by trade secret or copyright
//  law. Dissemination of this information or reproduction of this material is
//  strictly forbidden unless prior written permission is obtained from takram
//  design engineering.
//

#import "SLSApplicationMain.h"

#import <AppKit/AppKit.h>

#import "SLSNSApplicationDelegate.h"
#import "SLSNSBundle+Bundle.h"

int SLSApplicationMain(int argc, char **argv) {
  @autoreleasepool {
    NSApplication *app = [NSApplication sharedApplication];
    NSBundle *bundle = [NSBundle solasBundle];
    [bundle loadNibNamed:@"SLSNSApplication" owner:app topLevelObjects:NULL];
    [app run];
  }
  return EXIT_SUCCESS;
}
