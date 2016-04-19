//
//  SLSUIEventSourceView.mm
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

#import "SLSUIEventSourceView.h"

#import "SLSEvents.h"

#include <vector>

#include <boost/any.hpp>

#include "solas/gesture_event.h"
#include "solas/gesture_kind.h"
#include "solas/motion_event.h"
#include "solas/touch_event.h"
#include "takram/math.h"

@interface SLSUIEventSourceView () <UIGestureRecognizerDelegate>

#pragma mark Creating Events

- (solas::TouchEvent)touchEventWithEvent:(UIEvent *)event
    type:(solas::TouchEvent::Type)type;
- (solas::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::MotionEvent::Type)type
    kind:(solas::MotionKind)kind;
- (solas::GestureEvent)gestureEventWithRecognizer:
    (UIGestureRecognizer *)recognizer
    type:(solas::GestureEvent::Type)type
    kind:(solas::GestureKind)kind
    data:(const boost::any&)data;

#pragma mark Gesture Recognizer

- (void)addGestureRecognizers;

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
  [self notifyTouchesBeganWithEvent:event];
  [super touchesBegan:touches withEvent:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesMovedWithEvent:event];
  [super touchesMoved:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesCancelledWithEvent:event];
  [super touchesCancelled:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  [self notifyTouchesEndedWithEvent:event];
  [super touchesEnded:touches withEvent:event];
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionBeganWithEvent:event];
  [super motionBegan:motion withEvent:event];
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionCancelledWithEvent:event];
  [super motionCancelled:motion withEvent:event];
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  [self notifyMotionEndedWithEvent:event];
  [super motionEnded:motion withEvent:event];
}

#pragma mark Creating Events

- (solas::TouchEvent)touchEventWithEvent:(UIEvent *)event
    type:(solas::TouchEvent::Type)type {
  std::vector<takram::Vec2d> touches;
  for (UITouch *touch in event.allTouches) {
    CGPoint location = [touch locationInView:self];
    touches.emplace_back(location.x, location.y);
  }
  return solas::TouchEvent(type, touches);
}

- (solas::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::MotionEvent::Type)type
    kind:(solas::MotionKind)kind {
  return solas::MotionEvent(type, kind);
}

- (solas::GestureEvent)gestureEventWithRecognizer:
    (UIGestureRecognizer *)recognizer
    type:(solas::GestureEvent::Type)type
    kind:(solas::GestureKind)kind
    data:(const boost::any&)data {
  std::vector<takram::Vec2d> touches;
  for (NSInteger i = 0; i < recognizer.numberOfTouches; ++i) {
    CGPoint location = [recognizer locationOfTouch:i inView:self];
    touches.emplace_back(location.x, location.y);
  }
  return solas::GestureEvent(type, kind, touches, data);
}

#pragma mark Notifying Events to the Delegate

- (void)notifyTouchesBeganWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesBegan:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::BEGAN]);
    [_eventDelegate eventDelegate:self
                     touchesBegan:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesMovedWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesMoved:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::MOVED]);
    [_eventDelegate eventDelegate:self
                     touchesMoved:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesCancelledWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesCancelled:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::CANCELLED]);
    [_eventDelegate eventDelegate:self
                 touchesCancelled:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesEndedWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesEnded:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::ENDED]);
    [_eventDelegate eventDelegate:self
                     touchesEnded:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyMotionBeganWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:motionBegan:)]) {
    auto kind = solas::MotionKind::UNDEFINED;
    switch (event.subtype) {
      case UIEventSubtypeMotionShake:
        kind = solas::MotionKind::SHAKE;
        break;
      default:
        break;
    }
    if (kind == solas::MotionKind::UNDEFINED) {
      return;
    }
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::MotionEvent::Type::BEGAN kind:kind]);
    [_eventDelegate eventDelegate:self
                      motionBegan:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionCancelledWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:motionCancelled:)]) {
    auto kind = solas::MotionKind::UNDEFINED;
    switch (event.subtype) {
      case UIEventSubtypeMotionShake:
        kind = solas::MotionKind::SHAKE;
        break;
      default:
        break;
    }
    if (kind == solas::MotionKind::UNDEFINED) {
      return;
    }
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::MotionEvent::Type::CANCELLED kind:kind]);
    [_eventDelegate eventDelegate:self
                  motionCancelled:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionEndedWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:motionEnded:)]) {
    auto kind = solas::MotionKind::UNDEFINED;
    switch (event.subtype) {
      case UIEventSubtypeMotionShake:
        kind = solas::MotionKind::SHAKE;
        break;
      default:
        break;
    }
    if (kind == solas::MotionKind::UNDEFINED) {
      return;
    }
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::MotionEvent::Type::ENDED kind:kind]);
    [_eventDelegate eventDelegate:self
                      motionEnded:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyGestureWithRecognizer:(UIGestureRecognizer *)recognizer
                               kind:(solas::GestureKind)kind
                               data:(const boost::any&)data {
  if (recognizer.state == UIGestureRecognizerStateBegan) {
    if ([_eventDelegate respondsToSelector:
            @selector(eventDelegate:gestureBegan:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::GestureEvent::Type::BEGAN
          kind:kind data:data]);
      [_eventDelegate eventDelegate:self
                       gestureBegan:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateChanged) {
    if ([_eventDelegate respondsToSelector:
            @selector(eventDelegate:gestureChanged:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::GestureEvent::Type::CHANGED
          kind:kind data:data]);
      [_eventDelegate eventDelegate:self
                     gestureChanged:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateCancelled) {
    if ([_eventDelegate respondsToSelector:
            @selector(eventDelegate:gestureCancelled:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::GestureEvent::Type::CANCELLED
          kind:kind data:data]);
      [_eventDelegate eventDelegate:self
                   gestureCancelled:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateEnded) {
    if ([_eventDelegate respondsToSelector:
            @selector(eventDelegate:gestureEnded:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::GestureEvent::Type::ENDED
          kind:kind data:data]);
      [_eventDelegate eventDelegate:self
                       gestureEnded:SLSGestureEventMake(&event)];
    }
  }
}

#pragma mark Gesture Recognizer

- (void)addGestureRecognizers {
  // Tap
  NSMutableArray *tapGestures = [NSMutableArray array];
  for (NSInteger touches = 1; touches <= 4; ++touches) {
    UITapGestureRecognizer *previousGesture = nil;
    for (NSInteger taps = 3; taps >= 1; --taps) {
      UITapGestureRecognizer *gesture =
          [[UITapGestureRecognizer alloc]
              initWithTarget:self action:@selector(handleTapGesture:)];
      gesture.cancelsTouchesInView = NO;
      gesture.delaysTouchesBegan = NO;
      gesture.delaysTouchesEnded = NO;
      gesture.numberOfTapsRequired = taps;
      gesture.numberOfTouchesRequired = touches;
      gesture.delegate = self;
      if (previousGesture) {
        [gesture requireGestureRecognizerToFail:previousGesture];
      }
      [self addGestureRecognizer:gesture];
      [tapGestures addObject:gesture];
      previousGesture = gesture;
    }
  }

  // Pinch
  UIPinchGestureRecognizer *pinchGesture =
      [[UIPinchGestureRecognizer alloc]
          initWithTarget:self action:@selector(handlePinchGesture:)];
  pinchGesture.cancelsTouchesInView = NO;
  [self addGestureRecognizer:pinchGesture];

  // Rotation
  UIRotationGestureRecognizer *rotationGesture =
      [[UIRotationGestureRecognizer alloc]
          initWithTarget:self action:@selector(handleRotationGesture:)];
  rotationGesture.cancelsTouchesInView = NO;
  [self addGestureRecognizer:rotationGesture];

  // Pan
  NSMutableArray *panGestures = [NSMutableArray array];
  for (NSInteger touches = 1; touches <= 4; ++touches) {
    UIPanGestureRecognizer *gesture =
        [[UIPanGestureRecognizer alloc]
            initWithTarget:self action:@selector(handlePanGesture:)];
    gesture.cancelsTouchesInView = NO;
    gesture.minimumNumberOfTouches = touches;
    gesture.maximumNumberOfTouches = touches;
    gesture.delegate = self;
    [self addGestureRecognizer:gesture];
    [panGestures addObject:gesture];
  }

  // Swipe
  NSMutableArray *swipeGestures = [NSMutableArray array];
  for (NSInteger touches = 1; touches <= 4; ++touches) {
    const std::vector<UISwipeGestureRecognizerDirection> directions{
      UISwipeGestureRecognizerDirectionRight,
      UISwipeGestureRecognizerDirectionLeft,
      UISwipeGestureRecognizerDirectionUp,
      UISwipeGestureRecognizerDirectionDown,
    };
    for (UISwipeGestureRecognizerDirection direction : directions) {
      UISwipeGestureRecognizer *gesture =
          [[UISwipeGestureRecognizer alloc]
              initWithTarget:self action:@selector(handleSwipeGesture:)];
      gesture.cancelsTouchesInView = NO;
      gesture.numberOfTouchesRequired = touches;
      gesture.direction = direction;
      gesture.delegate = self;
      [self addGestureRecognizer:gesture];
      [swipeGestures addObject:gesture];
    }
  }

  // Screen edge pan
  NSMutableArray *screenEdgePanGestures = [NSMutableArray array];
  UIScreenEdgePanGestureRecognizer *screenEdgePanGesture;
  screenEdgePanGesture =
      [[UIScreenEdgePanGestureRecognizer alloc]
          initWithTarget:self
           action:@selector(handleScreenTopEdgePanGesture:)];
  screenEdgePanGesture.cancelsTouchesInView = NO;
  screenEdgePanGesture.edges = UIRectEdgeTop;
  screenEdgePanGesture.delegate = self;
  [self addGestureRecognizer:screenEdgePanGesture];
  [screenEdgePanGestures addObject:screenEdgePanGesture];
  screenEdgePanGesture =
      [[UIScreenEdgePanGestureRecognizer alloc]
          initWithTarget:self
           action:@selector(handleScreenLeftEdgePanGesture:)];
  screenEdgePanGesture.cancelsTouchesInView = NO;
  screenEdgePanGesture.edges = UIRectEdgeLeft;
  screenEdgePanGesture.delegate = self;
  [self addGestureRecognizer:screenEdgePanGesture];
  [screenEdgePanGestures addObject:screenEdgePanGesture];
  screenEdgePanGesture =
      [[UIScreenEdgePanGestureRecognizer alloc]
          initWithTarget:self
           action:@selector(handleScreenBottomEdgePanGesture:)];
  screenEdgePanGesture.cancelsTouchesInView = NO;
  screenEdgePanGesture.edges = UIRectEdgeBottom;
  screenEdgePanGesture.delegate = self;
  [self addGestureRecognizer:screenEdgePanGesture];
  [screenEdgePanGestures addObject:screenEdgePanGesture];
  screenEdgePanGesture =
      [[UIScreenEdgePanGestureRecognizer alloc]
          initWithTarget:self
           action:@selector(handleScreenRightEdgePanGesture:)];
  screenEdgePanGesture.cancelsTouchesInView = NO;
  screenEdgePanGesture.edges = UIRectEdgeRight;
  screenEdgePanGesture.delegate = self;
  [self addGestureRecognizer:screenEdgePanGesture];
  [screenEdgePanGestures addObject:screenEdgePanGesture];
}

- (void)handleTapGesture:(UITapGestureRecognizer *)recognizer {
  solas::GestureEvent::TapData data;
  data.taps = recognizer.numberOfTapsRequired;
  data.touches = recognizer.numberOfTouchesRequired;
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::TAP data:data];
}

- (void)handlePinchGesture:(UIPinchGestureRecognizer *)recognizer {
  solas::GestureEvent::PinchData data;
  data.scale = recognizer.scale;
  data.velocity = recognizer.velocity;
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::PINCH data:data];
}

- (void)handleRotationGesture:(UIRotationGestureRecognizer *)recognizer {
  solas::GestureEvent::RotationData data;
  data.rotation = recognizer.rotation;
  data.velocity = recognizer.velocity;
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::ROTATION data:data];
}

- (void)handleSwipeGesture:(UISwipeGestureRecognizer *)recognizer {
  solas::GestureEvent::SwipeData data;
  if (recognizer.direction == UISwipeGestureRecognizerDirectionRight) {
    data.direction = solas::SwipeDirection::RIGHT;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft) {
    data.direction = solas::SwipeDirection::LEFT;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionUp) {
    data.direction = solas::SwipeDirection::RELEASED;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionDown) {
    data.direction = solas::SwipeDirection::PRESSED;
  }
  data.touches = recognizer.numberOfTouchesRequired;
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::SWIPE data:data];
}

- (void)handlePanGesture:(UIPanGestureRecognizer *)recognizer {
  solas::GestureEvent::PanData data;
  CGPoint translation = [recognizer translationInView:self];
  data.translation.set(translation.x, translation.y);
  CGPoint velocity = [recognizer velocityInView:self];
  data.velocity.set(velocity.x, velocity.y);
  data.touches = recognizer.minimumNumberOfTouches;
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::PAN data:data];
}

- (void)handleScreenTopEdgePanGesture:
    (UIScreenEdgePanGestureRecognizer *)recognizer {
  [self handleScreenEdgePanGesture:recognizer edge:UIRectEdgeTop];
}

- (void)handleScreenLeftEdgePanGesture:
    (UIScreenEdgePanGestureRecognizer *)recognizer {
  [self handleScreenEdgePanGesture:recognizer edge:UIRectEdgeLeft];
}

- (void)handleScreenBottomEdgePanGesture:
    (UIScreenEdgePanGestureRecognizer *)recognizer {
  [self handleScreenEdgePanGesture:recognizer edge:UIRectEdgeBottom];
}

- (void)handleScreenRightEdgePanGesture:
    (UIScreenEdgePanGestureRecognizer *)recognizer {
  [self handleScreenEdgePanGesture:recognizer edge:UIRectEdgeRight];
}

- (void)handleScreenEdgePanGesture:
    (UIScreenEdgePanGestureRecognizer *)recognizer
    edge:(UIRectEdge)edge {
  solas::GestureEvent::ScreenEdgeData data;
  if (edge == UIRectEdgeTop) {
    data.edge = solas::ScreenEdge::TOP;
  } else if (edge == UIRectEdgeLeft) {
    data.edge = solas::ScreenEdge::LEFT;
  } else if (edge == UIRectEdgeBottom) {
    data.edge = solas::ScreenEdge::BOTTOM;
  } else if (edge == UIRectEdgeRight) {
    data.edge = solas::ScreenEdge::RIGHT;
  }
  [self notifyGestureWithRecognizer:recognizer
      kind:solas::GestureKind::SCREEN_EDGE data:data];
}

#pragma mark UIGestureRecognizerDelegate

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
    shouldRecognizeSimultaneouslyWithGestureRecognizer:
        (UIGestureRecognizer *)otherGestureRecognizer {
  return YES;
}

@end
