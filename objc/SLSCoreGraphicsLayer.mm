//
//  SLSCoreGraphicsLayer.mm
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

#import "SLSCoreGraphicsLayer.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSDisplayLink.h"
#import "SLSEvents.h"

#include "solas/app/app_event.h"
#include "solas/math/size.h"

@interface SLSCoreGraphicsLayer ()

@property (nonatomic, strong) SLSDisplayLink *displayLink;

- (void)setNeedsDisplayOnMainThread;

@end

@implementation SLSCoreGraphicsLayer

- (instancetype)init {
  self = [super init];
  if (self) {
    self.needsDisplayOnBoundsChange = YES;
    self.drawsAsynchronously = YES;
    self.actions = @{ @"contents" : [NSNull null] };
    [self startLoop];
  }
  return self;
}

#pragma mark Controlling Loop

- (void)startLoop {
  if (!_displayLink) {
    _displayLink = [SLSDisplayLink
        displayLinkWithTarget:self
                     selector:@selector(setNeedsDisplayOnMainThread)];
  }
  [_displayLink start];
}

- (void)stopLoop {
  if (_displayLink) {
    [_displayLink stop];
  }
}

- (void)setNeedsDisplayOnMainThread {
  [super performSelectorOnMainThread:@selector(setNeedsDisplay)
                          withObject:self
                       waitUntilDone:YES];
}

- (void)drawInContext:(CGContextRef)context {
  const solas::app::AppEvent event(context, solas::math::Size2d(
      self.bounds.size.width, self.bounds.size.height));
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
}

@end
