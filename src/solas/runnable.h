//
//  solas/runnable.h
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

#pragma once
#ifndef SOLAS_RUNNABLE_H_
#define SOLAS_RUNNABLE_H_

#include "solas/app_event.h"
#include "solas/backend.h"
#include "solas/context_holder.h"
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_event.h"
#include "solas/touch_event.h"

namespace solas {

class Runnable {
 private:
  friend class Runner;

 public:
  virtual ~Runnable() = 0;

 protected:
  // Lifecycle
  virtual void setup(const AppEvent& event);
  virtual void update(const AppEvent& event);
  virtual void pre(const AppEvent& event);
  virtual void draw(const AppEvent& event);
  virtual void post(const AppEvent& event);
  virtual void exit(const AppEvent& event);

  // Events
  virtual void mousePressed(const MouseEvent& event) {}
  virtual void mouseDragged(const MouseEvent& event) {}
  virtual void mouseReleased(const MouseEvent& event) {}
  virtual void mouseMoved(const MouseEvent& event) {}
  virtual void mouseEntered(const MouseEvent& event) {}
  virtual void mouseExited(const MouseEvent& event) {}
  virtual void mouseWheel(const MouseEvent& event) {}
  virtual void keyPressed(const KeyEvent& event) {}
  virtual void keyReleased(const KeyEvent& event) {}
  virtual void touchesBegan(const TouchEvent& event) {}
  virtual void touchesMoved(const TouchEvent& event) {}
  virtual void touchesCancelled(const TouchEvent& event) {}
  virtual void touchesEnded(const TouchEvent& event) {}
  virtual void gestureBegan(const GestureEvent& event) {}
  virtual void gestureChanged(const GestureEvent& event) {}
  virtual void gestureCancelled(const GestureEvent& event) {}
  virtual void gestureEnded(const GestureEvent& event) {}
  virtual void motionBegan(const MotionEvent& event) {}
  virtual void motionCancelled(const MotionEvent& event) {}
  virtual void motionEnded(const MotionEvent& event) {}

  // Context
  const ContextHolder& context() const;

 private:
  ContextHolder context_;
};

#pragma mark -

inline Runnable::~Runnable() {}

#pragma mark Lifecycle

inline void Runnable::setup(const AppEvent& event) {
  context_ = event.context();
  setup();
}

inline void Runnable::update(const AppEvent& event) {
  context_ = event.context();
  update();
}

inline void Runnable::pre(const AppEvent& event) {
  context_ = event.context();
  pre();
}

inline void Runnable::draw(const AppEvent& event) {
  context_ = event.context();
  draw();
}

inline void Runnable::post(const AppEvent& event) {
  context_ = event.context();
  post();
}

inline void Runnable::exit(const AppEvent& event) {
  context_ = event.context();
  exit();
}

#pragma mark Context

inline const ContextHolder& Runnable::context() const {
  return context_;
}

}  // namespace solas

#endif  // SOLAS_RUNNABLE_H_
