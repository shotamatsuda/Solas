//
//  solas/tween/clock.h
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
#ifndef SOLAS_TWEEN_CLOCK_H_
#define SOLAS_TWEEN_CLOCK_H_

#include <chrono>

#include "solas/tween/interval.h"

namespace solas {
namespace tween {

template <typename Interval_>
class Clock final {
 public:
  using Interval = Interval_;

 public:
  // Constructors
  Clock();

  // Copy and assign
  Clock(const Clock& other) = default;
  Clock& operator=(const Clock& other) = default;

  // Comparison
  bool operator==(const Clock& other) const;
  bool operator!=(const Clock& other) const;

  // Controlling clock
  Interval advance();
  Interval now() const { return Interval(now_); }

 private:
  typename Interval::Value now_;
  typename Interval::Value birth_;
};

#pragma mark -

template <typename Interval>
inline Clock<Interval>::Clock()
    : now_(),
      birth_(advance().count()) {}

#pragma mark Comparison

template <typename Interval>
inline bool Clock<Interval>::operator==(const Clock& other) const {
  return (now_ == other.now_ && birth_ == other.birth_);
}

template <typename Interval>
inline bool Clock<Interval>::operator!=(const Clock& other) const {
  return !operator==(other);
}

#pragma mark Controlling clock

template <>
inline Time Clock<Time>::advance() {
  using Clock = std::chrono::high_resolution_clock;
  using Duration = std::chrono::microseconds;
  now_ = static_cast<TimeValue>(std::chrono::duration_cast<Duration>(
      Clock::now().time_since_epoch()).count()) / Duration::period::den;
  return Time(now_);
}

template <>
inline Frame Clock<Frame>::advance() {
  return Frame(++now_);
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_CLOCK_H_
