//
//  solas/tween/timeline.h
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
#ifndef SOLAS_TWEEN_TIMELINE_H_
#define SOLAS_TWEEN_TIMELINE_H_

#include <cstddef>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "solas/tween/adaptor.h"
#include "solas/tween/clock.h"
#include "solas/tween/hash.h"

namespace solas {
namespace tween {

template <typename Interval_>
class Timeline final {
 public:
  using Interval = Interval_;

 private:
  using Adaptor = std::shared_ptr<Adaptor<Interval>>;
  using Targets = std::unordered_multimap<std::size_t, Adaptor>;

 public:
  // Constructors
  Timeline();

  // Disallow copy and assign
  Timeline(const Timeline& other) = delete;
  Timeline& operator=(const Timeline& other) = delete;

  // Move
  Timeline(Timeline&& other) = default;

  // Managing adaptors
  void add(Adaptor adaptor, bool overwrite = true);
  void remove(Adaptor adaptor);
  bool contains(Adaptor adaptor) const;
  template <typename T>
  void remove(const T *object);
  template <typename T>
  bool contains(const T *object) const;
  bool empty() const;

  // Advances the timeline
  Interval advance();
  Interval now() const { return clock_.now(); }

 private:
  std::unordered_map<std::size_t, Targets> objects_;
  Clock<Interval> clock_;
  std::unique_ptr<std::recursive_mutex> mutex_;
};

#pragma mark -

template <typename Interval>
inline Timeline<Interval>::Timeline()
    : mutex_(std::make_unique<std::recursive_mutex>()) {}

#pragma mark Managing adaptors

template <typename Interval>
template <typename T>
inline void Timeline<Interval>::remove(const T *object) {
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  objects_.erase(Hash(object));
}

template <typename Interval>
template <typename T>
inline bool Timeline<Interval>::contains(const T *object) const {
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  return objects_.find(Hash(object)) != objects_.end();
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TIMELINE_H_
