//
//  solas/tween/pointer_adaptor.h
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
