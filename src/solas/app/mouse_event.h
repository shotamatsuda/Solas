//
//  solas/app/mouse_event.h
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
#ifndef SOLAS_APP_MOUSE_EVENT_H_
#define SOLAS_APP_MOUSE_EVENT_H_

#include <cstdint>

#include "solas/app/key_modifier.h"
#include "solas/app/mouse_button.h"
#include "solas/math/vector.h"

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
             const math::Vec2d& location,
             MouseButton button,
             KeyModifier modifiers,
             const math::Vec3d& wheel = math::Vec3d());

  // Copy and move
  MouseEvent(const MouseEvent& other) = default;
  MouseEvent(MouseEvent&& other) = default;

  // Disallow assign
  MouseEvent& operator=(const MouseEvent& other) = delete;

  // Attributes
  bool empty() const { return type_ == Type::UNDEFINED; }

  // Properties
  Type type() const { return type_; }
  const math::Vec2d& location() const { return location_; }
  MouseButton button() const { return button_; }
  KeyModifier modifiers() const { return modifiers_; }
  const math::Vec3d& wheel() const { return wheel_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  math::Vec2d location_;
  MouseButton button_;
  KeyModifier modifiers_;
  math::Vec3d wheel_;
};

#pragma mark -

inline MouseEvent::MouseEvent()
    : type_(Type::UNDEFINED),
      button_(MouseButton::UNDEFINED),
      modifiers_(KeyModifier::NONE) {}

inline MouseEvent::MouseEvent(Type type,
                              const math::Vec2d& location,
                              MouseButton button,
                              KeyModifier modifiers,
                              const math::Vec3d& wheel)
    : type_(type),
      location_(location),
      button_(button),
      modifiers_(modifiers),
      wheel_(wheel) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_MOUSE_EVENT_H_
