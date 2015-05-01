//
//  solas/app/view.cc
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

#include "solas/app/view.h"

#include <cassert>

#include "solas/app/mouse_button.h"

namespace solas {
namespace app {

#pragma mark Event handlers

void View::handleMouseEvent(const MouseEvent& event) {
  if (event.type() == MouseEvent::Type::DOWN ||
      event.type() == MouseEvent::Type::DRAG ||
      event.type() == MouseEvent::Type::MOVE) {
    pmouse_ = emouse_;
    mouse_ = event.location();
  }
  mouse_button_ = event.button();
  switch (event.type()) {
    case MouseEvent::Type::DOWN:
      mouse_pressed_ = true;
      break;
    case MouseEvent::Type::UP:
      mouse_pressed_ = false;
      break;
    default:
      break;
  }
  if (event.type() == MouseEvent::Type::DRAG ||
      event.type() == MouseEvent::Type::MOVE) {
    emouse_ = mouse_;
  }
  switch (event.type()) {
    case MouseEvent::Type::DOWN:
      mousePressed(event);
      mousePressed();
      break;
    case MouseEvent::Type::DRAG:
      mouseDragged(event);
      mouseDragged();
      break;
    case MouseEvent::Type::UP:
      mouseReleased(event);
      mouseReleased();
      break;
    case MouseEvent::Type::MOVE:
      mouseMoved(event);
      mouseMoved();
      break;
    case MouseEvent::Type::ENTER:
      mouseEntered(event);
      mouseEntered();
      break;
    case MouseEvent::Type::EXIT:
      mouseExited(event);
      mouseExited();
      break;
    case MouseEvent::Type::WHEEL:
      mouseWheel(event);
      mouseWheel();
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleKeyEvent(const KeyEvent& event) {
  switch (event.type()) {
    case KeyEvent::Type::DOWN:
      keyPressed(event);
      keyPressed();
      break;
    case KeyEvent::Type::UP:
      keyReleased(event);
      keyReleased();
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleTouchEvent(const TouchEvent& event) {
  if (event.type() == TouchEvent::Type::BEGIN ||
      event.type() == TouchEvent::Type::MOVE) {
    ptouch_ = etouch_;
    touch_ = event.touches().front();
  }
  switch (event.type()) {
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
  if (event.type() == TouchEvent::Type::MOVE) {
    etouch_ = touch_;
  }
  switch (event.type()) {
    case TouchEvent::Type::BEGIN:
      touchesBegan(event);
      touchesBegan();
      break;
    case TouchEvent::Type::MOVE:
      touchesMoved(event);
      touchesMoved();
      break;
    case TouchEvent::Type::CANCEL:
      touchesCancelled(event);
      touchesCancelled();
      break;
    case TouchEvent::Type::END:
      touchesEnded(event);
      touchesEnded();
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleGestureEvent(const GestureEvent& event) {
  switch (event.type()) {
    case GestureEvent::Type::BEGIN:
      gestureBegan(event);
      gestureBegan();
      break;
    case GestureEvent::Type::CHANGE:
      gestureChanged(event);
      gestureChanged();
      break;
    case GestureEvent::Type::CANCEL:
      gestureCancelled(event);
      gestureCancelled();
      break;
    case GestureEvent::Type::END:
      gestureEnded(event);
      gestureEnded();
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

void View::handleMotionEvent(const MotionEvent& event) {
  switch (event.type()) {
    case MotionEvent::Type::BEGIN:
      motionBegan(event);
      motionBegan();
      break;
    case MotionEvent::Type::CANCEL:
      motionCancelled(event);
      motionCancelled();
      break;
    case MotionEvent::Type::END:
      motionEnded(event);
      motionEnded();
      break;
    default:
      break;  // Ignore unknown types of event
  }
}

}  // namespace app
}  // namespace solas
