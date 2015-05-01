//
//  solas/tween/adaptor.h
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
#ifndef SOLAS_TWEEN_ADAPTOR_H_
#define SOLAS_TWEEN_ADAPTOR_H_

#include <cstddef>

#include "solas/tween/easing.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_>
class Adaptor {
 public:
  using Interval = Interval_;

 public:
  // Constructors
  virtual ~Adaptor() = 0;

  // Disallow copy and assign
  Adaptor(const Adaptor& other) = delete;
  Adaptor& operator=(const Adaptor& other) = delete;

  // Controlling the adaptor
  void start(const Interval& now);
  void stop();
  void update(const Interval& now, bool callback = true);

  // Attributes
  bool running() const { return running_; }
  bool finished() const { return finished_; }

  // Hash
  virtual std::size_t object_hash() const = 0;
  virtual std::size_t target_hash() const = 0;

  // Parameters
  const Easing& easing() const;
  void set_easing(const Easing& value);
  const Interval& duration() const;
  void set_duration(const Interval& value);
  const Interval& delay() const;
  void set_delay(const Interval& value);
  const Callback& callback() const;
  void set_callback(const Callback& value);

 protected:
  // Constructors
  Adaptor(const Easing& easing,
              const Interval& duration,
              const Interval& delay,
              const Callback& callback);

  // Move
  Adaptor(Adaptor&& other) = default;

  // Updates against the local unit time
  virtual void update(Unit unit) = 0;

 private:
  Easing easing_;
  Interval duration_;
  Interval delay_;
  Callback callback_;
  bool running_;
  bool finished_;
  Interval started_;
};

#pragma mark -

template <typename Interval>
inline Adaptor<Interval>::Adaptor(
    const Easing& easing,
    const Interval& duration,
    const Interval& delay,
    const Callback& callback)
    : easing_(easing),
      duration_(duration),
      delay_(delay),
      callback_(callback),
      running_(false),
      finished_(false) {}

template <typename Interval>
inline Adaptor<Interval>::~Adaptor() {}

#pragma mark Controlling the adaptor

template <typename Interval>
inline void Adaptor<Interval>::start(const Interval& now) {
  if (!running_) {
    running_ = true;
    if (!finished_) {
      started_ = now;
    }
  }
}

template <typename Interval>
inline void Adaptor<Interval>::stop() {
  if (running_) {
    running_ = false;
  }
}

template <typename Interval>
inline void Adaptor<Interval>::update(const Interval& now, bool callback) {
  if (running_) {
    const auto elapsed = now - started_ - delay_;
    if (elapsed < duration_) {
      update(elapsed / duration_);
    } else {
      update(1.0);
      running_ = false;
      finished_ = true;
      started_ = Interval();
      if (callback && callback_) {
        callback_();
      }
    }
  }
}

#pragma mark Parameters

template <typename Interval>
inline const Easing& Adaptor<Interval>::easing() const {
  return easing_;
}

template <typename Interval>
inline void Adaptor<Interval>::set_easing(const Easing& value) {
  easing_ = value;
}

template <typename Interval>
inline const Interval& Adaptor<Interval>::duration() const {
  return duration_;
}

template <typename Interval>
inline void Adaptor<Interval>::set_duration(const Interval& value) {
  duration_ = value;
}

template <typename Interval>
inline const Interval& Adaptor<Interval>::delay() const {
  return delay_;
}

template <typename Interval>
inline void Adaptor<Interval>::set_delay(const Interval& value) {
  delay_ = value;
}

template <typename Interval>
inline const Callback& Adaptor<Interval>::callback() const {
  return callback_;
}

template <typename Interval>
inline void Adaptor<Interval>::set_callback(const Callback& value) {
  callback_ = value;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_ADAPTOR_H_
