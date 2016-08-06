//
//  solas/app_event.h
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
#ifndef SOLAS_APP_EVENT_H_
#define SOLAS_APP_EVENT_H_

#include <functional>

#include <boost/any.hpp>
#include <glm/glm.hpp>

namespace solas {

class AppEvent final {
 public:
  enum class Type {
    SETUP,
    UPDATE,
    PRE,
    DRAW,
    POST,
    EXIT
  };

 public:
  explicit AppEvent(Type type);
  template <class Context>
  AppEvent(Type type,
           const Context& context,
           const glm::vec2& size,
           double scale);

  // Copy semantics excluding assignment
  AppEvent(const AppEvent&) = default;
  AppEvent& operator=(const AppEvent&) = delete;

  // Properties
  Type type() const { return type_; }
  template <class Context>
  const Context& context() const;
  const glm::vec2& size() const { return size_; }
  double scale() const { return scale_; }

 private:
  Type type_;
  boost::any context_;
  glm::vec2 size_;
  double scale_;
};

#pragma mark -

inline AppEvent::AppEvent(Type type) : type_(type) {}

template <class Context>
inline AppEvent::AppEvent(Type type,
                          const Context& context,
                          const glm::vec2& size,
                          double scale)
    : type_(type),
      context_(std::reference_wrapper<const Context>(context)),
      size_(size),
      scale_(scale) {}

#pragma mark Properties

template <class Context>
inline const Context& AppEvent::context() const {
  return boost::any_cast<std::reference_wrapper<const Context>>(context_);
}

}  // namespace solas

#endif  // SOLAS_APP_EVENT_H_
