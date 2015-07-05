//
//  solas/app/composite.h
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
#ifndef SOLAS_APP_COMPOSITE_H_
#define SOLAS_APP_COMPOSITE_H_

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "solas/app/mouse_button.h"
#include "takram/math/vector.h"
#include "takram/tween/timeline.h"
#include "takram/tween/timeline_host.h"
#include "takram/tween/timer.h"
#include "takram/tween/tween.h"

namespace solas {
namespace app {

class Composite {
 public:
  // Constructors
  explicit Composite(Composite *parent);
  virtual ~Composite() = 0;

  // Disallow copy semantics
  Composite(const Composite& other) = delete;
  Composite& operator=(const Composite& other) = delete;

  // Move semantics
  Composite(Composite&& other);

  // Structure
  virtual double width() const;
  virtual double height() const;
  virtual double scale() const;

  // Mouse
  virtual const takram::math::Vec2d& mouse() const;
  virtual const takram::math::Vec2d& pmouse() const;
  virtual MouseButton mouse_button() const;
  virtual bool mouse_pressed() const;

  // Keyboard
  virtual char key() const;
  virtual std::uint32_t key_code() const;
  virtual bool key_pressed() const;

  // Touches
  virtual const takram::math::Vec2d& touch() const;
  virtual const takram::math::Vec2d& ptouch() const;
  virtual bool touch_pressed() const;

  // Creating tweens
  template <class Interval = takram::tween::Time, class... Args>
  takram::tween::Tween<Interval> tween(Args&&... args);
  template <class Interval = takram::tween::Time, class... Args>
  takram::tween::Timer<Interval> timer(Args&&... args);

  // Accessing timeline
  template <class Interval = takram::tween::Time>
  takram::tween::Timeline<Interval>& timeline();
  template <class Interval = takram::tween::Time>
  const takram::tween::Timeline<Interval>& timeline() const;

  // Aggregation
  virtual Composite * parent() const;

 protected:
  // Constructors
  Composite();

  // Aggregation
  virtual takram::tween::TimelineHost * timeline_host();
  virtual const takram::tween::TimelineHost * timeline_host() const;

 private:
  Composite *parent_;
};

#pragma mark -

inline Composite::Composite() : parent_(nullptr) {}

inline Composite::Composite(Composite *parent) : parent_(parent) {
  assert(parent);
}

inline Composite::Composite(Composite&& other) : parent_(other.parent_) {
  other.parent_ = nullptr;
}

inline Composite::~Composite() {}

#pragma mark Structure

inline double Composite::width() const {
  assert(parent_);
  return parent_->width();
}

inline double Composite::height() const {
  assert(parent_);
  return parent_->height();
}

inline double Composite::scale() const {
  assert(parent_);
  return parent_->scale();
}

#pragma mark Mouse

inline const takram::math::Vec2d& Composite::mouse() const {
  assert(parent_);
  return parent_->mouse();
}

inline const takram::math::Vec2d& Composite::pmouse() const {
  assert(parent_);
  return parent_->pmouse();
}

inline MouseButton Composite::mouse_button() const {
  assert(parent_);
  return parent_->mouse_button();
}

inline bool Composite::mouse_pressed() const {
  assert(parent_);
  return parent_->mouse_pressed();
}

#pragma mark Keyboard

inline char Composite::key() const {
  assert(parent_);
  return parent_->key();
}

inline std::uint32_t Composite::key_code() const {
  assert(parent_);
  return parent_->key_code();
}

inline bool Composite::key_pressed() const {
  assert(parent_);
  return parent_->key_pressed();
}

#pragma mark Touches

inline const takram::math::Vec2d& Composite::touch() const {
  assert(parent_);
  return parent_->touch();
}

inline const takram::math::Vec2d& Composite::ptouch() const {
  assert(parent_);
  return parent_->ptouch();
}

inline bool Composite::touch_pressed() const {
  assert(parent_);
  return parent_->touch_pressed();
}

#pragma mark Creating tweens

template <class Interval, class... Args>
inline takram::tween::Tween<Interval> Composite::tween(Args&&... args) {
  return timeline_host()->tween<Interval>(std::forward<Args>(args)...);
}

template <class Interval, class... Args>
inline takram::tween::Timer<Interval> Composite::timer(Args&&... args) {
  return timeline_host()->timer<Interval>(std::forward<Args>(args)...);
}

#pragma mark Accessing timeline

template <class Interval>
inline takram::tween::Timeline<Interval>& Composite::timeline() {
  return timeline_host()->timeline<Interval>();
}

template <class Interval>
inline const takram::tween::Timeline<Interval>& Composite::timeline() const {
  return timeline_host()->timeline<Interval>();
}

#pragma mark Aggregation

inline Composite * Composite::parent() const {
  assert(parent_);
  return parent_;
}

inline takram::tween::TimelineHost * Composite::timeline_host() {
  assert(parent_);
  return parent_->timeline_host();
}

inline const takram::tween::TimelineHost * Composite::timeline_host() const {
  assert(parent_);
  return parent_->timeline_host();
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_COMPOSITE_H_
