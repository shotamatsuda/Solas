//
//  SLSNSOpenGLView.m
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

#import "SLSNSOpenGLView.h"

#import <QuartzCore/QuartzCore.h>

#import "SLSDisplaySource.h"
#import "SLSOpenGLLayer.h"

@interface SLSNSOpenGLView ()

#pragma mark Initialization

@property (nonatomic, strong) CALayer<SLSDisplaySource> *displaySource;

@end

@implementation SLSNSOpenGLView

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

- (CALayer *)makeBackingLayer {
  return [SLSOpenGLLayer layer];
}

- (BOOL)isOpaque {
  return NO;
}

#pragma mark Controlling Loop

- (void)startLoop {
  [_displaySource startLoop];
}

- (void)stopLoop {
  [_displaySource stopLoop];
}

#pragma mark Managing the Delegate

- (id<SLSDisplayDelegate>)displayDelegate {
  return _displaySource.displayDelegate;
}

- (void)setDisplayDelegate:(id<SLSDisplayDelegate>)displayDelegate {
  _displaySource.displayDelegate = displayDelegate;
}

@end
