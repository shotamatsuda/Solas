//
//  solas/app/runnable.h
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
  virtual void pre(const AppEvent& event);
  virtual void pre() {}
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
  virtual void gestureBegin(const GestureEvent& event) {}
  virtual void gestureChange(const GestureEvent& event) {}
  virtual void gestureCancel(const GestureEvent& event) {}
  virtual void gestureEnd(const GestureEvent& event) {}
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

#pragma mark Backend

inline Backend Runnable::backend() const {
  return Backend::OPENGL2 | Backend::OPENGLES2;
}

#pragma mark Context

inline const ContextHolder& Runnable::context() const {
  return context_;
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUNNABLE_H_
