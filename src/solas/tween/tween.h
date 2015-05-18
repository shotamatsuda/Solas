//
//  solas/tween/tween.h
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
#ifndef SOLAS_TWEEN_TWEEN_H_
#define SOLAS_TWEEN_TWEEN_H_

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include "solas/tween/accessor_adaptor.h"
#include "solas/tween/adaptor.h"
#include "solas/tween/pointer_adaptor.h"
#include "solas/tween/timeline.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename Interval_ = Time>
class Tween final {
 public:
  using Interval = Interval_;
  using Timeline = Timeline<Interval>;
  using IntervalValue = typename Interval::Value;
  
 private:
  using Adaptor = std::shared_ptr<Adaptor<Interval>>;

 public:
  // Constructors
  Tween();
  explicit Tween(const Adaptor& adaptor, Timeline *timeline = nullptr);

  // Construct with pointer
  template <typename T, typename Value>
  Tween(Value *target,
        const T& to,
        const Easing& easing,
        IntervalValue duration,
        Timeline *timeline = nullptr);
  template <typename T, typename Value>
  Tween(Value *target,
        const T& to,
        const Easing& easing,
        IntervalValue duration,
        IntervalValue delay,
        Timeline *timeline = nullptr);
  template <typename T, typename Value>
  Tween(Value *target,
        const T& to,
        const Easing& easing,
        IntervalValue duration,
        const Callback& callback,
        Timeline *timeline = nullptr);
  template <typename T, typename Value>
  Tween(Value *target,
        const T& to,
        const Easing& easing,
        IntervalValue duration,
        IntervalValue delay,
        const Callback& callback,
        Timeline *timeline = nullptr);

  // Construct with accessor
  template <typename Value, typename Class, typename Getter, typename Setter>
  Tween(Class *target,
        Getter getter,
        Setter setter,
        const std::string& name,
        const Value& to,
        const Easing& easing,
        IntervalValue duration,
        Timeline *timeline = nullptr);
  template <typename Value, typename Class, typename Getter, typename Setter>
  Tween(Class *target,
        Getter getter,
        Setter setter,
        const std::string& name,
        const Value& to,
        const Easing& easing,
        IntervalValue duration,
        IntervalValue delay,
        Timeline *timeline = nullptr);
  template <typename Value, typename Class, typename Getter, typename Setter>
  Tween(Class *target,
        Getter getter,
        Setter setter,
        const std::string& name,
        const Value& to,
        const Easing& easing,
        IntervalValue duration,
        const Callback& callback,
        Timeline *timeline = nullptr);
  template <typename Value, typename Class, typename Getter, typename Setter>
  Tween(Class *target,
        Getter getter,
        Setter setter,
        const std::string& name,
        const Value& to,
        const Easing& easing,
        IntervalValue duration,
        IntervalValue delay,
        const Callback& callback,
        Timeline *timeline = nullptr);

  // Copy and assign
  Tween(const Tween& other) = default;
  Tween& operator=(const Tween& other) = default;

  // Move
  Tween(Tween&& other) = default;
  Tween& operator=(Tween&& other) = default;

  // Comparison
  bool operator==(const Tween& other) const;
  bool operator!=(const Tween& other) const;

  // Controlling tween
  void start();
  void stop();

  // Attributes
  bool running() const;
  bool finished() const;
  bool empty() const;

  // Parameters
  const Easing& easing() const;
  void set_easing(const Easing& value);
  IntervalValue duration() const;
  void set_duration(IntervalValue value);
  IntervalValue delay() const;
  void set_delay(IntervalValue value);
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
  template <typename T, typename Value>
  void init(Value *target,
            const T& to,
            const Easing& easing,
            const Interval& duration,
            const Interval& delay,
            const Callback& callback);
  template <typename Value, typename Class, typename Getter, typename Setter>
  void init(Class *target,
            Getter getter,
            Setter setter,
            const std::string& name,
            const Value& to,
            const Easing& easing,
            const Interval& duration,
            const Interval& delay,
            const Callback& callback);

 private:
  Adaptor adaptor_;
  Timeline *timeline_;
};

#pragma mark -

template <typename Interval>
inline Tween<Interval>::Tween()
    : timeline_(nullptr) {}

template <typename Interval>
inline Tween<Interval>::Tween(const Adaptor& adaptor, Timeline *timeline)
    : adaptor_(adaptor),
      timeline_(timeline) {}

#pragma mark Construct with pointer

template <typename Interval>
template <typename T, typename Value>
inline Tween<Interval>::Tween(Value *target,
                              const T& to,
                              const Easing& easing,
                              IntervalValue duration,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, to, easing, Interval(duration), Interval(), nullptr);
}

template <typename Interval>
template <typename T, typename Value>
inline Tween<Interval>::Tween(Value *target,
                              const T& to,
                              const Easing& easing,
                              IntervalValue duration,
                              IntervalValue delay,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, to, easing, Interval(duration), Interval(delay), nullptr);
}

template <typename Interval>
template <typename T, typename Value>
inline Tween<Interval>::Tween(Value *target,
                              const T& to,
                              const Easing& easing,
                              IntervalValue duration,
                              const Callback& callback,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, to, easing, Interval(duration), Interval(), callback);
}

template <typename Interval>
template <typename T, typename Value>
inline Tween<Interval>::Tween(Value *target,
                              const T& to,
                              const Easing& easing,
                              IntervalValue duration,
                              IntervalValue delay,
                              const Callback& callback,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, to, easing, Interval(duration), Interval(delay), callback);
}

#pragma mark Construct with accessor

template <typename Interval>
template <typename Value, typename Class, typename Getter, typename Setter>
inline Tween<Interval>::Tween(Class *target,
                              Getter getter,
                              Setter setter,
                              const std::string& name,
                              const Value& to,
                              const Easing& easing,
                              IntervalValue duration,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, getter, setter, name, to,
       easing, Interval(duration), Interval(), nullptr);
}

template <typename Interval>
template <typename Value, typename Class, typename Getter, typename Setter>
inline Tween<Interval>::Tween(Class *target,
                              Getter getter,
                              Setter setter,
                              const std::string& name,
                              const Value& to,
                              const Easing& easing,
                              IntervalValue duration,
                              IntervalValue delay,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, getter, setter, name, to,
       easing, Interval(duration), Interval(delay), nullptr);
}

template <typename Interval>
template <typename Value, typename Class, typename Getter, typename Setter>
inline Tween<Interval>::Tween(Class *target,
                              Getter getter,
                              Setter setter,
                              const std::string& name,
                              const Value& to,
                              const Easing& easing,
                              IntervalValue duration,
                              const Callback& callback,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, getter, setter, name, to,
       easing, Interval(duration), Interval(), callback);
}

template <typename Interval>
template <typename Value, typename Class, typename Getter, typename Setter>
inline Tween<Interval>::Tween(Class *target,
                              Getter getter,
                              Setter setter,
                              const std::string& name,
                              const Value& to,
                              const Easing& easing,
                              IntervalValue duration,
                              IntervalValue delay,
                              const Callback& callback,
                              Timeline *timeline)
    : timeline_(timeline) {
  init(target, getter, setter, name, to,
       easing, Interval(duration), Interval(delay), callback);
}

#pragma mark Comparison

template <typename Interval>
inline bool Tween<Interval>::operator==(const Tween& other) const {
  return adaptor_ == other.adaptor_ && timeline_ == other.timeline_;
}

template <typename Interval>
inline bool Tween<Interval>::operator!=(const Tween& other) const {
  return !operator==(other);
}

#pragma mark Initializers

template <typename Interval>
template <typename T, typename Value>
inline void Tween<Interval>::init(Value *target,
                                  const T& to,
                                  const Easing& easing,
                                  const Interval& duration,
                                  const Interval& delay,
                                  const Callback& callback) {
  assert(target);
  using Adaptor = PointerAdaptor<Interval, Value>;
  adaptor_ = std::make_shared<Adaptor>(
      target, to, easing, duration, delay, callback);
}

template <typename Interval>
template <typename Value, typename Class, typename Getter, typename Setter>
inline void Tween<Interval>::init(Class *target,
                                  Getter getter,
                                  Setter setter,
                                  const std::string& name,
                                  const Value& to,
                                  const Easing& easing,
                                  const Interval& duration,
                                  const Interval& delay,
                                  const Callback& callback) {
  assert(target);
  using Adaptor = AccessorAdaptor<Interval, Value, Class, Getter, Setter>;
  adaptor_ = std::make_shared<Adaptor>(
      target, getter, setter, name, to, easing, duration, delay, callback);
}

#pragma mark Controlling tween

template <typename Interval>
inline void Tween<Interval>::start() {
  assert(timeline_);
  assert(adaptor_);
  if (!adaptor_->running()) {
    timeline_->add(adaptor_);
    adaptor_->start(timeline_->now());
  }
}

template <typename Interval>
inline void Tween<Interval>::stop() {
  assert(timeline_);
  assert(adaptor_);
  if (adaptor_->running()) {
    adaptor_->stop();
    timeline_->remove(adaptor_);
  }
}

#pragma mark Attributes

template <typename Interval>
inline bool Tween<Interval>::running() const {
  return adaptor_ && adaptor_->running();
}

template <typename Interval>
inline bool Tween<Interval>::finished() const {
  return adaptor_ && adaptor_->finished();
}

template <typename Interval>
inline bool Tween<Interval>::empty() const {
  return !adaptor_;
}

#pragma mark Parameters

template <typename Interval>
inline const Easing& Tween<Interval>::easing() const {
  assert(adaptor_);
  return adaptor_->easing();
}

template <typename Interval>
inline void Tween<Interval>::set_easing(const Easing& value) {
  assert(adaptor_);
  adaptor_->set_easing(value);
}

template <typename Interval>
inline typename Interval::Value Tween<Interval>::duration() const {
  assert(adaptor_);
  return adaptor_->duration().count();
}

template <typename Interval>
inline void Tween<Interval>::set_duration(IntervalValue value) {
  assert(adaptor_);
  return adaptor_->set_duration(Interval(value));
}

template <typename Interval>
inline typename Interval::Value Tween<Interval>::delay() const {
  assert(adaptor_);
  return adaptor_->delay().count();
}

template <typename Interval>
inline void Tween<Interval>::set_delay(IntervalValue value) {
  assert(adaptor_);
  return adaptor_->set_delay(Interval(value));
}

template <typename Interval>
inline const Callback& Tween<Interval>::callback() const {
  assert(adaptor_);
  return adaptor_->callback();
}

template <typename Interval>
inline void Tween<Interval>::set_callback(const std::function<void()>& value) {
  return adaptor_->set_callback(value);
}

#pragma mark Timeline

template <typename Interval>
inline Timeline<Interval> * Tween<Interval>::timeline() const {
  return timeline_;
}

template <typename Interval>
inline void Tween<Interval>::set_timeline(Timeline *value) {
  timeline_ = value;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TWEEN_H_
