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

#include <string>

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

- (BOOL)mouseDownCanMoveWindow {
  return YES;
}

#pragma mark Responding to Events

- (void)mouseDown:(NSEvent *)event {
  [self notifyMousePressedWithEvent:event];
  [super mouseDown:event];
}

- (void)rightMouseDown:(NSEvent *)event {
  [self notifyMousePressedWithEvent:event];
  [super rightMouseDown:event];
}

- (void)otherMouseDown:(NSEvent *)event {
  [self notifyMousePressedWithEvent:event];
  [super otherMouseDown:event];
}

- (void)mouseUp:(NSEvent *)event {
  [self notifyMouseReleasedWithEvent:event];
  [super mouseUp:event];
}

- (void)rightMouseUp:(NSEvent *)event {
  [self notifyMouseReleasedWithEvent:event];
  [super rightMouseUp:event];
}

- (void)otherMouseUp:(NSEvent *)event {
  [self notifyMouseReleasedWithEvent:event];
  [super otherMouseUp:event];
}

- (void)mouseDragged:(NSEvent *)event {
  [self notifyMouseDraggedWithEvent:event];
  [super mouseDragged:event];
}

- (void)rightMouseDragged:(NSEvent *)event {
  [self notifyMouseDraggedWithEvent:event];
  [super rightMouseDragged:event];
}

- (void)otherMouseDragged:(NSEvent *)event {
  [self notifyMouseDraggedWithEvent:event];
  [super otherMouseDragged:event];
}

- (void)mouseMoved:(NSEvent *)event {
  [self notifyMouseMovedWithEvent:event];
  [super mouseMoved:event];
}

- (void)mouseEntered:(NSEvent *)event {
  [self notifyMouseEnteredWithEvent:event];
  [super mouseEntered:event];
}

- (void)mouseExited:(NSEvent *)event {
  [self notifyMouseExitedWithEvent:event];
  [super mouseExited:event];
}

- (void)scrollWheel:(NSEvent *)event {
  [self notifyMouseWheelWithEvent:event];
  [super scrollWheel:event];
}

- (void)keyDown:(NSEvent *)event {
  [self notifyKeyPressedWithEvent:event];
  [super keyDown:event];
}

- (void)keyUp:(NSEvent *)event {
  [self notifyKeyReleasedWithEvent:event];
  [super keyUp:event];
}

- (void)touchesBeganWithEvent:(NSEvent *)event {
  [self notifyTouchesBeganWithEvent:event];
  [super touchesBeganWithEvent:event];
}

- (void)touchesMovedWithEvent:(NSEvent *)event {
  [self notifyTouchesMovedWithEvent:event];
  [super touchesMovedWithEvent:event];
}

- (void)touchesCancelledWithEvent:(NSEvent *)event {
  [self notifyTouchesCancelledWithEvent:event];
  [super touchesCancelledWithEvent:event];
}

- (void)touchesEndedWithEvent:(NSEvent *)event {
  [self notifyTouchesEndedWithEvent:event];
  [super touchesEndedWithEvent:event];
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
  return solas::KeyEvent(
      type,
      event.keyCode,
      std::string(event.characters.UTF8String),
      [self keyModifiersForEvent:event]);
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

- (void)notifyMousePressedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mousePressed:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::PRESSED]);
    [_eventDelegate eventDelegate:self
                     mousePressed:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseDraggedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseDragged:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::DRAGGED]);
    [_eventDelegate eventDelegate:self
                     mouseDragged:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseReleasedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseReleased:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::RELEASED]);
    [_eventDelegate eventDelegate:self
                    mouseReleased:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseMovedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseMoved:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::MOVED]);
    [_eventDelegate eventDelegate:self
                       mouseMoved:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseEnteredWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseEntered:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::ENTERED]);
    [_eventDelegate eventDelegate:self
                     mouseEntered:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseExitedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseExited:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::EXITED]);
    [_eventDelegate eventDelegate:self
                      mouseExited:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyMouseWheelWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:mouseWheel:)]) {
    const auto mouseEvent([self mouseEventWithEvent:event
        type:solas::MouseEvent::Type::WHEEL]);
    [_eventDelegate eventDelegate:self
                       mouseWheel:SLSMouseEventMake(&mouseEvent)];
  }
}

- (void)notifyKeyPressedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:keyPressed:)]) {
    const auto keyEvent([self keyEventWithEvent:event
        type:solas::KeyEvent::Type::PRESSED]);
    [_eventDelegate eventDelegate:self
                       keyPressed:SLSKeyEventMake(&keyEvent)];
  }
}

- (void)notifyKeyReleasedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:keyReleased:)]) {
    const auto keyEvent([self keyEventWithEvent:event
        type:solas::KeyEvent::Type::RELEASED]);
    [_eventDelegate eventDelegate:self
                      keyReleased:SLSKeyEventMake(&keyEvent)];
  }
}

- (void)notifyTouchesBeganWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesBegan:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::BEGAN]);
    [_eventDelegate eventDelegate:self
                     touchesBegan:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesMovedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesMoved:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::MOVED]);
    [_eventDelegate eventDelegate:self
                     touchesMoved:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesCancelledWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesCancelled:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::CANCELLED]);
    [_eventDelegate eventDelegate:self
                 touchesCancelled:SLSTouchEventMake(&touchEvent)];
  }
}

- (void)notifyTouchesEndedWithEvent:(id)event {
  if ([_eventDelegate respondsToSelector:
          @selector(eventDelegate:touchesEnded:)]) {
    const auto touchEvent([self touchEventWithEvent:event
        type:solas::TouchEvent::Type::ENDED]);
    [_eventDelegate eventDelegate:self
                     touchesEnded:SLSTouchEventMake(&touchEvent)];
  }
}

@end
