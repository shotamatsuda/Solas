//
//  SLSQuartzLayer.mm
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

#import "SLSQuartzLayer.h"

#include "solas/app/app_event.h"
#include "solas/math/size.h"

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
  const solas::math::Size2d size(bounds.size.width, bounds.size.height);
  const solas::app::AppEvent event(context, size, self.contentsScale);
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [self performSelectorOnMainThread:@selector(setNeedsDisplay)
                         withObject:nil
                      waitUntilDone:YES];
}

@end
