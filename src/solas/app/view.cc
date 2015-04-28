//
//  solas/app/view.cc
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

#include "solas/app/view.h"

#include <cassert>

#include "solas/app/mouse_button.h"

namespace solas {
namespace app {

#pragma mark Event handlers

void View::handleMouseEvent(const MouseEvent& event) {
  if (event.type == MouseEvent::Type::DOWN ||
      event.type == MouseEvent::Type::DRAG ||
      event.type == MouseEvent::Type::MOVE) {
    pmouse_ = emouse_;
    mouse_ = event.location;
  }
  mouse_button_ = event.button;
  switch (event.type) {
    case MouseEvent::Type::DOWN:
      mouse_pressed_ = true;
      break;
    case MouseEvent::Type::UP:
      mouse_pressed_ = false;
      break;
    default:
      break;
  }
  if (event.type == MouseEvent::Type::DRAG ||
      event.type == MouseEvent::Type::MOVE) {
    emouse_ = mouse_;
  }
  switch (event.type) {
    case MouseEvent::Type::DOWN:
      mousePressed(event);
      break;
    case MouseEvent::Type::DRAG:
      mouseDragged(event);
      break;
    case MouseEvent::Type::UP:
      mouseReleased(event);
      break;
    case MouseEvent::Type::MOVE:
      mouseMoved(event);
      break;
    case MouseEvent::Type::ENTER:
      mouseEntered(event);
      break;
    case MouseEvent::Type::EXIT:
      mouseExited(event);
      break;
    case MouseEvent::Type::WHEEL:
      mouseWheel(event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleKeyEvent(const KeyEvent& event) {
  switch (event.type) {
    case KeyEvent::Type::DOWN:
      keyPressed(event);
      break;
    case KeyEvent::Type::UP:
      keyReleased(event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleTouchEvent(const TouchEvent& event) {
  if (event.type == TouchEvent::Type::BEGIN ||
      event.type == TouchEvent::Type::MOVE) {
    ptouch_ = etouch_;
    touch_ = event.touches.front();
  }
  switch (event.type) {
    case TouchEvent::Type::BEGIN:
      touch_pressed_ = true;
      break;
    case TouchEvent::Type::CANCEL:
    case TouchEvent::Type::END:
      touch_pressed_ = false;
      break;
    default:
      break;
  }
  if (event.type == TouchEvent::Type::MOVE) {
    etouch_ = touch_;
  }
  switch (event.type) {
    case TouchEvent::Type::BEGIN:
      touchesBegan(event);
      break;
    case TouchEvent::Type::MOVE:
      touchesMoved(event);
      break;
    case TouchEvent::Type::CANCEL:
      touchesCancelled(event);
      break;
    case TouchEvent::Type::END:
      touchesEnded(event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleGestureEvent(const GestureEvent& event) {
  switch (event.type) {
    case GestureEvent::Type::BEGIN:
      gestureBegan(event);
      break;
    case GestureEvent::Type::CHANGE:
      gestureChanged(event);
      break;
    case GestureEvent::Type::CANCEL:
      gestureCancelled(event);
      break;
    case GestureEvent::Type::END:
      gestureEnded(event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleMotionEvent(const MotionEvent& event) {
  switch (event.type) {
    case MotionEvent::Type::BEGIN:
      motionBegan(event);
      break;
    case MotionEvent::Type::CANCEL:
      motionCancelled(event);
      break;
    case MotionEvent::Type::END:
      motionEnded(event);
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

}  // namespace app
}  // namespace solas
