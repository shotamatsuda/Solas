//
//  solas/app/layer.h
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
#ifndef SOLAS_APP_LAYER_H_
#define SOLAS_APP_LAYER_H_

#include <cassert>
#include <cstdint>
#include <utility>

#include "solas/app/mouse_button.h"
#include "solas/math/vector.h"
#include "solas/tween.h"

namespace solas {
namespace app {

class Layer {
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

inline Layer::Layer() : parent_(nullptr) {}

inline Layer::Layer(Layer *parent) : parent_(parent) {
  assert(parent);
}

inline Layer::Layer(Layer&& other) : parent_(other.parent_) {
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

inline double Layer::scale() const {
  assert(parent_);
  return parent_->scale();
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
