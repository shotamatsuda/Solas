//
//  solas/app/motion_event.h
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
#ifndef SOLAS_APP_MOTION_EVENT_H_
#define SOLAS_APP_MOTION_EVENT_H_

namespace solas {
namespace app {

class MotionEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGIN,
    CANCEL,
    END
  };

 public:
  MotionEvent();

  // Copy semantics excluding assignment
  MotionEvent(const MotionEvent& other) = default;
  MotionEvent& operator=(const MotionEvent& other) = delete;

  // Attributes
  bool empty() const { return type_ == Type::UNDEFINED; }

  // Properties
  Type type() const { return type_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
};

#pragma mark -

inline MotionEvent::MotionEvent()
    : type_(Type::UNDEFINED) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_MOTION_EVENT_H_
