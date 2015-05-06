//
//  solas/graphics/contour.h
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//  Copyright (C) 2015 takram design engineering
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
#ifndef SOLAS_GRAPHICS_CONTOUR_H_
#define SOLAS_GRAPHICS_CONTOUR_H_

#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

#include "solas/graphics/segment.h"
#include "solas/math/vector.h"

namespace solas {
namespace graphics {

class Contour final {
 public:
  using Real = double;
  using Point = math::Vec2<Real>;
  using Iterator = std::vector<Segment>::iterator;
  using ConstIterator = std::vector<Segment>::const_iterator;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 public:
  enum class Direction {
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

 public:
  // Constructors
  Contour() = default;
  explicit Contour(const std::vector<Segment>& segments);

  // Copy and assign
  Contour(const Contour& other) = default;
  Contour& operator=(const Contour& other) = default;

  // Mutators
  void set(const std::vector<Segment>& segments);
  void reset();

  // Comparison
  bool operator==(const Contour& other) const;
  bool operator!=(const Contour& other) const;

  // Attributes
  bool empty() const { return segments_.empty(); }
  std::size_t size() const { return size(); }

  // Properties
  const std::vector<Segment>& segments() const { return segments_; }
  std::vector<Segment>& segments() { return segments_; }

  // Adding segments
  void close();
  void moveTo(Real x, Real y);
  void moveTo(const Point& point);
  void lineTo(Real x, Real y);
  void lineTo(const Point& point);
  void quadraticTo(Real cx, Real cy, Real x, Real y);
  void quadraticTo(const Point& control, const Point& point);
  void cubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y);
  void cubicTo(const Point& control1,
               const Point& control2,
               const Point& point);

  // Direction
  Direction direction() const;
  Contour& reverse();
  Contour reversed() const;

  // Iterator
  Iterator begin() { return segments_.begin(); }
  ConstIterator begin() const { return segments_.begin(); }
  Iterator end() { return segments_.end(); }
  ConstIterator end() const { return segments_.end(); }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

  // Pointer
  Segment * ptr() { return segments_.data(); }
  const Segment * ptr() const { return segments_.data(); }

 private:
  std::vector<Segment> segments_;
};

#pragma mark -

inline Contour::Contour(const std::vector<Segment>& segments)
    : segments_(segments) {}

#pragma mark Mutators

inline void Contour::set(const std::vector<Segment>& segments) {
  segments_ = segments;
}

inline void Contour::reset() {
  segments_.clear();
}

#pragma mark Comparison

inline bool Contour::operator==(const Contour& other) const {
  return segments_ == other.segments_;
}

inline bool Contour::operator!=(const Contour& other) const {
  return !operator==(other);
}

#pragma mark Adding segments

inline void Contour::close() {
  segments_.emplace_back(Segment::Type::CLOSE);
}

inline void Contour::moveTo(Real x, Real y) {
  moveTo(Point(x, y));
}

inline void Contour::moveTo(const Point& point) {
  segments_.clear();
  segments_.emplace_back(Segment::Type::MOVE, point);
}

inline void Contour::lineTo(Real x, Real y) {
  lineTo(Point(x, y));
}

inline void Contour::lineTo(const Point& point) {
  if (segments_.empty()) {
    moveTo(point);
  } else {
    segments_.emplace_back(Segment::Type::LINE, point);
  }
}

inline void Contour::quadraticTo(Real cx, Real cy, Real x, Real y) {
  quadraticTo(Point(cx, cy), Point(x, y));
}

inline void Contour::quadraticTo(const Point& control, const Point& point) {
  if (segments_.empty()) {
    moveTo(point);
  } else {
    segments_.emplace_back(Segment::Type::QUADRATIC, control, point);
  }
}

inline void Contour::cubicTo(Real cx1, Real cy1,
                             Real cx2, Real cy2,
                             Real x, Real y) {
  cubicTo(Point(cx1, cy1), Point(cx2, cy2), Point(x, y));
}

inline void Contour::cubicTo(const Point& control1,
                             const Point& control2,
                             const Point& point) {
  if (segments_.empty()) {
    moveTo(point);
  } else {
    segments_.emplace_back(Segment::Type::CUBIC, control1, control2, point);
  }
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_CONTOUR_H_
