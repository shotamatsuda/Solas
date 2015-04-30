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
#include "solas/app/gesture_kind.h"
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
- (solas::app::GestureEvent::Type)gestureEventTypeWithState:
    (UIGestureRecognizerState)state;
- (std::vector<solas::math::Vec2d>)touchesWithGestureRecognizer:
    (UIGestureRecognizer *)recognizer;

#pragma mark Gesture Recognizer

- (void)addGestureRecognizers;
- (void)handleTapGesture:(UITapGestureRecognizer *)recognizer;
- (void)handleSwipeRightGesture:(UISwipeGestureRecognizer *)recognizer;
- (void)handleSwipeLeftGesture:(UISwipeGestureRecognizer *)recognizer;
- (void)handleSwipeUpGesture:(UISwipeGestureRecognizer *)recognizer;
- (void)handleSwipeDownGesture:(UISwipeGestureRecognizer *)recognizer;
- (void)handleSwipeGesture:(UISwipeGestureRecognizer *)recognizer
                 direction:(UISwipeGestureRecognizerDirection)direction;

@end

@implementation SLSUIEventSourceView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.multipleTouchEnabled = YES;
    [self addGestureRecognizers];
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
  self = [super initWithCoder:decoder];
  if (self) {
    self.multipleTouchEnabled = YES;
    [self addGestureRecognizers];
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
  std::vector<solas::math::Vec2d> touches;
  for (UITouch *touch in event.allTouches) {
    CGPoint location = [touch locationInView:self];
    touches.emplace_back(location.x, location.y);
  }
  const solas::app::TouchEvent touchEvent(type, touches, _previousTouches);
  _previousTouches = touches;
  return std::move(touchEvent);
}

- (solas::app::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::app::MotionEvent::Type)type {
  return solas::app::MotionEvent();
}

- (solas::app::GestureEvent::Type)gestureEventTypeWithState:
    (UIGestureRecognizerState)state {
  switch (state) {
    case UIGestureRecognizerStateBegan:
      return solas::app::GestureEvent::Type::BEGIN;
    case UIGestureRecognizerStateChanged:
      return solas::app::GestureEvent::Type::CHANGE;
    case UIGestureRecognizerStateCancelled:
      return solas::app::GestureEvent::Type::CANCEL;
    case UIGestureRecognizerStateEnded:
      return solas::app::GestureEvent::Type::END;
    default:
      break;
  }
  return solas::app::GestureEvent::Type::UNDEFINED;
}

- (std::vector<solas::math::Vec2d>)touchesWithGestureRecognizer:
    (UIGestureRecognizer *)recognizer {
  std::vector<solas::math::Vec2d> touches;
  for (NSInteger i = 0; i < recognizer.numberOfTouches; ++i) {
    CGPoint location = [recognizer locationOfTouch:i inView:self];
    touches.emplace_back(location.x, location.y);
  }
  return std::move(touches);
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

#pragma mark Gesture Recognizer

- (void)addGestureRecognizers {
  // Tap
  UITapGestureRecognizer *doubleTapGesture = [[UITapGestureRecognizer alloc]
      initWithTarget:self action:@selector(handleDoubleTapGesture:)];
  doubleTapGesture.numberOfTapsRequired = 2;
  doubleTapGesture.delaysTouchesBegan = NO;
  doubleTapGesture.delaysTouchesEnded = NO;
  [self addGestureRecognizer:doubleTapGesture];
  UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc]
      initWithTarget:self action:@selector(handleTapGesture:)];
  tapGesture.numberOfTapsRequired = 1;
  tapGesture.delaysTouchesBegan = NO;
  tapGesture.delaysTouchesEnded = NO;
  [tapGesture requireGestureRecognizerToFail:doubleTapGesture];
  [self addGestureRecognizer:tapGesture];
//  tapGesture = [[UITapGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handleTripleTapGesture:)];
//  tapGesture.numberOfTapsRequired = 3;
//  tapGesture.delaysTouchesBegan = NO;
//  tapGesture.delaysTouchesEnded = NO;
//  [self addGestureRecognizer:tapGesture];
//
//  // Pinch and rotation
//  [self addGestureRecognizer:[[UIPinchGestureRecognizer alloc]
//    initWithTarget:self action:@selector(handlePinchGesture:)]];
//  [self addGestureRecognizer:[[UIRotationGestureRecognizer alloc]
//    initWithTarget:self action:@selector(handleRotationGesture:)]];
//
//  // Swipe
//  UISwipeGestureRecognizer *swipeGesture;
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handleSwipeRightGesture:)];
//  swipeGesture.numberOfTouchesRequired = 1;
//  swipeGesture.direction = UISwipeGestureRecognizerDirectionRight;
//  [self addGestureRecognizer:swipeGesture];
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handleSwipeLeftGesture:)];
//  swipeGesture.numberOfTouchesRequired = 1;
//  swipeGesture.direction = UISwipeGestureRecognizerDirectionLeft;
//  [self addGestureRecognizer:swipeGesture];
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handleSwipeUpGesture:)];
//  swipeGesture.numberOfTouchesRequired = 1;
//  swipeGesture.direction = UISwipeGestureRecognizerDirectionUp;
//  [self addGestureRecognizer:swipeGesture];
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handleSwipeDownGesture:)];
//  swipeGesture.numberOfTouchesRequired = 1;
//  swipeGesture.direction = UISwipeGestureRecognizerDirectionDown;
//  [self addGestureRecognizer:swipeGesture];
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handle2FingersSwipeGesture:)];
//  swipeGesture.numberOfTouchesRequired = 2;
//  [self addGestureRecognizer:swipeGesture];
//  swipeGesture = [[UISwipeGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handle3FingersSwipeGesture:)];
//  swipeGesture.numberOfTouchesRequired = 3;
//  [self addGestureRecognizer:swipeGesture];
//
//  // Pan
//  UIPanGestureRecognizer *panGesture;
//  panGesture = [[UIPanGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handlePanGesture:)];
//  panGesture.minimumNumberOfTouches = 1;
//  panGesture.maximumNumberOfTouches = 1;
//  [self addGestureRecognizer:panGesture];
//  panGesture = [[UIPanGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handle2FingersPanGesture:)];
//  panGesture.minimumNumberOfTouches = 2;
//  panGesture.maximumNumberOfTouches = 2;
//  [self addGestureRecognizer:panGesture];
//  panGesture = [[UIPanGestureRecognizer alloc]
//      initWithTarget:self action:@selector(handle3FingersPanGesture:)];
//  panGesture.minimumNumberOfTouches = 3;
//  panGesture.maximumNumberOfTouches = 3;
//  [self addGestureRecognizer:panGesture];
}

- (void)handleTapGesture:(UITapGestureRecognizer *)recognizer {
  const auto type = [self gestureEventTypeWithState:recognizer.state];
  const std::vector<solas::math::Vec2d> touches(
      [self touchesWithGestureRecognizer:recognizer]);
  const solas::app::GestureEvent event(
      type, solas::app::GestureKind::TAP, touches);
  if (recognizer.state == UIGestureRecognizerStateBegan) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureBegin:)]) {
      [_eventDelegate sender:self gestureBegin:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateChanged) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureChange:)]) {
      [_eventDelegate sender:self gestureChange:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateCancelled) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureCancel:)]) {
      [_eventDelegate sender:self gestureCancel:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateEnded) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureEnd:)]) {
      [_eventDelegate sender:self gestureEnd:SLSGestureEventMake(&event)];
    }
  }
}

- (void)handleDoubleTapGesture:(UITapGestureRecognizer *)recognizer {
  const auto type = [self gestureEventTypeWithState:recognizer.state];
  const std::vector<solas::math::Vec2d> touches(
      [self touchesWithGestureRecognizer:recognizer]);
  const solas::app::GestureEvent event(
      type, solas::app::GestureKind::DOUBLE_TAP, touches);
  if (recognizer.state == UIGestureRecognizerStateBegan) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureBegin:)]) {
      [_eventDelegate sender:self gestureBegin:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateChanged) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureChange:)]) {
      [_eventDelegate sender:self gestureChange:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateCancelled) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureCancel:)]) {
      [_eventDelegate sender:self gestureCancel:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateEnded) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureEnd:)]) {
      [_eventDelegate sender:self gestureEnd:SLSGestureEventMake(&event)];
    }
  }
}

- (void)handleSwipeRightGesture:(UISwipeGestureRecognizer *)recognizer {
  [self handleSwipeGesture:recognizer
                 direction:UISwipeGestureRecognizerDirectionRight];
}

- (void)handleSwipeLeftGesture:(UISwipeGestureRecognizer *)recognizer {
  [self handleSwipeGesture:recognizer
                 direction:UISwipeGestureRecognizerDirectionLeft];
}

- (void)handleSwipeUpGesture:(UISwipeGestureRecognizer *)recognizer {
  [self handleSwipeGesture:recognizer
                 direction:UISwipeGestureRecognizerDirectionUp];
}

- (void)handleSwipeDownGesture:(UISwipeGestureRecognizer *)recognizer {
  [self handleSwipeGesture:recognizer
                 direction:UISwipeGestureRecognizerDirectionDown];
}

- (void)handleSwipeGesture:(UISwipeGestureRecognizer *)recognizer
                 direction:(UISwipeGestureRecognizerDirection)direction {
//  const auto type = [self gestureEventTypeWithState:recognizer.state];
//  const std::vector<solas::math::Vec2d> touches(
//      [self touchesWithGestureRecognizer:recognizer]);
//  solas::app::GestureDirection dir;
//  if (direction & UISwipeGestureRecognizerDirectionRight) {
//    dir = solas::app::GestureDirection::RIGHT;
//  } else if (recognizer.direction & UISwipeGestureRecognizerDirectionLeft) {
//    dir = solas::app::GestureDirection::LEFT;
//  } else if (recognizer.direction & UISwipeGestureRecognizerDirectionUp) {
//    dir = solas::app::GestureDirection::UP;
//  } else if (recognizer.direction & UISwipeGestureRecognizerDirectionDown) {
//    dir = solas::app::GestureDirection::DOWN;
//  }
//  const solas::app::GestureEvent event(
//      type, solas::app::GestureKind::SWIPE, touches, dir);
//  if (recognizer.state == UIGestureRecognizerStateBegan) {
//    if ([_eventDelegate respondsToSelector:@selector(sender:gestureBegin:)]) {
//      [_eventDelegate sender:self gestureBegin:SLSGestureEventMake(&event)];
//    }
//  } else if (recognizer.state == UIGestureRecognizerStateChanged) {
//    if ([_eventDelegate respondsToSelector:@selector(sender:gestureChange:)]) {
//      [_eventDelegate sender:self gestureChange:SLSGestureEventMake(&event)];
//    }
//  } else if (recognizer.state == UIGestureRecognizerStateCancelled) {
//    if ([_eventDelegate respondsToSelector:@selector(sender:gestureCancel:)]) {
//      [_eventDelegate sender:self gestureCancel:SLSGestureEventMake(&event)];
//    }
//  } else if (recognizer.state == UIGestureRecognizerStateEnded) {
//    if ([_eventDelegate respondsToSelector:@selector(sender:gestureEnd:)]) {
//      [_eventDelegate sender:self gestureEnd:SLSGestureEventMake(&event)];
//    }
//  }
}

@end
