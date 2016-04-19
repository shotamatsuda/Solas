//
//  solas/motion_event.h
//
//  The MIT License
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
#ifndef SOLAS_MOTION_EVENT_H_
#define SOLAS_MOTION_EVENT_H_

#include <cassert>
#include <ostream>

#include "solas/motion_kind.h"

namespace solas {

class MotionEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGAN,
    CANCELLED,
    ENDED
  };

 public:
  MotionEvent();
  MotionEvent(Type type, MotionKind kind);

  // Copy semantics excluding assignment
  MotionEvent(const MotionEvent&) = default;
  MotionEvent& operator=(const MotionEvent&) = delete;

  // Properties
  bool empty() const { return type_ == Type::UNDEFINED; }
  Type type() const { return type_; }
  MotionKind kind() const { return kind_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  MotionKind kind_;
};

#pragma mark -

inline MotionEvent::MotionEvent()
    : type_(Type::UNDEFINED),
      kind_(MotionKind::UNDEFINED) {}

inline MotionEvent::MotionEvent(Type type, MotionKind kind)
    : type_(type),
      kind_(kind) {}

#pragma mark Stream

inline std::ostream& operator<<(std::ostream& os, MotionEvent::Type type) {
  switch (type) {
    case MotionEvent::Type::UNDEFINED:
      os << "undefined";
      break;
    case MotionEvent::Type::BEGAN:
      os << "begin";
      break;
    case MotionEvent::Type::CANCELLED:
      os << "cancel";
      break;
    case MotionEvent::Type::ENDED:
      os << "end";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const MotionEvent& event) {
  os << "( type = " << event.type() << ", kind = " << event.kind();
  return os << " )";
}

}  // namespace solas

#endif  // SOLAS_MOTION_EVENT_H_
