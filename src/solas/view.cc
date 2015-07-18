//
//  solas/view.cc
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

#include "solas/view.h"

#include <cassert>

#include "solas/mouse_button.h"

namespace solas {

#pragma mark Event handlers

void View::handleMouseEvent(const MouseEvent& event) {
  if (event.type() == MouseEvent::Type::PRESSED ||
      event.type() == MouseEvent::Type::DRAGGED ||
      event.type() == MouseEvent::Type::MOVED) {
    pmouse_ = emouse_;
    mouse_ = event.location();
  }
  mouse_button_ = event.button();
  switch (event.type()) {
    case MouseEvent::Type::PRESSED:
      mouse_pressed_ = true;
      break;
    case MouseEvent::Type::RELEASED:
      mouse_pressed_ = false;
      break;
    default:
      break;
  }
  if (event.type() == MouseEvent::Type::DRAGGED ||
      event.type() == MouseEvent::Type::MOVED) {
    emouse_ = mouse_;
  }
  switch (event.type()) {
    case MouseEvent::Type::PRESSED:
      mousePressed(event);
      mousePressed();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::DRAGGED:
      mouseDragged(event);
      mouseDragged();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::RELEASED:
      mouseReleased(event);
      mouseReleased();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::MOVED:
      mouseMoved(event);
      mouseMoved();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::ENTERED:
      mouseEntered(event);
      mouseEntered();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::EXITED:
      mouseExited(event);
      mouseExited();
      mouse_event_signals_[event.type()](event);
      break;
    case MouseEvent::Type::WHEEL:
      mouseWheel(event);
      mouseWheel();
      mouse_event_signals_[event.type()](event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleKeyEvent(const KeyEvent& event) {
  switch (event.type()) {
    case KeyEvent::Type::PRESSED:
      keyPressed(event);
      keyPressed();
      key_event_signals_[event.type()](event);
      break;
    case KeyEvent::Type::RELEASED:
      keyReleased(event);
      keyReleased();
      key_event_signals_[event.type()](event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleTouchEvent(const TouchEvent& event) {
  if (event.type() == TouchEvent::Type::BEGAN) {
    ptouch_ = etouch_;
    touch_ = event.touches().front();
  } else if (event.type() == TouchEvent::Type::MOVED) {
    ptouch_ = etouch_;
    touch_ = event.touches().front();
  }
  switch (event.type()) {
    case TouchEvent::Type::BEGAN:
      touch_pressed_ = true;
      break;
    case TouchEvent::Type::CANCELLED:
    case TouchEvent::Type::ENDED:
      touch_pressed_ = false;
      break;
    default:
      break;
  }
  if (event.type() == TouchEvent::Type::BEGAN ||
      event.type() == TouchEvent::Type::MOVED) {
    etouch_ = touch_;
  }
  switch (event.type()) {
    case TouchEvent::Type::BEGAN:
      touchesBegan(event);
      touchesBegan();
      touch_event_signals_[event.type()](event);
      break;
    case TouchEvent::Type::MOVED:
      touchesMoved(event);
      touchesMoved();
      touch_event_signals_[event.type()](event);
      break;
    case TouchEvent::Type::CANCELLED:
      touchesCancelled(event);
      touchesCancelled();
      touch_event_signals_[event.type()](event);
      break;
    case TouchEvent::Type::ENDED:
      touchesEnded(event);
      touchesEnded();
      touch_event_signals_[event.type()](event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleGestureEvent(const GestureEvent& event) {
  switch (event.type()) {
    case GestureEvent::Type::BEGAN:
      gestureBegan(event);
      gestureBegan();
      gesture_event_signals_[event.type()](event);
      break;
    case GestureEvent::Type::CHANGED:
      gestureChanged(event);
      gestureChanged();
      gesture_event_signals_[event.type()](event);
      break;
    case GestureEvent::Type::CANCELLED:
      gestureCancelled(event);
      gestureCancelled();
      gesture_event_signals_[event.type()](event);
      break;
    case GestureEvent::Type::ENDED:
      gestureEnded(event);
      gestureEnded();
      gesture_event_signals_[event.type()](event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleMotionEvent(const MotionEvent& event) {
  switch (event.type()) {
    case MotionEvent::Type::BEGAN:
      motionBegan(event);
      motionBegan();
      motion_event_signals_[event.type()](event);
      break;
    case MotionEvent::Type::CANCELLED:
      motionCancelled(event);
      motionCancelled();
      motion_event_signals_[event.type()](event);
      break;
    case MotionEvent::Type::ENDED:
      motionEnded(event);
      motionEnded();
      motion_event_signals_[event.type()](event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

}  // namespace solas
