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
#include <utility>
#include <vector>

#include "solas/graphics/contour.h"
#include "solas/graphics/segment.h"
#include "solas/math/vector.h"
#include "solas/utility/tree_iterator.h"

class SkPath;

namespace solas {
namespace graphics {

class Path final {
 public:
  using Real = double;
  using Point = math::Vec2<Real>;
  using Iterator = utility::TreeIterator<
      Segment,
      std::vector<Contour>::iterator,
      Contour::Iterator>;
  using ConstIterator = utility::TreeIterator<
      const Segment,
      std::vector<Contour>::const_iterator,
      Contour::ConstIterator>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 public:
  // Constructors
  Path() = default;
  explicit Path(const std::vector<Contour>& contours);

  // Implicit conversion
  Path(const SkPath& path);

  // Copy and assign
  Path(const Path& other) = default;
  Path& operator=(const Path& other) = default;

  // Mutators
  void set(const std::vector<Contour>& contours);
  void set(const SkPath& path);
  void reset();

  // Comparison
  bool operator==(const Path& other) const;
  bool operator!=(const Path& other) const;

  // Attributes
  bool empty() const { return contours_.empty(); }
  std::size_t size() const { return contours_.size(); }

  // Properties
  const std::vector<Contour>& contours() const { return contours_; }
  std::vector<Contour>& contours() { return contours_; }

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

  // Implicit conversion
  operator SkPath() const;

  // Element access
  Contour& operator[](int index) { return contours_.at(index); }
  const Contour& operator[](int index) const { return contours_.at(index); }
  Contour& at(int index) { return contours_.at(index); }
  const Contour& at(int index) const { return contours_.at(index); }
  Contour& front() { return contours_.front(); }
  const Contour& front() const { return contours_.front(); }
  Contour& back() { return contours_.back(); }
  const Contour& back() const { return contours_.back(); }

  // Iterator
  Iterator begin();
  ConstIterator begin() const;
  Iterator end();
  ConstIterator end() const;
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

 private:
  std::vector<Contour> contours_;
};

#pragma mark -

inline Path::Path(const std::vector<Contour>& contours)
    : contours_(contours) {}

#pragma mark Implicit conversion

inline Path::Path(const SkPath& path) {
  set(path);
}

#pragma mark Mutators

inline void Path::set(const std::vector<Contour>& contours) {
  contours_ = contours;
}

inline void Path::reset() {
  contours_.clear();
}

#pragma mark Comparison

inline bool Path::operator==(const Path& other) const {
  return contours_ == other.contours_;
}

inline bool Path::operator!=(const Path& other) const {
  return !operator==(other);
}

#pragma mark Configuring segments

inline void Path::close() {
  if (!contours_.empty()) {
    contours_.back().close();
  }
}

inline void Path::moveTo(Real x, Real y) {
  contours_.emplace_back();
  contours_.back().moveTo(x, y);
}

inline void Path::moveTo(const Point& point) {
  contours_.emplace_back();
  contours_.back().moveTo(point);
}

inline void Path::lineTo(Real x, Real y) {
  if (!contours_.empty()) {
    contours_.back().lineTo(x, y);
  }
}

inline void Path::lineTo(const Point& point) {
  if (!contours_.empty()) {
    contours_.back().lineTo(point);
  }
}

inline void Path::quadraticTo(Real cx, Real cy, Real x, Real y) {
  if (!contours_.empty()) {
    contours_.back().quadraticTo(cx, cy, x, y);
  }
}

inline void Path::quadraticTo(const Point& control, const Point& point) {
  if (!contours_.empty()) {
    contours_.back().quadraticTo(control, point);
  }
}

inline void Path::cubicTo(Real cx1, Real cy1,
                          Real cx2, Real cy2,
                          Real x, Real y) {
  if (!contours_.empty()) {
    contours_.back().cubicTo(cx1, cy1, cx2, cy2, x, y);
  }
}

inline void Path::cubicTo(const Point& control1,
                          const Point& control2,
                          const Point& point) {
  if (!contours_.empty()) {
    contours_.back().cubicTo(control1, control2, point);
  }
}

#pragma mark Iterator

inline Path::Iterator Path::begin() {
  return Iterator(contours_.begin(), contours_.end());
}

inline Path::ConstIterator Path::begin() const {
  return ConstIterator(contours_.begin(), contours_.end());
}

inline Path::Iterator Path::end() {
  return Iterator(contours_.end(), contours_.end());
}

inline Path::ConstIterator Path::end() const {
  return ConstIterator(contours_.end(), contours_.end());
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_PATH_H_
