//
//  solas/app/context_holder.h
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
#ifndef SOLAS_APP_CONTEXT_HOLDER_H_
#define SOLAS_APP_CONTEXT_HOLDER_H_

#include <functional>

#include <boost/any.hpp>

namespace solas {
namespace app {

class ContextHolder final {
 public:
  // Constructors
  ContextHolder() {}
  template <typename T>
  explicit ContextHolder(const T& value);

  // Copy and assign
  ContextHolder(const ContextHolder& other) = default;
  ContextHolder(ContextHolder&& other) = default;
  ContextHolder& operator=(const ContextHolder& other) = default;
  ContextHolder& operator=(ContextHolder&& other) = default;

  // Reference
  template <typename T>
  const T& get() const;

  // Attributes
  bool empty() const { return value_.empty(); }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  boost::any value_;
};

#pragma mark -

template <typename T>
inline ContextHolder::ContextHolder(const T& value)
    : value_(std::reference_wrapper<const T>(value)) {}

#pragma mark Context

template <typename Context>
inline const Context& ContextHolder::get() const {
  return boost::any_cast<std::reference_wrapper<const Context>>(value_);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_CONTEXT_HOLDER_H_
