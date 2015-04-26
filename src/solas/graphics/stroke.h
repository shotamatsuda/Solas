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

class Stroke final {
 public:
  using Real = double;

 public:
  enum class Type {
    NONE,
    SOLID
  };

  enum class Cap {
    SQUARE,
    PROJECT,
    ROUND
  };

  enum class Join {
    MITER,
    BEVEL,
    ROUND
  };

 public:
  // Constructors
  Stroke();
  Stroke(const Color4<Real>& color, Real weight);
  Stroke(const Color4<Real>& color, Real weight,
         Stroke::Cap cap, Stroke::Join join);

  // Copy and assign
  Stroke(const Stroke& other) = default;
  Stroke(Stroke&& other) = default;
  Stroke& operator=(const Stroke& other) = default;
  Stroke& operator=(Stroke&& other) = default;

  // Comparison
  bool operator==(const Stroke& other) const;
  bool operator!=(const Stroke& other) const;

  // Conversion
  operator bool() const { return type != Stroke::Type::NONE; }

 public:
  Stroke::Type type;
  Color4<Real> color;
  Real weight;
  Stroke::Cap cap;
  Stroke::Join join;
};

#pragma mark -

inline Stroke::Stroke()
    : type(Stroke::Type::NONE),
      weight(),
      cap(Stroke::Cap::SQUARE),
      join(Stroke::Join::MITER) {}

inline Stroke::Stroke(const Color4<Real>& color, Real weight)
    : type(Stroke::Type::SOLID),
      color(color),
      weight(weight),
      cap(Stroke::Cap::SQUARE),
      join(Stroke::Join::MITER) {}

inline Stroke::Stroke(const Color4<Real>& color, Real weight,
                      Stroke::Cap cap, Stroke::Join join)
    : type(Stroke::Type::SOLID),
      color(color),
      weight(weight),
      cap(cap),
      join(join) {}

#pragma mark Comparison

inline bool Stroke::operator==(const Stroke& other) const {
  return (type == other.type && weight == other.weight &&
          cap == other.cap && join == other.join);
}

inline bool Stroke::operator!=(const Stroke& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_STROKE_H_
