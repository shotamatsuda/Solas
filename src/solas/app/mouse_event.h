//
//  solas/app/mouse_event.h
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
#ifndef SOLAS_APP_MOUSE_EVENT_H_
#define SOLAS_APP_MOUSE_EVENT_H_

#include <cstdint>

#include "solas/app/key_modifier.h"
#include "solas/app/mouse_button.h"
#include "takram/math/vector.h"

namespace solas {
namespace app {

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
  // Constructors
  MouseEvent();
  MouseEvent(Type type,
             const takram::math::Vec2d& location,
             MouseButton button,
             KeyModifier modifiers,
             const takram::math::Vec3d& wheel = takram::math::Vec3d());

  // Copy and move
  MouseEvent(const MouseEvent& other) = default;
  MouseEvent(MouseEvent&& other) = default;

  // Disallow assign
  MouseEvent& operator=(const MouseEvent& other) = delete;

  // Attributes
  bool empty() const { return type_ == Type::UNDEFINED; }

  // Properties
  Type type() const { return type_; }
  const takram::math::Vec2d& location() const { return location_; }
  MouseButton button() const { return button_; }
  KeyModifier modifiers() const { return modifiers_; }
  const takram::math::Vec3d& wheel() const { return wheel_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  takram::math::Vec2d location_;
  MouseButton button_;
  KeyModifier modifiers_;
  takram::math::Vec3d wheel_;
};

#pragma mark -

inline MouseEvent::MouseEvent()
    : type_(Type::UNDEFINED),
      button_(MouseButton::UNDEFINED),
      modifiers_(KeyModifier::NONE) {}

inline MouseEvent::MouseEvent(Type type,
                              const takram::math::Vec2d& location,
                              MouseButton button,
                              KeyModifier modifiers,
                              const takram::math::Vec3d& wheel)
    : type_(type),
      location_(location),
      button_(button),
      modifiers_(modifiers),
      wheel_(wheel) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_MOUSE_EVENT_H_
