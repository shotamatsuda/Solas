//
//  solas/tween/timeline.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
  std::unique_ptr<std::mutex> mutex_;
};

#pragma mark -

template <typename Interval>
inline Timeline<Interval>::Timeline()
    : mutex_(std::make_unique<std::mutex>()) {}

#pragma mark Managing adaptors

template <typename Interval>
template <typename T>
inline void Timeline<Interval>::remove(const T *object) {
  std::lock_guard<std::mutex> lock(*mutex_);
  objects_.erase(Hash(object));
}

template <typename Interval>
template <typename T>
inline bool Timeline<Interval>::contains(const T *object) const {
  std::lock_guard<std::mutex> lock(*mutex_);
  return objects_.find(Hash(object)) != objects_.end();
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TIMELINE_H_
