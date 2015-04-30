//
//  solas/graphics/path.h
//
//  MIT License
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
#ifndef SOLAS_GRAPHICS_PATH_H_
#define SOLAS_GRAPHICS_PATH_H_

#include <iterator>
#include <vector>

#include "solas/graphics/segment.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

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

  // Copy and assign
  Path(const Path& other) = default;
  Path(Path&& other) = default;
  Path& operator=(const Path& other) = default;
  Path& operator=(Path&& other) = default;

  // Mutators
  void reset();

  // Comparison
  bool operator==(const Path& other) const;
  bool operator!=(const Path& other) const;

  // Attributes
  bool empty() const { return segments_.empty(); }

  // Configuring segments
  void close();
  void moveTo(Real x, Real y);
  void moveTo(const math::Vec2<Real>& point);
  void lineTo(Real x, Real y);
  void lineTo(const math::Vec2<Real>& point);
  void curveTo(Real x, Real y);
  void curveTo(const math::Vec2<Real>& point);
  void quadraticTo(Real cx, Real cy, Real x, Real y);
  void quadraticTo(const math::Vec2<Real>& control,
                   const math::Vec2<Real>& point);
  void bezierTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y);
  void bezierTo(const math::Vec2<Real>& control1,
                const math::Vec2<Real>& control2,
                const math::Vec2<Real>& point);

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

inline void Path::curveTo(Real x, Real y) {
  curveTo({x, y});
}

inline void Path::curveTo(const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::CURVE, point);
}

inline void Path::quadraticTo(Real cx, Real cy, Real x, Real y) {
  quadraticTo({cx, cy}, {x, y});
}

inline void Path::quadraticTo(const math::Vec2<Real>& control,
                              const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::QUADRATIC, control, point);
}

inline void Path::bezierTo(Real cx1, Real cy1,
                           Real cx2, Real cy2,
                           Real x, Real y) {
  bezierTo({cx1, cy1}, {cx2, cy2}, {x, y});
}

inline void Path::bezierTo(const math::Vec2<Real>& control1,
                           const math::Vec2<Real>& control2,
                           const math::Vec2<Real>& point) {
  segments_.emplace_back(Segment::Type::BEZIER, control1, control2, point);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_PATH_H_
