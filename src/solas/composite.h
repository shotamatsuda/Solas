//
//  solas/composite.h
//
//  The MIT License
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
#ifndef SOLAS_COMPOSITE_H_
#define SOLAS_COMPOSITE_H_

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "solas/mouse_button.h"
#include "solas/math.h"

namespace solas {

class Composite {
 public:
  explicit Composite(Composite *parent);
  virtual ~Composite() = 0;

  // Disallow copy semantics
  Composite(const Composite&) = delete;
  Composite& operator=(const Composite&) = delete;

  // Move semantics
  Composite(Composite&& other);
  Composite& operator=(Composite&& other);

  // Environment
  virtual void frameRate(double fps) const;
  virtual void resize(const Size2d& size) const;
  virtual void resize(double width, double height) const;
  virtual void fullscreen(bool flag) const;

  // Structure
  virtual const Size2d& size() const;
  virtual double width() const;
  virtual double height() const;
  virtual double scale() const;

  // Mouse
  virtual const Vec2d& mouse() const;
  virtual const Vec2d& pmouse() const;
  virtual MouseButton mouse_button() const;
  virtual bool mouse_pressed() const;

  // Key
  virtual char key() const;
  virtual std::uint32_t key_code() const;
  virtual bool key_pressed() const;

  // Touches
  virtual const Vec2d& touch() const;
  virtual const Vec2d& ptouch() const;
  virtual bool touch_pressed() const;

  // Aggregation
  virtual Composite * parent() const;

 protected:
  Composite();

 private:
  Composite *parent_;
};

#pragma mark -

inline Composite::Composite() : parent_(nullptr) {}

inline Composite::Composite(Composite *parent) : parent_(parent) {
  assert(parent);
}

inline Composite::~Composite() {}

#pragma mark Move semantics

inline Composite::Composite(Composite&& other) : parent_(other.parent_) {
  other.parent_ = nullptr;
}

inline Composite& Composite::operator=(Composite&& other) {
  if (&other != this) {
    std::swap(parent_, other.parent_);
  }
  return *this;
}

#pragma mark Environment

inline void Composite::frameRate(double fps) const {
  assert(parent_);
  return parent_->frameRate(fps);
}

inline void Composite::resize(const Size2d& size) const {
  assert(parent_);
  return parent_->resize(size);
}

inline void Composite::resize(double width, double height) const {
  assert(parent_);
  return parent_->resize(width, height);
}

inline void Composite::fullscreen(bool flag) const {
  assert(parent_);
  return parent_->fullscreen(flag);
}

#pragma mark Structure

inline const Size2d& Composite::size() const {
  assert(parent_);
  return parent_->size();
}

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

inline const Vec2d& Composite::mouse() const {
  assert(parent_);
  return parent_->mouse();
}

inline const Vec2d& Composite::pmouse() const {
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

#pragma mark Key

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

inline const Vec2d& Composite::touch() const {
  assert(parent_);
  return parent_->touch();
}

inline const Vec2d& Composite::ptouch() const {
  assert(parent_);
  return parent_->ptouch();
}

inline bool Composite::touch_pressed() const {
  assert(parent_);
  return parent_->touch_pressed();
}

#pragma mark Aggregation

inline Composite * Composite::parent() const {
  assert(parent_);
  return parent_;
}

}  // namespace solas

#endif  // SOLAS_COMPOSITE_H_
