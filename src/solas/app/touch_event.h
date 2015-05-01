//
//  solas/app/touch_event.h
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
#ifndef SOLAS_APP_TOUCH_EVENT_H_
#define SOLAS_APP_TOUCH_EVENT_H_

#include <vector>

#include "solas/math/vector.h"

namespace solas {
namespace app {

class TouchEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGIN,
    MOVE,
    CANCEL,
    END
  };

 public:
  // Constructors
  TouchEvent();
  TouchEvent(Type type, const std::vector<math::Vec2d>& touches);

  // Copy and move
  TouchEvent(const TouchEvent& other) = default;
  TouchEvent(TouchEvent&& other) = default;

  // Disallow assign
  TouchEvent& operator=(const TouchEvent& other) = delete;

  // Attributes
  bool empty() const { return type_ == Type::UNDEFINED; }

  // Properties
  Type type() const { return type_; }
  const std::vector<math::Vec2d>& touches() const { return touches_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  std::vector<math::Vec2d> touches_;
};

#pragma mark -

inline TouchEvent::TouchEvent() : type_(Type::UNDEFINED) {}

inline TouchEvent::TouchEvent(Type type,
                              const std::vector<math::Vec2d>& touches)
    : type_(type),
      touches_(touches) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_TOUCH_EVENT_H_
