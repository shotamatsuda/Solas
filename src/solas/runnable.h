//
//  solas/runnable.h
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_event.h"
#include "solas/touch_event.h"

namespace solas {

class Runner;

class Runnable {
 private:
  friend class Runner;

 public:
  virtual ~Runnable() = 0;

 protected:
  // Lifecycle
  virtual void setup(const AppEvent& event, const Runner&) = 0;
  virtual void update(const AppEvent& event, const Runner&) = 0;
  virtual void pre(const AppEvent& event, const Runner&) = 0;
  virtual void draw(const AppEvent& event, const Runner&) = 0;
  virtual void post(const AppEvent& event, const Runner&) = 0;
  virtual void exit(const AppEvent& event, const Runner&) = 0;

  // Events
  virtual void mousePressed(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseDragged(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseReleased(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseMoved(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseEntered(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseExited(const MouseEvent& event, const Runner&) = 0;
  virtual void mouseWheel(const MouseEvent& event, const Runner&) = 0;
  virtual void keyPressed(const KeyEvent& event, const Runner&) = 0;
  virtual void keyReleased(const KeyEvent& event, const Runner&) = 0;
  virtual void touchesBegan(const TouchEvent& event, const Runner&) = 0;
  virtual void touchesMoved(const TouchEvent& event, const Runner&) = 0;
  virtual void touchesCancelled(const TouchEvent& event, const Runner&) = 0;
  virtual void touchesEnded(const TouchEvent& event, const Runner&) = 0;
  virtual void gestureBegan(const GestureEvent& event, const Runner&) = 0;
  virtual void gestureChanged(const GestureEvent& event, const Runner&) = 0;
  virtual void gestureCancelled(const GestureEvent& event, const Runner&) = 0;
  virtual void gestureEnded(const GestureEvent& event, const Runner&) = 0;
  virtual void motionBegan(const MotionEvent& event, const Runner&) = 0;
  virtual void motionCancelled(const MotionEvent& event, const Runner&) = 0;
  virtual void motionEnded(const MotionEvent& event, const Runner&) = 0;
};

#pragma mark -

inline Runnable::~Runnable() {}

}  // namespace solas

#endif  // SOLAS_RUNNABLE_H_
