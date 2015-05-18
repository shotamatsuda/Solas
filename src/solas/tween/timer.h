//
//  solas/tween/timer.h
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
#ifndef SOLAS_TWEEN_TIMER_H_
#define SOLAS_TWEEN_TIMER_H_

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include "solas/tween/adaptor.h"
#include "solas/tween/timeline.h"
#include "solas/tween/timer_adaptor.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_ = Time>
class Timer final {
 public:
  using Interval = Interval_;
  using Timeline = Timeline<Interval>;
  using IntervalValue = typename Interval::Value;
  
 private:
  using Adaptor = std::shared_ptr<Adaptor<Interval>>;

 public:
  // Constructors
  Timer();
  explicit Timer(const Adaptor& adaptor, Timeline *timeline = nullptr);

  // Construct with duration
  Timer(IntervalValue duration, Timeline *timeline = nullptr);
  Timer(IntervalValue duration,
        const Callback& callback,
        Timeline *timeline = nullptr);

  // Copy and assign
  Timer(const Timer& other) = default;
  Timer& operator=(const Timer& other) = default;

  // Move
  Timer(Timer&& other) = default;
  Timer& operator=(Timer&& other) = default;

  // Comparison
  bool operator==(const Timer& other) const;
  bool operator!=(const Timer& other) const;

  // Controlling timer
  void start();
  void stop();

  // Attributes
  bool running() const;
  bool finished() const;
  bool empty() const;

  // Parameters
  IntervalValue duration() const;
  void set_duration(IntervalValue value);
  const Callback& callback() const;
  void set_callback(const Callback& value);

  // Timeline
  Timeline * timeline() const;
  void set_timeline(Timeline *value);

  // Adaptor
  Adaptor adaptor() const { return adaptor_; }

  // Conversion
  operator bool() const { return adaptor_ && timeline_; }

 private:
  // Initializers
  void init(const Interval& duration,
            const Callback& callback);

 private:
  Adaptor adaptor_;
  Timeline *timeline_;
};

#pragma mark -

template <typename Interval>
inline Timer<Interval>::Timer()
    : timeline_(nullptr) {}

template <typename Interval>
inline Timer<Interval>::Timer(const Adaptor& adaptor, Timeline *timeline)
    : adaptor_(adaptor),
      timeline_(timeline) {}

#pragma mark Construct with duration

template <typename Interval>
inline Timer<Interval>::Timer(IntervalValue duration, Timeline *timeline)
    : timeline_(timeline) {
  init(Interval(duration), nullptr);
}

template <typename Interval>
inline Timer<Interval>::Timer(IntervalValue duration,
                              const Callback& callback,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(Interval(duration), callback);
}

#pragma mark Comparison

template <typename Interval>
inline bool Timer<Interval>::operator==(const Timer& other) const {
  return adaptor_ == other.adaptor_ && timeline_ == other.timeline_;
}

template <typename Interval>
inline bool Timer<Interval>::operator!=(const Timer& other) const {
  return !operator==(other);
}

#pragma mark Initializers

template <typename Interval>
inline void Timer<Interval>::init(const Interval& duration,
                                  const Callback& callback) {
  adaptor_ = std::make_shared<TimerAdaptor<Interval>>(duration, callback);
}

#pragma mark Controlling tween

template <typename Interval>
inline void Timer<Interval>::start() {
  assert(timeline_);
  assert(adaptor_);
  if (!adaptor_->running()) {
    timeline_->add(adaptor_);
    adaptor_->start(timeline_->now());
  }
}

template <typename Interval>
inline void Timer<Interval>::stop() {
  assert(timeline_);
  assert(adaptor_);
  if (adaptor_->running()) {
    adaptor_->stop();
    timeline_->remove(adaptor_);
  }
}

#pragma mark Attributes

template <typename Interval>
inline bool Timer<Interval>::running() const {
  return adaptor_ && adaptor_->running();
}

template <typename Interval>
inline bool Timer<Interval>::finished() const {
  return adaptor_ && adaptor_->finished();
}

template <typename Interval>
inline bool Timer<Interval>::empty() const {
  return !adaptor_;
}

#pragma mark Parameters

template <typename Interval>
inline typename Interval::Value Timer<Interval>::duration() const {
  assert(adaptor_);
  return adaptor_->duration().count();
}

template <typename Interval>
inline void Timer<Interval>::set_duration(IntervalValue value) {
  assert(adaptor_);
  return adaptor_->set_duration(Interval(value));
}

template <typename Interval>
inline const Callback& Timer<Interval>::callback() const {
  assert(adaptor_);
  return adaptor_->callback();
}

template <typename Interval>
inline void Timer<Interval>::set_callback(const std::function<void()>& value) {
  return adaptor_->set_callback(value);
}

#pragma mark Timeline

template <typename Interval>
inline Timeline<Interval> * Timer<Interval>::timeline() const {
  return timeline_;
}

template <typename Interval>
inline void Timer<Interval>::set_timeline(Timeline *value) {
  timeline_ = value;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TWEEN_H_
