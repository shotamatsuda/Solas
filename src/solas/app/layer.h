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

#include "solas/app/mouse_button.h"
#include "solas/math/vector.h"

namespace solas {
namespace app {

class Layer {
 public:
  // Constructors
  explicit Layer(Layer *parent);

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
  virtual double mouse_x() const;
  virtual double mouse_y() const;
  virtual const math::Vec2d& pmouse() const;
  virtual double pmouse_x() const;
  virtual double pmouse_y() const;
  virtual MouseButton mouse_button() const;
  virtual bool mouse_pressed() const;

  // Keyboard
  virtual char key() const;
  virtual std::uint32_t key_code() const;
  virtual bool key_pressed() const;

 protected:
  // Constructors
  Layer();

 private:
  Layer *parent_;
};

#pragma mark -

inline Layer::Layer()
    : parent_(nullptr) {}

inline Layer::Layer(Layer *parent)
    : parent_(parent) {}

inline Layer::Layer(Layer&& other)
    : parent_(other.parent_) {
  other.parent_ = nullptr;
}

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

inline double Layer::mouse_x() const {
  assert(parent_);
  return parent_->mouse_x();
}

inline double Layer::mouse_y() const {
  assert(parent_);
  return parent_->mouse_y();
}

inline const math::Vec2d& Layer::pmouse() const {
  assert(parent_);
  return parent_->pmouse();
}

inline double Layer::pmouse_x() const {
  assert(parent_);
  return parent_->pmouse_x();
}

inline double Layer::pmouse_y() const {
  assert(parent_);
  return parent_->pmouse_y();
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

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_LAYER_H_
