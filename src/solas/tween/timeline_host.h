//
//  solas/tween/timeline_host.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//  Copyright (C) 2014-2015 takram design engineering
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
#ifndef SOLAS_TWEEN_TIMELINE_HOST_H_
#define SOLAS_TWEEN_TIMELINE_HOST_H_

#include "solas/tween/interval.h"
#include "solas/tween/timeline.h"
#include "solas/tween/tween.h"

namespace solas {
namespace tween {

template <typename Interval_ = Time>
class TimelineHost {
 public:
  using Interval = Interval_;
  using Timeline = Timeline<Interval>;
  using Tween = Tween<Interval>;

  // Constructors
  virtual ~TimelineHost() = 0;

  // Creating tweens
  template <typename... Args>
  Tween tween(Args&&... args);

  // Accessing timeline
  virtual Timeline& timeline() = 0;
  virtual const Timeline& timeline() const = 0;
};

#pragma mark - Inline Implementations

template <typename Interval>
inline TimelineHost<Interval>::~TimelineHost() {}

#pragma mark Creating tweens

template <typename Interval>
template <typename... Args>
inline Tween<Interval> TimelineHost<Interval>::tween(Args&&... args) {
  auto tween = Tween(args..., &timeline());
  tween.start();
  return tween;
}

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TIMELINE_HOST_H_
