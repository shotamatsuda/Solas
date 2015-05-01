//
//  solas/tween/interval.h
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
#ifndef SOLAS_TWEEN_INTERVAL_H_
#define SOLAS_TWEEN_INTERVAL_H_

#include <cassert>

#include "solas/tween/interval.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename T>
class Interval final {
 public:
  using Value = T;

 public:
  // Constructors
  Interval();
  explicit Interval(T value);

  // Copy and assign
  Interval(const Interval& other) = default;
  Interval& operator=(const Interval& other) = default;

  // Comparison
  bool operator==(const Interval& other) const;
  bool operator!=(const Interval& other) const;
  bool operator<(const Interval& other) const;
  bool operator>(const Interval& other) const;
  bool operator<=(const Interval& other) const;
  bool operator>=(const Interval& other) const;

  // Arithmetic
  Interval& operator+=(const Interval& other);
  Interval& operator-=(const Interval& other);
  Interval operator+(const Interval& other) const;
  Interval operator-(const Interval& other) const;
  Unit operator/(const Interval& other) const;

  // Attributes
  bool empty() const { return !value_; }
  Value count() const { return value_; }

 private:
  T value_;
};

using Time = Interval<TimeValue>;
using Frame = Interval<FrameValue>;

#pragma mark -

template <typename T>
inline Interval<T>::Interval()
    : value_() {}

template <typename T>
inline Interval<T>::Interval(T value)
    : value_(value) {}

#pragma mark Arithmetic

template <typename T>
inline Interval<T>& Interval<T>::operator+=(const Interval& other) {
  value_ += other.value_;
  return *this;
}

template <typename T>
inline Interval<T>& Interval<T>::operator-=(const Interval& other) {
  value_ -= other.value_;
  return *this;
}

template <typename T>
inline Interval<T> Interval<T>::operator+(const Interval& other) const {
  return Interval<T>(value_ + other.value_);
}

template <typename T>
inline Interval<T> Interval<T>::operator-(const Interval& other) const {
  return Interval<T>(value_ - other.value_);
}

template <typename T>
inline Unit Interval<T>::operator/(const Interval& other) const {
  return static_cast<Unit>(value_) / other.value_;
}

#pragma mark Comparison

template <typename T>
inline bool Interval<T>::operator==(const Interval<T>& other) const {
  return value_ == other.value_;
}

template <typename T>
inline bool Interval<T>::operator!=(const Interval<T>& other) const {
  return !operator==(other);
}

template <typename T>
inline bool Interval<T>::operator<(const Interval& other) const {
  return value_ < other.value_;
}

template <typename T>
inline bool Interval<T>::operator>(const Interval& other) const {
  return value_ > other.value_;
}

template <typename T>
inline bool Interval<T>::operator<=(const Interval& other) const {
  return (value_ < other.value_ || value_ == other.value_);
}

template <typename T>
inline bool Interval<T>::operator>=(const Interval& other) const {
  return (value_ > other.value_ || value_ == other.value_);
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_INTERVAL_H_
