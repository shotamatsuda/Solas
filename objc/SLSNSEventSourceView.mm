//
//  SLSNSEventSourceView.mm
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

#import "SLSNSEventSourceView.h"

#import "SLSEvents.h"

#include <utility>

#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/key_modifier.h"
#include "solas/mouse_button.h"
#include "solas/mouse_event.h"
#include "solas/touch_event.h"
#include "solas/math.h"

@interface SLSNSEventSourceView ()

#pragma mark Initialization

@property (nonatomic, strong) NSTrackingArea *trackingArea;

- (void)setUpTrackingArea;

#pragma mark Creating Events

- (solas::MouseEvent)mouseEventWithEvent:(NSEvent *)event
    type:(solas::MouseEvent::Type)type;
- (solas::KeyEvent)keyEventWithEvent:(NSEvent *)event
    type:(solas::KeyEvent::Type)type;
- (solas::TouchEvent)touchEventWithEvent:(NSEvent *)event
    type:(solas::TouchEvent::Type)type;
- (solas::KeyModifier)keyModifiersForEvent:(NSEvent *)event;

@end

@implementation SLSNSEventSourceView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.acceptsTouchEvents = YES;
    [self setUpTrackingArea];
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    self.acceptsTouchEvents = YES;
    [self setUpTrackingArea];
  }
  return self;
}

- (void)setFrameSize:(CGSize)size {
  [super setFrameSize:size];
  [self setUpTrackingArea];
}

- (BOOL)isFlipped {
  return YES;
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

#pragma mark Responding to Events

- (void)mouseDown:(NSEvent *)event {
  [self notifyMouseDownWithEvent:event];
}

- (void)rightMouseDown:(NSEvent *)event {
  [self notifyMouseDownWithEvent:event];
}

- (void)otherMouseDown:(NSEvent *)event {
  [self notifyMouseDownWithEvent:event];
}

- (void)mouseUp:(NSEvent *)event {
  [self notifyMouseUpWithEvent:event];
}

- (void)rightMouseUp:(NSEvent *)event {
  [self notifyMouseUpWithEvent:event];
}

- (void)otherMouseUp:(NSEvent *)event {
  [self notifyMouseUpWithEvent:event];
}

- (void)mouseDragged:(NSEvent *)event {
  [self notifyMouseDragWithEvent:event];
}

- (void)rightMouseDragged:(NSEvent *)event {
  [self notifyMouseDragWithEvent:event];
}

- (void)otherMouseDragged:(NSEvent *)event {
  [self notifyMouseDragWithEvent:event];
}

- (void)mouseMoved:(NSEvent *)event {
  [self notifyMouseMoveWithEvent:event];
}

- (void)mouseEntered:(NSEvent *)event {
  [self notifyMouseEnterWithEvent:event];
}

- (void)mouseExited:(NSEvent *)event {
  [self notifyMouseExitWithEvent:event];
}

- (void)scrollWheel:(NSEvent *)event {
  [self notifyScrollWheelWithEvent:event];
}

- (void)keyDown:(NSEvent *)event {
  [self notifyKeyDownWithEvent:event];
}

- (void)keyUp:(NSEvent *)event {
  [self notifyKeyUpWithEvent:event];
}

- (void)touchesBeganWithEvent:(NSEvent *)event {
  [self notifyTouchesBeginWithEvent:event];
}

- (void)touchesMovedWithEvent:(NSEvent *)event {
  [self notifyTouchesMoveWithEvent:event];
}

- (void)touchesCancelledWithEvent:(NSEvent *)event {
  [self notifyTouchesCancelWithEvent:event];
}

- (void)touchesEndedWithEvent:(NSEvent *)event {
  [self notifyTouchesEndWithEvent:event];
}

#pragma mark Initialization

- (void)setUpTrackingArea {
  if (_trackingArea) {
    [self removeTrackingArea:_trackingArea];
  }
  _trackingArea = [[NSTrackingArea alloc]
      initWithRect:self.bounds
           options:(NSTrackingMouseEnteredAndExited |
                    NSTrackingMouseMoved |
                    NSTrackingActiveInKeyWindow)
             owner:self
          userInfo:nil];
  [self addTrackingArea:_trackingArea];
}

#pragma mark Creating Events

- (solas::MouseEvent)mouseEventWithEvent:(NSEvent *)event
    type:(solas::MouseEvent::Type)type {
  CGPoint location = [self convertPoint:event.locationInWindow
                               fromView:self.window.contentView];
  return solas::MouseEvent(
      type,
      solas::Vec2d(location.x, location.y),
      static_cast<solas::MouseButton>(event.buttonNumber),
      [self keyModifiersForEvent:event],
      solas::Vec3d(event.deltaX, event.deltaY, event.deltaZ));
}

- (solas::KeyEvent)keyEventWithEvent:(NSEvent *)event
    type:(solas::KeyEvent::Type)type {
  return solas::KeyEvent();
}

- (solas::TouchEvent)touchEventWithEvent:(NSEvent *)event
    type:(solas::TouchEvent::Type)type {
  return solas::TouchEvent();
}

- (solas::KeyModifier)keyModifiersForEvent:(NSEvent *)event {
  NSEventModifierFlags flags = event.modifierFlags;
  solas::KeyModifier modifiers = solas::KeyModifier::NONE;
  if (flags & NSAlphaShiftKeyMask) {
    modifiers |= solas::KeyModifier::CAPS;
  }
  if (flags & NSShiftKeyMask) {
    modifiers |= solas::KeyModifier::SHIFT;
  }
  if (flags & NSControlKeyMask) {
    modifiers |= solas::KeyModifier::CONTROL;
  }
  if (flags & NSAlternateKeyMask) {
    modifiers |= solas::KeyModifier::ALTERNATE;
  }
  if (flags & NSCommandKeyMask) {
    modifiers |= solas::KeyModifier::COMMAND;
  }
  if (flags & NSFunctionKeyMask) {
    modifiers |= solas::KeyModifier::FUNCTION;
  }
  return modifiers;
}

#pragma mark Notifying Events to the Delegate

- (void)notifyMouseDownWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseDown:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::DOWN]);
    [_eventDelegate eventDelegate:self
                        mouseDown:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseDragWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseDrag:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::DRAG]);
    [_eventDelegate eventDelegate:self
                        mouseDrag:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseUpWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseUp:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::UP]);
    [_eventDelegate eventDelegate:self
                          mouseUp:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseMoveWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseMove:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::MOVE]);
    [_eventDelegate eventDelegate:self
                        mouseMove:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseEnterWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseEnter:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::ENTER]);
    [_eventDelegate eventDelegate:self
                       mouseEnter:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseExitWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseExit:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::EXIT]);
    [_eventDelegate eventDelegate:self
                        mouseExit:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyScrollWheelWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:scrollWheel:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::WHEEL]);
    [_eventDelegate eventDelegate:self
                      scrollWheel:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyKeyDownWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:keyDown:)]) {
    const auto keyEvent([self keyEventWithEvent:event
        type:solas::KeyEvent::Type::DOWN]);
    [_eventDelegate eventDelegate:self
                          keyDown:SLSKeyEventMake(&keyEvent)];
  }
}

- (void)notifyKeyUpWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:keyUp:)]) {
    const auto keyEvent([self keyEventWithEvent:event
        type:solas::KeyEvent::Type::UP]);
    [_eventDelegate eventDelegate:self
                            keyUp:SLSKeyEventMake(&keyEvent)];
  }
}

- (void)notifyTouchesBeginWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesBegin:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::BEGIN]);
    [_eventDelegate eventDelegate:self
                     touchesBegin:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesMoveWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesMove:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::MOVE]);
    [_eventDelegate eventDelegate:self
                      touchesMove:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesCancelWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesCancel:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::CANCEL]);
    [_eventDelegate eventDelegate:self
                    touchesCancel:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesEndWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesEnd:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::END]);
    [_eventDelegate eventDelegate:self
                       touchesEnd:SLSTouchEventMake(&touchEvent)];
  }
}

@end
