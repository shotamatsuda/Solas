//
//  SLSQuartzLayer.mm
//
//  The MIT License
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

#import "SLSQuartzLayer.h"

#include "solas/app_event.h"
#include "takram/math.h"

@implementation SLSQuartzLayer

- (instancetype)init {
  self = [super init];
  if (self) {
    self.needsDisplayOnBoundsChange = YES;
    self.drawsAsynchronously = YES;
    self.actions = @{ @"contents" : [NSNull null] };
  }
  return self;
}

- (void)drawInContext:(CGContextRef)context {
  CGRect bounds = self.bounds;
  const takram::Size2d size(bounds.size.width, bounds.size.height);
  if ([_displayDelegate respondsToSelector:
          @selector(displayDelegate:update:)]) {
    const solas::AppEvent event(solas::AppEvent::Type::UPDATE,
                                context, size, self.contentsScale);
    [_displayDelegate displayDelegate:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:
          @selector(displayDelegate:draw:)]) {
    const solas::AppEvent event(solas::AppEvent::Type::DRAW,
                                context, size, self.contentsScale);
    [_displayDelegate displayDelegate:self draw:SLSAppEventMake(&event)];
  }
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  if ([NSThread isMainThread]) {
    [self setNeedsDisplay];
  } else {
    // Don't wait until done here because CVDisplayLinkStop call on
    // CVDisplayLink's deallocation on the main thread will result in deadlock.
    [self performSelectorOnMainThread:@selector(setNeedsDisplay)
                           withObject:nil
                        waitUntilDone:NO];
  }
}

@end
