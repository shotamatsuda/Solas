//
//  solas/mouse_event.h
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
#ifndef SOLAS_MOUSE_EVENT_H_
#define SOLAS_MOUSE_EVENT_H_

#include <cstdint>

#include "solas/key_modifier.h"
#include "solas/mouse_button.h"
#include "solas/math.h"

namespace solas {

class MouseEvent final {
 public:
  enum class Type {
    UNDEFINED,
    DOWN,
    DRAG,
    UP,
    MOVE,
    ENTER,
    EXIT,
    WHEEL
  };

 public:
  MouseEvent();
  MouseEvent(Type type,
             const Vec2d& location,
             MouseButton button,
             KeyModifier modifiers,
             const Vec3d& wheel = Vec3d());

  // Copy semantics excluding assignment
  MouseEvent(const MouseEvent& other) = default;
  MouseEvent& operator=(const MouseEvent& other) = delete;

  // Properties
  bool empty() const { return type_ == Type::UNDEFINED; }
  Type type() const { return type_; }
  const Vec2d& location() const { return location_; }
  MouseButton button() const { return button_; }
  KeyModifier modifiers() const { return modifiers_; }
  const Vec3d& wheel() const { return wheel_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  Vec2d location_;
  MouseButton button_;
  KeyModifier modifiers_;
  Vec3d wheel_;
};

#pragma mark -

inline MouseEvent::MouseEvent()
    : type_(Type::UNDEFINED),
      button_(MouseButton::UNDEFINED),
      modifiers_(KeyModifier::NONE) {}

inline MouseEvent::MouseEvent(Type type,
                              const Vec2d& location,
                              MouseButton button,
                              KeyModifier modifiers,
                              const Vec3d& wheel)
    : type_(type),
      location_(location),
      button_(button),
      modifiers_(modifiers),
      wheel_(wheel) {}

}  // namespace solas

#endif  // SOLAS_MOUSE_EVENT_H_
