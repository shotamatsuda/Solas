//
//  solas/app/touch_event.h
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
#ifndef SOLAS_APP_TOUCH_EVENT_H_
#define SOLAS_APP_TOUCH_EVENT_H_

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
  TouchEvent(Type type,
             const std::vector<math::Vec2d>& touches,
             const std::vector<math::Vec2d>& previous_touches);

  // Copy and move
  TouchEvent(const TouchEvent& other) = default;
  TouchEvent(TouchEvent&& other) = default;

  // Disallow assign
  TouchEvent& operator=(const TouchEvent& other) = delete;

  // Attributes
  bool empty() const { return type == Type::UNDEFINED; }

  // Conversion
  operator bool() const { return !empty(); }

 public:
  Type type;
  std::vector<math::Vec2d> touches;
  std::vector<math::Vec2d> previous_touches;
};

#pragma mark -

inline TouchEvent::TouchEvent()
    : type(Type::UNDEFINED) {}

inline TouchEvent::TouchEvent(
    Type type,
    const std::vector<math::Vec2d>& touches,
    const std::vector<math::Vec2d>& previous_touches)
    : type(type),
      touches(touches),
      previous_touches(previous_touches) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_TOUCH_EVENT_H_
