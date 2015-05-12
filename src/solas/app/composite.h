//
//  solas/app/composite.h
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
#ifndef SOLAS_APP_COMPOSITE_H_
#define SOLAS_APP_COMPOSITE_H_

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "solas/app/mouse_button.h"
#include "solas/math/vector.h"
#include "solas/tween/timeline.h"
#include "solas/tween/timeline_host.h"
#include "solas/tween/tween.h"

namespace solas {
namespace app {

class Composite {
 public:
  // Constructors
  explicit Composite(Composite *parent);
  virtual ~Composite() = 0;

  // Disallow copy and assign
  Composite(const Composite& other) = delete;
  Composite& operator=(const Composite& other) = delete;

  // Move
  Composite(Composite&& other);

  // Structure
  virtual double width() const;
  virtual double height() const;
  virtual double scale() const;

  // Mouse
  virtual const math::Vec2d& mouse() const;
  virtual const math::Vec2d& pmouse() const;
  virtual MouseButton mouse_button() const;
  virtual bool mouse_pressed() const;

  // Keyboard
  virtual char key() const;
  virtual std::uint32_t key_code() const;
  virtual bool key_pressed() const;

  // Touches
  virtual const math::Vec2d& touch() const;
  virtual const math::Vec2d& ptouch() const;
  virtual bool touch_pressed() const;

  // Creating tweens
  template <typename Interval, typename... Args>
  tween::Tween<Interval> tween(Args&&... args);

  // Accessing timeline
  template <typename Interval>
  tween::Timeline<Interval>& timeline();
  template <typename Interval>
  const tween::Timeline<Interval>& timeline() const;

  // Aggregation
  virtual Composite * parent() const;

 protected:
  // Constructors
  Composite();

  // Aggregation
  virtual tween::TimelineHost * timeline_host();
  virtual const tween::TimelineHost * timeline_host() const;

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

inline const math::Vec2d& Composite::mouse() const {
  assert(parent_);
  return parent_->mouse();
}

inline const math::Vec2d& Composite::pmouse() const {
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

inline const math::Vec2d& Composite::touch() const {
  assert(parent_);
  return parent_->touch();
}

inline const math::Vec2d& Composite::ptouch() const {
  assert(parent_);
  return parent_->ptouch();
}

inline bool Composite::touch_pressed() const {
  assert(parent_);
  return parent_->touch_pressed();
}

#pragma mark Creating tweens

template <typename Interval, typename... Args>
inline tween::Tween<Interval> Composite::tween(Args&&... args) {
  return timeline_host()->tween<Interval>(std::forward<Args>(args)...);
}

#pragma mark Accessing timeline

template <typename Interval>
inline tween::Timeline<Interval>& Composite::timeline() {
  return timeline_host()->timeline<Interval>();
}

template <typename Interval>
inline const tween::Timeline<Interval>& Composite::timeline() const {
  return timeline_host()->timeline<Interval>();
}

#pragma mark Aggregation

inline Composite * Composite::parent() const {
  assert(parent_);
  return parent_;
}

inline tween::TimelineHost * Composite::timeline_host() {
  assert(parent_);
  return parent_->timeline_host();
}

inline const tween::TimelineHost * Composite::timeline_host() const {
  assert(parent_);
  return parent_->timeline_host();
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_COMPOSITE_H_
