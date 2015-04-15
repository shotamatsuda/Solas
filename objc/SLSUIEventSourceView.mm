//
//  SLSUIEventSourceView.mm
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

#import "SLSUIEventSourceView.h"

#import "SLSEvents.h"

#include <utility>
#include <vector>

#include "solas/app/gesture_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/touch_event.h"
#include "solas/math/vector.h"

@interface SLSUIEventSourceView () {
 @private
  std::vector<solas::math::Vec2d> _previousTouches;
}

#pragma mark Creating Events

- (solas::app::TouchEvent)touchEventWithEvent:(UIEvent *)event
    type:(solas::app::TouchEvent::Type)type;
- (solas::app::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::app::MotionEvent::Type)type;

@end

@implementation SLSUIEventSourceView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    _internalContentsScaleFactor = 1.0;
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
  self = [super initWithCoder:decoder];
  if (self) {
    _internalContentsScaleFactor = 1.0;
  }
  return self;
}

- (BOOL)isFlipped {
  return YES;
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

#pragma mark Responding to Events

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesBeginWithEvent:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesMoveWithEvent:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesCancelWithEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesEndWithEvent:event];
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionBeginWithEvent:event];
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionCancelWithEvent:event];
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionEndWithEvent:event];
}

#pragma mark Creating Events

- (solas::app::TouchEvent)touchEventWithEvent:(UIEvent *)event
    type:(solas::app::TouchEvent::Type)type {
  CGFloat scale = self.internalContentsScaleFactor;
  std::vector<solas::math::Vec2d> touches;
  for (UITouch *touch in event.allTouches) {
    CGPoint location = [touch locationInView:self];
    touches.emplace_back(location.x * scale, location.y * scale);
  }
  const solas::app::TouchEvent touchEvent(type, touches, _previousTouches);
  _previousTouches = touches;
  return std::move(touchEvent);
}

- (solas::app::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::app::MotionEvent::Type)type {
  return solas::app::MotionEvent();
}

#pragma mark Notifying Events to the Delegate

- (void)notifyTouchesBeginWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesBegin:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::BEGIN]);
    [_eventDelegate sender:self touchesBegin:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesMoveWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesMove:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::MOVE]);
    [_eventDelegate sender:self touchesMove:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesCancelWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesCancel:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::CANCEL]);
    [_eventDelegate sender:self touchesCancel:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesEndWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesEnd:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::END]);
    [_eventDelegate sender:self touchesEnd:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyMotionBeginWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionBegin:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::BEGIN]);
    [_eventDelegate sender:self motionBegin:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionCancelWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionCancel:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::CANCEL]);
    [_eventDelegate sender:self motionCancel:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionEndWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionEnd:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::END]);
    [_eventDelegate sender:self motionEnd:SLSMotionEventMake(&motionEvent)];
  }
}

@end