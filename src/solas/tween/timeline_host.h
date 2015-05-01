//
//  solas/tween/timeline_host.h
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
#ifndef SOLAS_TWEEN_TIMELINE_HOST_H_
#define SOLAS_TWEEN_TIMELINE_HOST_H_

#include <utility>

#include "solas/tween/interval.h"
#include "solas/tween/timeline.h"
#include "solas/tween/tween.h"

namespace solas {
namespace tween {

class TimelineHost {
 public:
  // Constructors
  virtual ~TimelineHost() {}

  // Creating tweens
  template <typename Interval, typename... Args>
  Tween<Interval> tween(Args&&... args);

  // Accessing timeline
  template <typename Interval>
  Timeline<Interval>& timeline();
  template <typename Interval>
  const Timeline<Interval>& timeline() const;

 private:
  Timeline<Time> time_timeline_;
  Timeline<Frame> frame_timeline_;
};

#pragma mark -

#pragma mark Creating tweens

template <typename Interval, typename... Args>
inline tween::Tween<Interval> TimelineHost::tween(Args&&... args) {
  auto tween = tween::Tween<Interval>(
      std::forward<Args>(args)...,
      &timeline<Interval>());
  tween.start();
  return std::move(tween);
}

#pragma mark Accessing timeline

template <>
inline Timeline<Time>& TimelineHost::timeline() {
  return time_timeline_;
}

template <>
inline Timeline<Frame>& TimelineHost::timeline() {
  return frame_timeline_;
}

template <>
inline const Timeline<Time>& TimelineHost::timeline() const {
  return time_timeline_;
}

template <>
inline const Timeline<Frame>& TimelineHost::timeline() const {
  return frame_timeline_;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TIMELINE_HOST_H_
