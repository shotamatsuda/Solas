//
//  SLSNSApplicationDelegate.mm
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

#import "SLSNSApplicationDelegate.h"

#import "SLSRunner.h"
#import "SLSNSViewController.h"
#import "SLSNSWindowController.h"

#include "solas/app/runner_factory.h"

@interface SLSNSApplicationDelegate () {
 @private
  NSMutableArray *_windowControllers;
}

#pragma mark Window Notifications

- (void)windowWillClose:(NSNotification *)notification;

@end

@implementation SLSNSApplicationDelegate

- (instancetype)init {
  self = [super init];
  if (self) {
    _windowControllers = [[NSMutableArray alloc] init];
  }
  return self;
}

- (void)dealloc {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  [self newWindow:self];
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
  if (!_windowControllers.count) {
    [self newWindow:self];
  }
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication *)sender {
  const auto& options = solas::app::RunnerFactory::Shared().options();
  return !options.multiple_windows();
}

#pragma mark Window Controllers

- (NSArray *)windowControllers {
  return [NSArray arrayWithArray:_windowControllers];
}

#pragma mark Window Notifications

- (void)windowWillClose:(NSNotification *)notification {
  const auto& options = solas::app::RunnerFactory::Shared().options();
  if (options.multiple_windows()) {
    NSWindow *window = notification.object;
    [[NSNotificationCenter defaultCenter]
        removeObserver:self
                  name:NSWindowWillCloseNotification
                object:window];
    [_windowControllers removeObject:window.windowController];
  }
}

#pragma mark Received Actions

- (IBAction)newWindow:(id)sender {
  SLSRunner *runner = [[SLSRunner alloc]
      initWithRunnable:solas::app::RunnerFactory::Shared().create()];
  SLSNSViewController *viewController =
      [[SLSNSViewController alloc] initWithRunner:runner];
  SLSNSWindowController *windowController =
      [[SLSNSWindowController alloc] initWithViewController:viewController];
  [[NSNotificationCenter defaultCenter]
      addObserver:self
         selector:@selector(windowWillClose:)
             name:NSWindowWillCloseNotification
           object:windowController.window];
  [_windowControllers addObject:windowController];
  [windowController showWindow:self];
}

#pragma mark NSUserInterfaceValidations

- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)item {
  SEL action = item.action;
  if (action == @selector(newWindow:)) {
    const auto& options = solas::app::RunnerFactory::Shared().options();
    return options.multiple_windows();
  }
  return NO;
}

@end
