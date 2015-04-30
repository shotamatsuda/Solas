//
//  solas/app/app_event.h
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
#ifndef SOLAS_APP_APP_EVENT_H_
#define SOLAS_APP_APP_EVENT_H_

#include "solas/app/context_holder.h"
#include "solas/math/size.h"

namespace solas {
namespace app {

class AppEvent final {
 public:
  // Constructors
  AppEvent() {}
  template <typename Context>
  AppEvent(const Context& context, const math::Size2d& size);

  // Copy and move
  AppEvent(const AppEvent& other) = default;
  AppEvent(AppEvent&& other) = default;

  // Disallow assign
  AppEvent& operator=(const AppEvent& other) = delete;

  // Parameters
  const ContextHolder& context() const { return context_; }
  const math::Size2d& size() const { return size_; }

 private:
  ContextHolder context_;
  math::Size2d size_;
};

#pragma mark -

template <typename Context>
inline AppEvent::AppEvent(const Context& context, const math::Size2d& size)
    : context_(context),
      size_(size) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_APP_EVENT_H_
