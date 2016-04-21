//
//  SLSNSWindowController.m
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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

#import "SLSNSWindowController.h"

#import "SLSNSBundle+Bundle.h"
#import "SLSNSViewController.h"
#import "SLSNSSplitViewController.h"

@interface SLSNSWindowController ()

@property (nonatomic, strong) IBOutlet NSView *contentView;
@property (nonatomic, strong)
    IBOutlet SLSNSSplitViewController *splitViewController;

@end

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
  self.window.movableByWindowBackground = YES;
  NSView *view = _viewController.view;
  view.translatesAutoresizingMaskIntoConstraints = NO;
  [self.contentView addSubview:view];
  [self.contentView addConstraints:[NSLayoutConstraint
      constraintsWithVisualFormat:@"|-0-[view]-0-|"
      options:0
      metrics:nil
      views:NSDictionaryOfVariableBindings(view)]];
  [self.contentView addConstraints:[NSLayoutConstraint
      constraintsWithVisualFormat:@"V:|-0-[view]-0-|"
      options:0
      metrics:nil
      views:NSDictionaryOfVariableBindings(view)]];
  _splitViewController.leadingViewCollapsed = YES;
}

#pragma mark Configuring the Window Appearance

- (BOOL)darkContent {
  return [self.window.appearance.name
      isEqualToString:NSAppearanceNameVibrantDark];
}

- (void)setDarkContent:(BOOL)darkContent {
  NSString *appearanceName = NSAppearanceNameAqua;
  if (darkContent) {
    appearanceName = NSAppearanceNameVibrantDark;
  }
  self.window.appearance = [NSAppearance appearanceNamed:appearanceName];
}

- (BOOL)fullSizeContent {
  return (self.window.titleVisibility == NSWindowTitleHidden &&
          self.window.titlebarAppearsTransparent == YES &&
          self.window.styleMask & NSFullSizeContentViewWindowMask);
}

- (void)setFullSizeContent:(BOOL)fullSizeContent {
  if (fullSizeContent) {
    self.window.titleVisibility = NSWindowTitleHidden;
    self.window.titlebarAppearsTransparent = YES;
    self.window.styleMask |= NSFullSizeContentViewWindowMask;
  } else {
    self.window.titleVisibility = NSWindowTitleVisible;
    self.window.titlebarAppearsTransparent = NO;
    self.window.styleMask &= ~NSFullSizeContentViewWindowMask;
  }
}

@end
