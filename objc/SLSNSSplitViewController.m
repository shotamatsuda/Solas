//
//  SLSNSSplitViewController.m
//
//  The MIT License
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

#import "SLSNSSplitViewController.h"

@interface SLSNSSplitViewController ()

#pragma mark Controlling Subview's State

@property (nonatomic, assign) CGFloat leadingPosition;
@property (nonatomic, assign) CGFloat traillingPosition;

@end

@implementation SLSNSSplitViewController

- (instancetype)init {
  self = [super init];
  if (self) {
    _leadingViewCollapsible = YES;
    _trailingViewCollapsible = YES;
  }
  return self;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil
                         bundle:(NSBundle *)nibBundleOrNil {
  self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
  if (self) {
    _leadingViewCollapsible = YES;
    _trailingViewCollapsible = YES;
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    _leadingViewCollapsible = YES;
    _trailingViewCollapsible = YES;
  }
  return self;
}

- (void)dealloc {
  self.splitView.delegate = nil;
}

- (void)setView:(NSView *)view {
  [super setView:view];
  NSAssert([view isKindOfClass:[NSSplitView class]], nil);
  ((NSSplitView *)view).delegate = self;
}

#pragma mark Accessing Views

- (NSSplitView *)splitView {
  return (NSSplitView *)self.view;
}

#pragma mark Controlling Subview's State

- (BOOL)isLeadingViewCollapsed {
  NSSplitView *splitView = self.splitView;
  if (splitView.subviews.firstObject == _leadingView) {
    return [splitView isSubviewCollapsed:_leadingView];
  }
  return NO;
}

- (void)setLeadingViewCollapsed:(BOOL)value {
  NSSplitView *splitView = self.splitView;
  NSArray *subviews = splitView.subviews;
  if (subviews.count < 2) {
    return;  // For cannot collapse the view
  }
  if (subviews.firstObject == _leadingView &&
      value != self.leadingViewCollapsed) {
    if (value) {
      [splitView setPosition:0.0 ofDividerAtIndex:0];
    } else {
      [splitView setPosition:_leadingPosition ofDividerAtIndex:0];
    }
  }
}

- (BOOL)isTrailingViewCollapsed {
  NSSplitView *splitView = self.splitView;
  if (splitView.subviews.lastObject == _trailingView) {
    return [splitView isSubviewCollapsed:_trailingView];
  }
  return NO;
}

- (void)setTrailingViewCollapsed:(BOOL)value {
  NSSplitView *splitView = self.splitView;
  NSArray *subviews = splitView.subviews;
  if (subviews.count < 2) {
    return;  // For cannot collapse the view
  }
  if (subviews.lastObject == _trailingView &&
      value != self.trailingViewCollapsed) {
    if (value) {
      CGFloat position;
      if (splitView.vertical) {
        position = splitView.frame.size.width;
      } else {
        position = splitView.frame.size.height;
      }
      [splitView setPosition:position ofDividerAtIndex:subviews.count - 2];
    } else {
      [splitView setPosition:_traillingPosition
            ofDividerAtIndex:subviews.count - 2];
    }
  }
}

#pragma mark Received Actions

- (IBAction)collapseLeadingView:(id)sender {
  self.leadingViewCollapsed = YES;
}

- (IBAction)collapseTrailingView:(id)sender {
  self.trailingViewCollapsed = YES;
}

- (IBAction)expandLeadingView:(id)sender {
  self.leadingViewCollapsed = NO;
}

- (IBAction)expandTrailingView:(id)sender {
  self.trailingViewCollapsed = NO;
}

- (IBAction)toggleLeadingViewCollapsed:(id)sender {
  self.leadingViewCollapsed = !self.leadingViewCollapsed;
}

- (IBAction)toggleTrailingViewCollapsed:(id)sender {
  self.trailingViewCollapsed = !self.trailingViewCollapsed;
}

#pragma mark NSSplitViewDelegate

- (CGRect)splitView:(NSSplitView *)splitView
    additionalEffectiveRectOfDividerAtIndex:(NSInteger)dividerIndex {
  NSArray *subviews = splitView.subviews;
  if (dividerIndex == 0 &&
      subviews.firstObject == _leadingView &&
      _leadingHandle && !self.leadingViewCollapsed) {
    return [splitView convertRect:_leadingHandle.bounds
                         fromView:_leadingHandle];
  }
  if (dividerIndex == subviews.count - 2 &&
      subviews.lastObject == _trailingView &&
      _trailingHandle && !self.trailingViewCollapsed) {
    return [splitView convertRect:_trailingHandle.bounds
                         fromView:_trailingHandle];
  }
  return NSZeroRect;
}

- (void)splitViewDidResizeSubviews:(NSNotification *)notification {
  NSSplitView *splitView = self.splitView;
  NSArray *subviews = splitView.subviews;
  if (subviews.firstObject == _leadingView && !self.leadingViewCollapsed) {
    CGFloat position;
    if (splitView.vertical) {
      position = _leadingView.frame.size.width;
    } else {
      position = _leadingView.frame.size.height;
    }
    _leadingPosition = position;
  }
  if (subviews.lastObject == _trailingView && !self.trailingViewCollapsed) {
    CGFloat position;
    if (splitView.vertical) {
      position = splitView.frame.size.width - _trailingView.frame.size.width;
    } else {
      position = splitView.frame.size.height - _trailingView.frame.size.height;
    }
    position -= splitView.dividerThickness * (subviews.count - 1);
    _traillingPosition = position;
  }
}

- (BOOL)splitView:(NSSplitView *)splitView
    canCollapseSubview:(NSView *)subview {
  return (subview && ((subview == _leadingView && _leadingViewCollapsible) ||
                      (subview == _trailingView && _trailingViewCollapsible)));
}

- (BOOL)splitView:(NSSplitView *)splitView
    shouldCollapseSubview:(NSView *)subview
    forDoubleClickOnDividerAtIndex:(NSInteger)dividerIndex {
  return [self splitView:splitView canCollapseSubview:subview];
}

- (BOOL)splitView:(NSSplitView *)splitView
    shouldHideDividerAtIndex:(NSInteger)dividerIndex {
  return YES;
}

@end
