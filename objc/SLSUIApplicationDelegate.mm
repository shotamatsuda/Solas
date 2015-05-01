//
//  SLSUIApplicationDelegate.mm
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

#import "SLSUIApplicationDelegate.h"

#import "SLSRunner.h"
#import "SLSUIViewController.h"

#include "solas/app/runner_factory.h"

@implementation SLSUIApplicationDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application {
  SLSRunner *runner = [[SLSRunner alloc]
      initWithRunnable:solas::app::RunnerFactory::Shared().create()];
  SLSUIViewController *viewController =
      [[SLSUIViewController alloc] initWithRunner:runner];
  _window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  _window.rootViewController = viewController;
  [_window makeKeyAndVisible];
}

@end
