//
//  solas/tween/timer_adaptor.h
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
#ifndef SOLAS_TWEEN_TIMER_ADAPTOR_H_
#define SOLAS_TWEEN_TIMER_ADAPTOR_H_

#include <cstddef>
#include <limits>
#include <random>

#include "solas/tween/adaptor.h"
#include "solas/tween/easing.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_>
class TimerAdaptor : public Adaptor<Interval_> {
 public:
  using Interval = Interval_;

  // Constructors
  TimerAdaptor(const Interval& duration, const Callback& callback);

  // Disallow copy and assign
  TimerAdaptor(const TimerAdaptor& other) = delete;
  TimerAdaptor& operator=(const TimerAdaptor& other) = delete;

  // Move
  TimerAdaptor(TimerAdaptor&& other) = default;

  // Controlling the adaptor
  using Adaptor<Interval>::update;

  // Hash
  std::size_t object_hash() const override;
  std::size_t target_hash() const override;

 protected:
  // Updates against the local unit time
  void update(Unit unit) override {}
};

#pragma mark -

template <typename Interval>
inline TimerAdaptor<Interval>::TimerAdaptor(
    const Interval& duration,
    const Callback& callback)
    : Adaptor<Interval>(LinearEasing::In, duration, Interval(), callback) {}

#pragma mark Hash

template <typename Interval>
inline std::size_t TimerAdaptor<Interval>::object_hash() const {
  std::mt19937 generator((std::random_device()()));
  std::uniform_int_distribution<std::size_t> distribution(
      std::numeric_limits<std::size_t>::min(),
      std::numeric_limits<std::size_t>::max());
  return distribution(generator);
}

template <typename Interval>
inline std::size_t TimerAdaptor<Interval>::target_hash() const {
  std::mt19937 generator((std::random_device()()));
  std::uniform_int_distribution<std::size_t> distribution(
      std::numeric_limits<std::size_t>::min(),
      std::numeric_limits<std::size_t>::max());
  return distribution(generator);
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TIMER_ADAPTOR_H_
