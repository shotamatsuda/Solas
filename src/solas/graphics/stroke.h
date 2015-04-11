//
//  solas/graphics/stroke.h
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
#ifndef SOLAS_GRAPHICS_STROKE_H_
#define SOLAS_GRAPHICS_STROKE_H_

#include "solas/graphics/color.h"

namespace solas {
namespace graphics {

enum class StrokeType {
  NONE,
  SOLID
};

enum class StrokeCap {
  SQUARE,
  PROJECT,
  ROUND
};

enum class StrokeJoin {
  MITER,
  BEVEL,
  ROUND
};

template <typename T>
class Stroke {
 public:
  using Type = T;

 public:
  // Constructors
  Stroke();
  Stroke(const Color4<T>& color, T weight);
  Stroke(const Color4<T>& color, T weight, StrokeCap cap, StrokeJoin join);

  // Copy and assign
  Stroke(const Stroke& other) = default;
  Stroke(Stroke&& other) = default;
  Stroke& operator=(const Stroke& other) = default;
  Stroke& operator=(Stroke&& other) = default;

  // Comparison
  bool operator==(const Stroke& other) const;
  bool operator!=(const Stroke& other) const;

  // Conversion
  operator bool() const { return type != StrokeType::NONE; }

 public:
  StrokeType type;
  Color4<T> color;
  T weight;
  StrokeCap cap;
  StrokeJoin join;
};

#pragma mark -

template <typename T>
inline Stroke<T>::Stroke()
    : type(StrokeType::NONE),
      weight(),
      cap(StrokeCap::SQUARE),
      join(StrokeJoin::MITER) {}

template <typename T>
inline Stroke<T>::Stroke(const Color4<T>& color, T weight)
    : type(StrokeType::SOLID),
      color(color),
      weight(weight),
      cap(StrokeCap::SQUARE),
      join(StrokeJoin::MITER) {}

template <typename T>
inline Stroke<T>::Stroke(const Color4<T>& color, T weight,
                         StrokeCap cap, StrokeJoin join)
    : type(StrokeType::SOLID),
      color(color),
      weight(weight),
      cap(cap),
      join(join) {}

#pragma mark Comparison

template <typename T>
inline bool Stroke<T>::operator==(const Stroke& other) const {
  return (type == other.type && weight == other.weight &&
          cap == other.cap && join == other.join);
}

template <typename T>
inline bool Stroke<T>::operator!=(const Stroke& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_STROKE_H_
