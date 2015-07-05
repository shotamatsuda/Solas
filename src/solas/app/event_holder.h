//
//  solas/app/event_holder.h
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
#ifndef SOLAS_APP_EVENT_HOLDER_H_
#define SOLAS_APP_EVENT_HOLDER_H_

#include <cassert>

#include <boost/any.hpp>

#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"

namespace solas {
namespace app {

class EventHolder final {
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
  explicit EventHolder(const MouseEvent& event);
  explicit EventHolder(const KeyEvent& event);
  explicit EventHolder(const TouchEvent& event);
  explicit EventHolder(const GestureEvent& event);
  explicit EventHolder(const MotionEvent& event);

  // Copy and move
  EventHolder(const EventHolder& other) = default;
  EventHolder(EventHolder&& other) = default;

  // Disallow assign
  EventHolder& operator=(const EventHolder& other) = delete;

  // Properties
  Type type() const { return type_; }

  // Accessing the event
  const MouseEvent& mouse() const;
  const KeyEvent& key() const;
  const TouchEvent& touch() const;
  const GestureEvent& gesture() const;
  const MotionEvent& motion() const;

 private:
  Type type_;
  boost::any event_;
};

#pragma mark -

inline EventHolder::EventHolder(const MouseEvent& event)
    : type_(Type::MOUSE),
      event_(event) {}

inline EventHolder::EventHolder(const KeyEvent& event)
    : type_(Type::KEY),
      event_(event) {}

inline EventHolder::EventHolder(const TouchEvent& event)
    : type_(Type::TOUCH),
      event_(event) {}

inline EventHolder::EventHolder(const GestureEvent& event)
    : type_(Type::GESTURE),
      event_(event) {}

inline EventHolder::EventHolder(const MotionEvent& event)
    : type_(Type::MOTION),
      event_(event) {}

#pragma mark Accessing the event

inline const MouseEvent& EventHolder::mouse() const {
  assert(type_ == Type::MOUSE);
  return *boost::any_cast<MouseEvent>(&event_);
}

inline const KeyEvent& EventHolder::key() const {
  assert(type_ == Type::KEY);
  return *boost::any_cast<KeyEvent>(&event_);
}

inline const TouchEvent& EventHolder::touch() const {
  assert(type_ == Type::TOUCH);
  return *boost::any_cast<TouchEvent>(&event_);
}

inline const GestureEvent& EventHolder::gesture() const {
  assert(type_ == Type::GESTURE);
  return *boost::any_cast<GestureEvent>(&event_);
}

inline const MotionEvent& EventHolder::motion() const {
  assert(type_ == Type::MOTION);
  return *boost::any_cast<MotionEvent>(&event_);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_EVENT_HOLDER_H_
