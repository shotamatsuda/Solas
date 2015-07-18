//
//  solas/context_holder.h
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
#ifndef SOLAS_CONTEXT_HOLDER_H_
#define SOLAS_CONTEXT_HOLDER_H_

#include <functional>

#include <boost/any.hpp>

namespace solas {

class ContextHolder final {
 public:
  ContextHolder() {}
  template <class T>
  explicit ContextHolder(const T& value);

  // Copy semantics
  ContextHolder(const ContextHolder& other) = default;
  ContextHolder& operator=(const ContextHolder& other) = default;

  // Reference
  template <class T>
  const T& get() const;

  // Attributes
  bool empty() const { return value_.empty(); }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  boost::any value_;
};

#pragma mark -

template <class T>
inline ContextHolder::ContextHolder(const T& value)
    : value_(std::reference_wrapper<const T>(value)) {}

#pragma mark Reference

template <class Context>
inline const Context& ContextHolder::get() const {
  return boost::any_cast<std::reference_wrapper<const Context>>(value_);
}

}  // namespace solas

#endif  // SOLAS_CONTEXT_HOLDER_H_
