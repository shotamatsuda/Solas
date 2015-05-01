//
//  solas/tween/accessor_adaptor.h
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
#ifndef SOLAS_TWEEN_ACCESSOR_ADAPTOR_H_
#define SOLAS_TWEEN_ACCESSOR_ADAPTOR_H_

#include <cassert>
#include <cstddef>
#include <functional>
#include <string>

#include "solas/tween/adaptor.h"
#include "solas/tween/easing.h"
#include "solas/tween/hash.h"
#include "solas/tween/transform.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_,
          typename Value_,
          typename Class_,
          typename Getter_,
          typename Setter_>
class AccessorAdaptor : public Adaptor<Interval_> {
 public:
  using Interval = Interval_;
  using Value = Value_;
  using Class = Class_;
  using Getter = Getter_;
  using Setter = Setter_;

  // Constructors
  template <typename T>
  AccessorAdaptor(Class *object,
                  Getter getter,
                  Setter setter,
                  const std::string& name,
                  const T& to,
                  const Easing& easing,
                  const Interval& duration,
                  const Interval& delay,
                  const std::function<void()>& callback);

  // Disallow copy and assign
  AccessorAdaptor(const AccessorAdaptor& other) = delete;
  AccessorAdaptor& operator=(const AccessorAdaptor& other) = delete;

  // Move
  AccessorAdaptor(AccessorAdaptor&& other) = default;

  // Controlling the adaptor
  using Adaptor<Interval>::update;

  // Hash
  std::size_t object_hash() const override;
  std::size_t target_hash() const override;

  // Parameters
  Class * object() const { return object_; }
  const Value& from() const { return from_; }
  const Value& to() const { return to_; }

 protected:
  // Updates against the local unit time
  void update(Unit unit) override;

 private:
  Class *object_;
  Getter getter_;
  Setter setter_;
  std::size_t target_hash_;
  Value from_;
  Value to_;
};

#pragma mark -

template <typename Interval,
          typename Value,
          typename Class,
          typename Getter,
          typename Setter>
template <typename T>
inline AccessorAdaptor<Interval, Value, Class, Getter, Setter>
    ::AccessorAdaptor(Class *object,
                      Getter getter,
                      Setter setter,
                      const std::string& name,
                      const T& to,
                      const Easing& easing,
                      const Interval& duration,
                      const Interval& delay,
                      const Callback& callback)
    : Adaptor<Interval>(easing, duration, delay, callback),
      object_(object),
      getter_(getter),
      setter_(setter),
      target_hash_(std::hash<std::string>()(name)),
      from_((object->*getter)()),
      to_(to) {}

#pragma mark Updates against the local unit time

template <typename Interval,
          typename Value,
          typename Class,
          typename Getter,
          typename Setter>
inline void AccessorAdaptor<Interval, Value, Class, Getter, Setter>
    ::update(Unit unit) {
  assert(object_);
  if (unit < 0.0) {
    from_ = (object_->*getter_)();
  } else if (Adaptor<Interval>::duration().empty() || unit > 1.0) {
    (object_->*setter_)(Transform(this->easing(), 1.0, from_, to_));
  } else {
    (object_->*setter_)(Transform(this->easing(), unit, from_, to_));
  }
}

#pragma mark Hash

template <typename Interval,
          typename Value,
          typename Class,
          typename Getter,
          typename Setter>
inline std::size_t AccessorAdaptor<Interval, Value, Class, Getter, Setter>
    ::object_hash() const {
  return Hash(object_);
}

template <typename Interval,
          typename Value,
          typename Class,
          typename Getter,
          typename Setter>
inline std::size_t AccessorAdaptor<Interval, Value, Class, Getter, Setter>
    ::target_hash() const {
  return target_hash_;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_ACCESSOR_ADAPTOR_H_
