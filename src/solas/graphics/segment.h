//
//  solas/graphics/segment.h
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
#ifndef SOLAS_GRAPHICS_SEGMENT_H_
#define SOLAS_GRAPHICS_SEGMENT_H_

#include "solas/math/vector.h"

namespace solas {
namespace graphics {

class Segment final {
 public:
  using Real = double;

 public:
  enum class Type {
    MOVE,
    LINE,
    CURVE,
    QUADRATIC,
    BEZIER,
    CLOSE
  };

 public:
  // Constructors
  explicit Segment(Type type);
  Segment(Type type, const math::Vec2<Real>& point);
  Segment(Type type,
          const math::Vec2<Real>& control,
          const math::Vec2<Real>& point);
  Segment(Type type,
          const math::Vec2<Real>& control1,
          const math::Vec2<Real>& control2,
          const math::Vec2<Real>& point);
  Segment(Type type,
          const math::Vec2<Real>& center,
          const math::Vec2<Real>& radius,
          Real start_angle,
          Real stop_angle);

  // Copy and move
  Segment(const Segment& other) = default;
  Segment(Segment&& other) = default;

  // Disallow assign
  Segment& operator=(const Segment& other) = delete;

  // Comparison
  bool operator==(const Segment& other) const;
  bool operator!=(const Segment& other) const;

 public:
  const Type type;
  const union {
    struct {
      math::Vec2<Real> control1;
      math::Vec2<Real> control2;
      math::Vec2<Real> point;
    };
    struct {
      math::Vec2<Real> center;
      math::Vec2<Real> radius;
      Real start_angle;
      Real stop_angle;
    };
  };
};

#pragma mark -

inline Segment::Segment(Type type)
    : type(type),
      control1(),
      control2(),
      point() {}

inline Segment::Segment(Type type, const math::Vec2<Real>& point)
    : type(type),
      control1(),
      control2(),
      point(point) {}

inline Segment::Segment(Type type,
                        const math::Vec2<Real>& control,
                        const math::Vec2<Real>& point)
    : type(type),
      control1(control),
      control2(control),
      point(point) {}

inline Segment::Segment(Type type,
                        const math::Vec2<Real>& control1,
                        const math::Vec2<Real>& control2,
                        const math::Vec2<Real>& point)
    : type(type),
      control1(control1),
      control2(control2),
      point(point) {}

inline Segment::Segment(Type type,
                        const math::Vec2<Real>& center,
                        const math::Vec2<Real>& radius,
                        Real start_angle,
                        Real stop_angle)
    : type(type),
      center(center),
      radius(radius),
      start_angle(start_angle),
      stop_angle(stop_angle) {}

#pragma mark Comparison

inline bool Segment::operator==(const Segment& other) const {
  return (type == other.type &&
          control1 == other.control1 &&
          control2 == other.control2 &&
          point == other.point);
}

inline bool Segment::operator!=(const Segment& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_SEGMENT_H_
