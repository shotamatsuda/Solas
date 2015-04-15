//
//  solas/app/event.h
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
#ifndef SOLAS_APP_EVENT_H_
#define SOLAS_APP_EVENT_H_

#include <cassert>

#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"

namespace solas {
namespace app {

class Event {
 public:
  enum class Type {
    MOUSE,
    KEY,
    TOUCH,
    GESTURE,
    MOTION
  };

 public:
  // Constructors
  explicit Event(const MouseEvent& event);
  explicit Event(const KeyEvent& event);
  explicit Event(const TouchEvent& event);
  explicit Event(const GestureEvent& event);
  explicit Event(const MotionEvent& event);

  // Copy and move
  Event(const Event& other) = default;
  Event(Event&& other) = default;

  // Disallow assign
  Event& operator=(const Event& other) = delete;

  // Accessing the event
  const MouseEvent& mouse() const;
  const KeyEvent& key() const;
  const TouchEvent& touch() const;
  const GestureEvent& gesture() const;
  const MotionEvent& motion() const;

 public:
  const Type type;

 private:
  MouseEvent mouse_;
  KeyEvent key_;
  TouchEvent touch_;
  GestureEvent gesture_;
  MotionEvent motion_;
};

#pragma mark -

inline Event::Event(const MouseEvent& event)
    : type(Type::MOUSE),
      mouse_(event) {}

inline Event::Event(const KeyEvent& event)
    : type(Type::KEY),
      key_(event) {}

inline Event::Event(const TouchEvent& event)
    : type(Type::TOUCH),
      touch_(event) {}

inline Event::Event(const GestureEvent& event)
    : type(Type::GESTURE),
      gesture_(event) {}

inline Event::Event(const MotionEvent& event)
    : type(Type::MOTION),
      motion_(event) {}

#pragma mark Accessing the event

inline const MouseEvent& Event::mouse() const {
  assert(type == Type::MOUSE);
  return mouse_;
}

inline const KeyEvent& Event::key() const {
  assert(type == Type::KEY);
  return key_;
}

inline const TouchEvent& Event::touch() const {
  assert(type == Type::TOUCH);
  return touch_;
}

inline const GestureEvent& Event::gesture() const {
  assert(type == Type::GESTURE);
  return gesture_;
}

inline const MotionEvent& Event::motion() const {
  assert(type == Type::MOTION);
  return motion_;
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_EVENT_H_
