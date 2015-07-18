//
//  solas/app_event.h
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
#ifndef SOLAS_APP_EVENT_H_
#define SOLAS_APP_EVENT_H_

#include "solas/context_holder.h"
#include "solas/math.h"

namespace solas {

class AppEvent final {
 public:
  enum class Type {
    UNDEFINED,
    SETUP,
    UPDATE,
    PRE,
    DRAW,
    POST,
    EXITED
  };

 public:
  AppEvent() {}
  template <class Context>
  AppEvent(const Context& context, const Size2d& size, double scale);

  // Copy semantics excluding assignment
  AppEvent(const AppEvent& other) = default;
  AppEvent& operator=(const AppEvent& other) = delete;

  // Properties
  const ContextHolder& context() const { return context_; }
  const Size2d& size() const { return size_; }
  double scale() const { return scale_; }

 private:
  ContextHolder context_;
  Size2d size_;
  double scale_;
};

#pragma mark -

template <class Context>
inline AppEvent::AppEvent(const Context& context,
                          const Size2d& size,
                          double scale)
    : context_(context),
      size_(size),
      scale_(scale) {}

}  // namespace solas

#endif  // SOLAS_APP_EVENT_H_
