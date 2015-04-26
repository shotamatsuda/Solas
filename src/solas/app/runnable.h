//
//  solas/app/runnable.h
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

#pragma once
#ifndef SOLAS_APP_RUNNABLE_H_
#define SOLAS_APP_RUNNABLE_H_

#include "solas/app/app_event.h"
#include "solas/app/backend.h"
#include "solas/app/context_holder.h"
#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/touch_event.h"

namespace solas {
namespace app {

class Runnable {
 private:
  friend class Runner;

 public:
  // Constructors
  virtual ~Runnable() = 0;

 protected:
  // Lifecycle
  virtual void setup(const AppEvent& event);
  virtual void setup() {}
  virtual void update(const AppEvent& event);
  virtual void update() {}
  virtual void draw(const AppEvent& event);
  virtual void draw() {}
  virtual void post(const AppEvent& event);
  virtual void post() {}
  virtual void exit(const AppEvent& event);
  virtual void exit() {}

  // Events
  virtual void mouseDown(const MouseEvent& event) {}
  virtual void mouseDrag(const MouseEvent& event) {}
  virtual void mouseUp(const MouseEvent& event) {}
  virtual void mouseMove(const MouseEvent& event) {}
  virtual void mouseEnter(const MouseEvent& event) {}
  virtual void mouseExit(const MouseEvent& event) {}
  virtual void scrollWheel(const MouseEvent& event) {}
  virtual void keyDown(const KeyEvent& event) {}
  virtual void keyUp(const KeyEvent& event) {}
  virtual void touchesBegin(const TouchEvent& event) {}
  virtual void touchesMove(const TouchEvent& event) {}
  virtual void touchesCancel(const TouchEvent& event) {}
  virtual void touchesEnd(const TouchEvent& event) {}
  virtual void motionBegin(const MotionEvent& event) {}
  virtual void motionCancel(const MotionEvent& event) {}
  virtual void motionEnd(const MotionEvent& event) {}

  // Backend
  virtual Backend backend() const;

  // Context
  const ContextHolder& context() const;

 private:
  ContextHolder context_;
};

#pragma mark -

inline Runnable::~Runnable() {}

#pragma mark Lifecycle

inline void Runnable::setup(const AppEvent& event) {
  context_ = event.context;
  setup();
}

inline void Runnable::update(const AppEvent& event) {
  context_ = event.context;
  update();
}

inline void Runnable::draw(const AppEvent& event) {
  context_ = event.context;
  draw();
}

inline void Runnable::post(const AppEvent& event) {
  context_ = event.context;
  post();
}

inline void Runnable::exit(const AppEvent& event) {
  context_ = event.context;
  exit();
}

#pragma mark Backend

inline Backend Runnable::backend() const {
  return (Backend)(Backend::OPENGL2 | Backend::OPENGLES3);
}

#pragma mark Context

inline const ContextHolder& Runnable::context() const {
  return context_;
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUNNABLE_H_
