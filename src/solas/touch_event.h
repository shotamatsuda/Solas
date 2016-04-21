//
//  solas/touch_event.h
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
#ifndef SOLAS_TOUCH_EVENT_H_
#define SOLAS_TOUCH_EVENT_H_

#include <vector>

#include "takram/math.h"

namespace solas {

class TouchEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGAN,
    MOVED,
    CANCELLED,
    ENDED
  };

 public:
  TouchEvent();
  TouchEvent(Type type, const std::vector<takram::Vec2d>& touches);

  // Copy semantics excluding assignment
  TouchEvent(const TouchEvent&) = default;
  TouchEvent& operator=(const TouchEvent&) = delete;

  // Properties
  bool empty() const { return type_ == Type::UNDEFINED; }
  Type type() const { return type_; }
  const std::vector<takram::Vec2d>& touches() const { return touches_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  std::vector<takram::Vec2d> touches_;
};

#pragma mark -

inline TouchEvent::TouchEvent() : type_(Type::UNDEFINED) {}

inline TouchEvent::TouchEvent(Type type,
                              const std::vector<takram::Vec2d>& touches)
    : type_(type),
      touches_(touches) {}

}  // namespace solas

#endif  // SOLAS_TOUCH_EVENT_H_
