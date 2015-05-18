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
  using Point = math::Vec2<Real>;

 public:
  enum class Type {
    MOVE,
    LINE,
    QUADRATIC,
    CUBIC,
    CLOSE
  };

 public:
  // Constructors
  explicit Segment(Type type);
  Segment(Type type, const math::Vec2<Real>& point);
  Segment(Type type, const Point& control, const Point& point);
  Segment(Type type,
          const Point& control1,
          const Point& control2,
          const Point& point);

  // Copy and assign
  Segment(const Segment& other) = default;
  Segment(Segment&& other) = default;
  Segment& operator=(const Segment& other) = default;
  Segment& operator=(Segment&& other) = default;

  // Comparison
  bool operator==(const Segment& other) const;
  bool operator!=(const Segment& other) const;

  // Properties
  Type type() const { return type_; }
  const Point& control() const { return control1_; }
  Point& control() { return control1_; }
  const Point& control1() const { return control1_; }
  Point& control1() { return control1_; }
  const Point& control2() const { return control2_; }
  Point& control2() { return control2_; }
  const Point& point() const { return point_; }
  Point& point() { return point_; }

 private:
  Type type_;
  Point control1_;
  Point control2_;
  Point point_;
};

#pragma mark -

inline Segment::Segment(Type type) : type_(type) {}

inline Segment::Segment(Type type, const Point& point)
    : type_(type),
      point_(point) {}

inline Segment::Segment(Type type, const Point& control, const Point& point)
    : type_(type),
      control1_(control),
      point_(point) {}

inline Segment::Segment(Type type,
                        const Point& control1,
                        const Point& control2,
                        const Point& point)
    : type_(type),
      control1_(control1),
      control2_(control2),
      point_(point) {}

#pragma mark Comparison

inline bool Segment::operator==(const Segment& other) const {
  return (type_ == other.type_ &&
          control1_ == other.control1_ &&
          control2_ == other.control2_ &&
          point_ == other.point_);
}

inline bool Segment::operator!=(const Segment& other) const {
  return !operator==(other);
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_SEGMENT_H_
