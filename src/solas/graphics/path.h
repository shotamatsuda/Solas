//
//  solas/graphics/path.h
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
#ifndef SOLAS_GRAPHICS_PATH_H_
#define SOLAS_GRAPHICS_PATH_H_

#include <cstddef>
#include <iterator>
#include <vector>

#include "solas/graphics/segment.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

class SkPath;

namespace solas {
namespace graphics {

class Path final {
 public:
  using Real = double;
  using Iterator = std::vector<Segment>::iterator;
  using ConstIterator = std::vector<Segment>::const_iterator;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 public:
  // Constructors
  Path() = default;

  // Implicit conversion
  Path(const SkPath& path);

  // Copy and assign
  Path(const Path& other) = default;
  Path(Path&& other) = default;
  Path& operator=(const Path& other) = default;
  Path& operator=(Path&& other) = default;

  // Mutators
  void reset();
  void set(const SkPath& path);

  // Comparison
  bool operator==(const Path& other) const;
  bool operator!=(const Path& other) const;

  // Attributes
  bool empty() const { return segments_.empty(); }
  std::size_t size() const { return size(); }

  // Configuring segments
  void close();
  void moveTo(Real x, Real y);
  void moveTo(const math::Vec2<Real>& point);
  void lineTo(Real x, Real y);
  void lineTo(const math::Vec2<Real>& point);
  void quadraticTo(Real cx, Real cy, Real x, Real y);
  void quadraticTo(const math::Vec2<Real>& control,
                   const math::Vec2<Real>& point);
  void cubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y);
  void cubicTo(const math::Vec2<Real>& control1,
               const math::Vec2<Real>& control2,
               const math::Vec2<Real>& point);

  // Implicit conversion
  operator SkPath() const;

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

#pragma mark Implicit conversion

inline Path::Path(const SkPath& path) {
  set(path);
}

#pragma mark Mutators

inline void Path::reset() {
  segments_.clear();
}

#pragma mark Comparison

inline bool Path::operator==(const Path& other) const {
  return segments_ == other.segments_;
}

inline bool Path::operator!=(const Path& other) const {
  return !operator==(other);
}

#pragma mark Configuring segments

inline void Path::close() {
  segments_.emplace_back(Segment::Type::CLOSE);
}

inline void Path::moveTo(Real x, Real y) {
  moveTo({x, y});
}

inline void Path::moveTo(const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::MOVE, point);
}

inline void Path::lineTo(Real x, Real y) {
  lineTo({x, y});
}

inline void Path::lineTo(const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::LINE, point);
}

inline void Path::quadraticTo(Real cx, Real cy, Real x, Real y) {
  quadraticTo({cx, cy}, {x, y});
}

inline void Path::quadraticTo(const math::Vec2<Real>& control,
                              const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::QUADRATIC, control, point);
}

inline void Path::cubicTo(Real cx1, Real cy1,
                          Real cx2, Real cy2,
                          Real x, Real y) {
  cubicTo({cx1, cy1}, {cx2, cy2}, {x, y});
}

inline void Path::cubicTo(const math::Vec2<Real>& control1,
                          const math::Vec2<Real>& control2,
                          const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::CUBIC, control1, control2, point);
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_PATH_H_
