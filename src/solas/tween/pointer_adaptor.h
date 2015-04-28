//
//  solas/tween/pointer_adaptor.h
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
#ifndef SOLAS_TWEEN_POINTER_ADAPTOR_H_
#define SOLAS_TWEEN_POINTER_ADAPTOR_H_

#include <cassert>
#include <cstddef>

#include "solas/tween/adaptor.h"
#include "solas/tween/easing.h"
#include "solas/tween/hash.h"
#include "solas/tween/transform.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_, typename Value_>
class PointerAdaptor : public Adaptor<Interval_> {
 public:
  using Interval = Interval_;
  using Value = Value_;

  // Constructors
  template <typename T>
  PointerAdaptor(Value *target,
                 const T& to,
                 const Easing& easing,
                 const Interval& duration,
                 const Interval& delay,
                 const Callback& callback);

  // Disallow copy and assign
  PointerAdaptor(const PointerAdaptor& other) = delete;
  PointerAdaptor& operator=(const PointerAdaptor& other) = delete;

  // Move
  PointerAdaptor(PointerAdaptor&& other) = default;

  // Controlling the adaptor
  using Adaptor<Interval>::update;

  // Hash
  std::size_t object_hash() const override;
  std::size_t target_hash() const override;

  // Parameters
  Value * target() const { return target_; }
  const Value& from() const { return from_; }
  const Value& to() const { return to_; }

 protected:
  // Updates against the local unit time
  void update(Unit unit) override;

 private:
  // Data members
  Value *target_;
  Value from_;
  Value to_;
};

#pragma mark -

template <typename Interval, typename Value>
template <typename T>
inline PointerAdaptor<Interval, Value>::PointerAdaptor(
    Value *target,
    const T& to,
    const Easing& easing,
    const Interval& duration,
    const Interval& delay,
    const Callback& callback)
    : Adaptor<Interval>(easing, duration, delay, callback),
      target_(target),
      from_(*target),
      to_(to) {}

#pragma mark Updates against the local unit time

template <typename Interval, typename Value>
inline void PointerAdaptor<Interval, Value>::update(Unit unit) {
  assert(target_);
  if (unit < 0.0) {
    from_ = *target_;
  } else if (this->duration().empty() || unit > 1.0) {
    *target_ = Transform(this->easing(), 1.0, from_, to_);
  } else {
    *target_ = Transform(this->easing(), unit, from_, to_);
  }
}

#pragma mark Hash

template <typename Interval, typename Value>
inline std::size_t PointerAdaptor<Interval, Value>::object_hash() const {
  return Hash(target_);
}

template <typename Interval, typename Value>
inline std::size_t PointerAdaptor<Interval, Value>::target_hash() const {
  return Hash(target_);
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_POINTER_ADAPTOR_H_
