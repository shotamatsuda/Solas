//
//  solas/app/layer.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
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
#ifndef SOLAS_APP_LAYER_H_
#define SOLAS_APP_LAYER_H_

#include <cassert>
#include <cstdint>
#include <utility>

#include "solas/app/mouse_button.h"
#include "solas/app/utilities.h"
#include "solas/math/vector.h"
#include "solas/tween.h"

namespace solas {
namespace app {

class Layer : public Utilities {
 public:
  using Time = tween::Time;
  using Frame = tween::Frame;
  using Easing = tween::Easing;
  using BackEasing = tween::BackEasing;
  using BounceEasing = tween::BounceEasing;
  using CircularEasing = tween::CircularEasing;
  using CubicEasing = tween::CubicEasing;
  using ElasticEasing = tween::ElasticEasing;
  using ExponentialEasing = tween::ExponentialEasing;
  using LinearEasing = tween::LinearEasing;
  using QuadraticEasing = tween::QuadraticEasing;
  using QuarticEasing = tween::QuarticEasing;
  using QuinticEasing = tween::QuinticEasing;
  using SinusoidalEasing = tween::SinusoidalEasing;

 public:
  // Constructors
  explicit Layer(Layer *parent);
  virtual ~Layer() = 0;

  // Disallow copy and assign
  Layer(const Layer& other) = delete;
  Layer& operator=(const Layer& other) = delete;

  // Move
  Layer(Layer&& other);

  // Structure
  virtual double width() const;
  virtual double height() const;

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
  Layer& parent();
  const Layer& parent() const;

 protected:
  // Constructors
  Layer();

  // Aggregation
  virtual tween::TimelineHost * timeline_host();
  virtual const tween::TimelineHost * timeline_host() const;

 private:
  Layer *parent_;
};

#pragma mark -

inline Layer::Layer()
    : parent_(nullptr) {}

inline Layer::Layer(Layer *parent)
    : parent_(parent) {
  assert(parent);
}

inline Layer::Layer(Layer&& other)
    : parent_(other.parent_) {
  other.parent_ = nullptr;
}

inline Layer::~Layer() {}

#pragma mark Structure

inline double Layer::width() const {
  assert(parent_);
  return parent_->width();
}

inline double Layer::height() const {
  assert(parent_);
  return parent_->height();
}

#pragma mark Mouse

inline const math::Vec2d& Layer::mouse() const {
  assert(parent_);
  return parent_->mouse();
}

inline const math::Vec2d& Layer::pmouse() const {
  assert(parent_);
  return parent_->pmouse();
}

inline MouseButton Layer::mouse_button() const {
  assert(parent_);
  return parent_->mouse_button();
}

inline bool Layer::mouse_pressed() const {
  assert(parent_);
  return parent_->mouse_pressed();
}

#pragma mark Keyboard

inline char Layer::key() const {
  assert(parent_);
  return parent_->key();
}

inline std::uint32_t Layer::key_code() const {
  assert(parent_);
  return parent_->key_code();
}

inline bool Layer::key_pressed() const {
  assert(parent_);
  return parent_->key_pressed();
}

#pragma mark Touches

inline const math::Vec2d& Layer::touch() const {
  assert(parent_);
  return parent_->touch();
}

inline const math::Vec2d& Layer::ptouch() const {
  assert(parent_);
  return parent_->ptouch();
}

inline bool Layer::touch_pressed() const {
  assert(parent_);
  return parent_->touch_pressed();
}

#pragma mark Creating tweens

template <typename Interval, typename... Args>
inline tween::Tween<Interval> Layer::tween(Args&&... args) {
  return timeline_host()->tween<Interval>(std::forward<Args>(args)...);
}

#pragma mark Accessing timeline

template <typename Interval>
inline tween::Timeline<Interval>& Layer::timeline() {
  return timeline_host()->timeline<Interval>();
}

template <typename Interval>
inline const tween::Timeline<Interval>& Layer::timeline() const {
  return timeline_host()->timeline<Interval>();
}

#pragma mark Aggregation

inline Layer& Layer::parent() {
  assert(parent_);
  return *parent_;
}

inline const Layer& Layer::parent() const {
  assert(parent_);
  return *parent_;
}

inline tween::TimelineHost * Layer::timeline_host() {
  assert(parent_);
  return parent_->timeline_host();
}

inline const tween::TimelineHost * Layer::timeline_host() const {
  assert(parent_);
  return parent_->timeline_host();
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_LAYER_H_
