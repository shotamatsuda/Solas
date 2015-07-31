//
//  SLSNSView.m
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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

#import "SLSNSView.h"

#import <QuartzCore/QuartzCore.h>

#import "SLSDisplayDelegate.h"
#import "SLSDisplaySource.h"
#import "SLSQuartzLayer.h"

@interface SLSNSView () {
 @private
  BOOL _mouseDownCanMoveWindow;
}

#pragma mark Initialization

@property (nonatomic, strong) CALayer<SLSDisplaySource> *displaySource;

@end

@implementation SLSNSView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.wantsLayer = YES;
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    self.wantsLayer = YES;
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
  }
  return self;
}

- (BOOL)isOpaque {
  return YES;
}

- (CALayer *)makeBackingLayer {
  NSAssert(NO, @"Subclass must implement makeBackingLayer");
  return nil;  // Implement in subviews
}

- (BOOL)mouseDownCanMoveWindow {
  return _mouseDownCanMoveWindow;
}

- (void)setMouseDownCanMoveWindow:(BOOL)flag {
  _mouseDownCanMoveWindow = flag;
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [_displaySource setDisplaySourceNeedsDisplay];
}

#pragma mark Managing the Delegate

- (id<SLSDisplayDelegate>)displayDelegate {
  return _displaySource.displayDelegate;
}

- (void)setDisplayDelegate:(id<SLSDisplayDelegate>)displayDelegate {
  _displaySource.displayDelegate = displayDelegate;
}

@end
