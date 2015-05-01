//
//  SLSNSWindowController.m
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

#import "SLSNSWindowController.h"

#import "SLSNSBundle+Bundle.h"
#import "SLSNSViewController.h"

@implementation SLSNSWindowController

- (instancetype)initWithViewController:(SLSNSViewController *)viewController {
  NSString *path = [[NSBundle solasBundle]
      pathForResource:@"SLSNSWindowController"
               ofType:@"nib"];
  self = [super initWithWindowNibPath:path owner:self];
  if (self) {
    _viewController = viewController;
  }
  return self;
}

- (void)windowDidLoad {
  [super windowDidLoad];
  self.window.backgroundColor = [NSColor whiteColor];
  NSView *view = _viewController.view;
  view.frame = ((NSView *)self.window.contentView).frame;
  view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
  [self.window.contentView addSubview:view];
}

@end
