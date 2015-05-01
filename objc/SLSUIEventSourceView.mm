//
//  SLSUIEventSourceView.mm
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

#import "SLSUIEventSourceView.h"

#import "SLSEvents.h"

#include <utility>
#include <vector>

#include "solas/app/gesture_event.h"
#include "solas/app/gesture_kind.h"
#include "solas/app/motion_event.h"
#include "solas/app/touch_event.h"
#include "solas/math/vector.h"

@interface SLSUIEventSourceView () <UIGestureRecognizerDelegate>

#pragma mark Creating Events

- (solas::app::TouchEvent)touchEventWithEvent:(UIEvent *)event
    type:(solas::app::TouchEvent::Type)type;
- (solas::app::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::app::MotionEvent::Type)type;
- (solas::app::GestureEvent)gestureEventWithRecognizer:
    (UIGestureRecognizer *)recognizer
    type:(solas::app::GestureEvent::Type)type
    kind:(solas::app::GestureKind)kind
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
  return solas::app::TouchEvent(type, touches);
}

- (solas::app::MotionEvent)motionEventWithEvent:(UIEvent *)event
    type:(solas::app::MotionEvent::Type)type {
  return solas::app::MotionEvent();
}

- (solas::app::GestureEvent)gestureEventWithRecognizer:
    (UIGestureRecognizer *)recognizer
    type:(solas::app::GestureEvent::Type)type
    kind:(solas::app::GestureKind)kind
    data:(const boost::any&)data {
  std::vector<solas::math::Vec2d> touches;
  for (NSInteger i = 0; i < recognizer.numberOfTouches; ++i) {
    CGPoint location = [recognizer locationOfTouch:i inView:self];
    touches.emplace_back(location.x, location.y);
  }
  return solas::app::GestureEvent(type, kind, touches, data);
}

#pragma mark Notifying Events to the Delegate

- (void)notifyTouchesBeginWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesBegin:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::BEGIN]);
    [_eventDelegate sender:self touchesBegin:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesMoveWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesMove:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::MOVE]);
    [_eventDelegate sender:self touchesMove:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesCancelWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesCancel:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::CANCEL]);
    [_eventDelegate sender:self touchesCancel:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesEndWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:touchesEnd:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::app::TouchEvent::Type::END]);
    [_eventDelegate sender:self touchesEnd:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyMotionBeginWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionBegin:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::BEGIN]);
    [_eventDelegate sender:self motionBegin:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionCancelWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionCancel:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::CANCEL]);
    [_eventDelegate sender:self motionCancel:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyMotionEndWithEvent:(UIEvent *)event {
  if ([_eventDelegate respondsToSelector:@selector(sender:motionEnd:)]) {
    const auto motionEvent([self motionEventWithEvent:event
        type:solas::app::MotionEvent::Type::END]);
    [_eventDelegate sender:self motionEnd:SLSMotionEventMake(&motionEvent)];
  }
}

- (void)notifyGestureEventWithRecognizer:(UIGestureRecognizer *)recognizer
                                    kind:(solas::app::GestureKind)kind
                                    data:(const boost::any&)data {
  if (recognizer.state == UIGestureRecognizerStateBegan) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureBegin:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::app::GestureEvent::Type::BEGIN
          kind:kind data:data]);
      [_eventDelegate sender:self gestureBegin:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateChanged) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureChange:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::app::GestureEvent::Type::CHANGE
          kind:kind data:data]);
      [_eventDelegate sender:self gestureChange:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateCancelled) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureCancel:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::app::GestureEvent::Type::CANCEL
          kind:kind data:data]);
      [_eventDelegate sender:self gestureCancel:SLSGestureEventMake(&event)];
    }
  } else if (recognizer.state == UIGestureRecognizerStateEnded) {
    if ([_eventDelegate respondsToSelector:@selector(sender:gestureEnd:)]) {
      const auto event([self gestureEventWithRecognizer:recognizer
          type:solas::app::GestureEvent::Type::END
          kind:kind data:data]);
      [_eventDelegate sender:self gestureEnd:SLSGestureEventMake(&event)];
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
  solas::app::GestureEvent::TapData data;
  data.taps = recognizer.numberOfTapsRequired;
  data.touches = recognizer.numberOfTouchesRequired;
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::TAP data:data];
}

- (void)handlePinchGesture:(UIPinchGestureRecognizer *)recognizer {
  solas::app::GestureEvent::PinchData data;
  data.scale = recognizer.scale;
  data.velocity = recognizer.velocity;
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::PINCH data:data];
}

- (void)handleRotationGesture:(UIRotationGestureRecognizer *)recognizer {
  solas::app::GestureEvent::RotationData data;
  data.rotation = recognizer.rotation;
  data.velocity = recognizer.velocity;
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::ROTATION data:data];
}

- (void)handleSwipeGesture:(UISwipeGestureRecognizer *)recognizer {
  solas::app::GestureEvent::SwipeData data;
  if (recognizer.direction == UISwipeGestureRecognizerDirectionRight) {
    data.direction = solas::app::SwipeDirection::RIGHT;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft) {
    data.direction = solas::app::SwipeDirection::LEFT;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionUp) {
    data.direction = solas::app::SwipeDirection::UP;
  } else if (recognizer.direction == UISwipeGestureRecognizerDirectionDown) {
    data.direction = solas::app::SwipeDirection::DOWN;
  }
  data.touches = recognizer.numberOfTouchesRequired;
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::SWIPE data:data];
}

- (void)handlePanGesture:(UIPanGestureRecognizer *)recognizer {
  solas::app::GestureEvent::PanData data;
  CGPoint translation = [recognizer translationInView:self];
  data.translation.set(translation.x, translation.y);
  CGPoint velocity = [recognizer velocityInView:self];
  data.velocity.set(velocity.x, velocity.y);
  data.touches = recognizer.minimumNumberOfTouches;
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::PAN data:data];
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
  solas::app::GestureEvent::ScreenEdgeData data;
  if (edge == UIRectEdgeTop) {
    data.edge = solas::app::ScreenEdge::TOP;
  } else if (edge == UIRectEdgeLeft) {
    data.edge = solas::app::ScreenEdge::LEFT;
  } else if (edge == UIRectEdgeBottom) {
    data.edge = solas::app::ScreenEdge::BOTTOM;
  } else if (edge == UIRectEdgeRight) {
    data.edge = solas::app::ScreenEdge::RIGHT;
  }
  [self notifyGestureEventWithRecognizer:recognizer
      kind:solas::app::GestureKind::SCREEN_EDGE data:data];
}

#pragma mark UIGestureRecognizerDelegate

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
    shouldRecognizeSimultaneouslyWithGestureRecognizer:
        (UIGestureRecognizer *)otherGestureRecognizer {
  return YES;
}

@end
