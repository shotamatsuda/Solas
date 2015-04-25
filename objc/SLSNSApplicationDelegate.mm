//
//  SLSNSApplicationDelegate.mm
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
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

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
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
  SLSRunner *runner =
      [[SLSRunner alloc] initWithRunnable:solas::app::RunnerFactory::Shared().create()];
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
