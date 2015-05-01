//
//  solas/graphics/segment.h
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
