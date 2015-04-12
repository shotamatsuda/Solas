//
//  solas/math/rect.h
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
#ifndef SOLAS_MATH_RECT_H_
#define SOLAS_MATH_RECT_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ostream>

#include "solas/math/promotion.h"
#include "solas/math/size.h"
#include "solas/math/vector.h"
#include "solas/utility/enablers.h"

namespace solas {
namespace math {

template <typename T>
class Rect final {
 public:
  using Type = T;

 public:
  // Constructors
  Rect();
  explicit Rect(const Vector2<T>& origin);
  explicit Rect(const Size2<T>& size);
  Rect(T x, T y, T width, T height);
  Rect(T x, T y, const Size2<T>& size);
  Rect(const Vector2<T>& origin, T width, T height);
  Rect(const Vector2<T>& origin, const Size2<T>& size);
  Rect(const Vector2<T>& p1, const Vector2<T>& p2);

  // Implicit conversion
  template <typename U>
  Rect(const Rect<U>& other);

  // Copy and assign
  Rect(const Rect& other);
  Rect& operator=(const Rect& other);

  // Mutators
  void set(const Vector2<T>& origin);
  void set(const Size2<T>& size);
  void set(T x, T y, T width, T height);
  void set(const Vector2<T>& origin, const Size2<T>& size);
  void set(T x, T y, const Size2<T>& size);
  void set(const Vector2<T>& origin, T width, T height);
  void set(const Vector2<T>& p1, const Vector2<T>& p2);
  void reset();

  // Comparison
  template <typename U>
  bool operator==(const Rect<U>& other) const;
  template <typename U>
  bool operator!=(const Rect<U>& other) const;
  template <typename U>
  bool operator<(const Rect<U>& other) const;
  template <typename U>
  bool operator>(const Rect<U>& other) const;
  template <typename U>
  bool operator<=(const Rect<U>& other) const;
  template <typename U>
  bool operator>=(const Rect<U>& other) const;

  // Scalar arithmetic
  Rect& operator*=(T scalar);
  Rect& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Rect<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Rect<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return size.empty(); }
  Promote<T> aspect() const;
  Promote<T> diagonal() const;
  Promote<T> area() const;
  Promote<T> circumference() const;
  Vector2<Promote<T>> centroid() const;

  // Edges
  T min_x() const;
  T max_x() const;
  T min_y() const;
  T max_y() const;
  T left() const;
  T right() const;
  T top() const;
  T bottom() const;

  // Corners
  Vector2<T> top_left() const;
  Vector2<T> top_right() const;
  Vector2<T> bottom_left() const;
  Vector2<T> bottom_right() const;
  Vector2<T> tl() const { return top_left(); }
  Vector2<T> tr() const { return top_right(); }
  Vector2<T> bl() const { return bottom_left(); }
  Vector2<T> br() const { return bottom_right(); }

  // Canonicalization
  bool canonical() const { return width > 0 && height > 0; }
  Rect& canonicalize();
  Rect<Promote<T>> canonicalized() const;

  // Translation
  Rect& translate(T offset);
  Rect& translate(T dx, T dy);
  Rect& translate(const Vector2<T>& offset);
  template <typename U>
  Rect<Promote<T, U>> translated(U offset) const;
  template <typename U>
  Rect<Promote<T, U>> translated(U dx, U dy) const;
  template <typename U>
  Rect<Promote<T, U>> translated(const Vector2<U>& offset) const;

  // Scaling
  Rect& scale(T scale);
  Rect& scale(T sx, T sy);
  Rect& scale(const Vector2<T>& scale);
  template <typename U>
  Rect<Promote<T, U>> scaled(U scale) const;
  template <typename U>
  Rect<Promote<T, U>> scaled(U sx, U sy) const;
  template <typename U>
  Rect<Promote<T, U>> scaled(const Vector2<U>& scale) const;

  // Containment
  template <typename U>
  bool contains(const Vector2<U>& point) const;
  template <typename U>
  bool contains(const Rect<U>& rect) const;

 public:
  union {
    Vector2<T> origin;
    struct { T x; T y; };
  };
  union {
    Size2<T> size;
    struct { T width; T height; };
    struct { T w; T h; };
  };
};

using Recti = Rect<int>;
using Rectf = Rect<float>;
using Rectd = Rect<double>;

#pragma mark -

template <typename T>
inline Rect<T>::Rect()
    : origin(),
      size() {}

template <typename T>
inline Rect<T>::Rect(const Vector2<T>& origin)
    : origin(origin),
      size() {}

template <typename T>
inline Rect<T>::Rect(const Size2<T>& size)
    : origin(),
      size(size) {}

template <typename T>
inline Rect<T>::Rect(T x, T y, T width, T height)
    : origin(x, y),
      size(width, height) {}

template <typename T>
inline Rect<T>::Rect(T x, T y, const Size2<T>& size)
    : origin(x, y),
      size(size) {}

template <typename T>
inline Rect<T>::Rect(const Vector2<T>& origin, T width, T height)
    : origin(origin),
      size(width, height) {}

template <typename T>
inline Rect<T>::Rect(const Vector2<T>& origin, const Size2<T>& size)
    : origin(origin),
      size(size) {}

template <typename T>
inline Rect<T>::Rect(const Vector2<T>& p1, const Vector2<T>& p2)
    : origin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
      size(std::max(p1.x, p2.x) - origin.x, std::max(p1.y, p2.y) - origin.y) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Rect<T>::Rect(const Rect<U>& other)
    : origin(other.origin),
      size(other.size) {}

#pragma mark Copy and assign

template <typename T>
inline Rect<T>::Rect(const Rect<T>& other)
    : origin(other.origin),
      size(other.size) {}

template <typename T>
inline Rect<T>& Rect<T>::operator=(const Rect<T>& other) {
  if (&other != this) {
    origin = other.origin;
    size = other.size;
  }
  return *this;
}

#pragma mark Mutators

template <typename T>
inline void Rect<T>::set(const Vector2<T>& origin) {
  this->origin.set(origin);
}

template <typename T>
inline void Rect<T>::set(const Size2<T>& size) {
  this->size.set(size);
}

template <typename T>
inline void Rect<T>::set(T x, T y, T width, T height) {
  origin.set(x, y);
  size.set(width, height);
}

template <typename T>
inline void Rect<T>::set(const Vector2<T>& origin, const Size2<T>& size) {
  this->origin.set(origin);
  this->size.set(size);
}

template <typename T>
inline void Rect<T>::set(T x, T y, const Size2<T>& size) {
  origin.set(x, y);
  this->size.set(size);
}

template <typename T>
inline void Rect<T>::set(const Vector2<T>& origin, T width, T height) {
  this->origin.set(origin);
  size.set(width, height);
}

template <typename T>
inline void Rect<T>::set(const Vector2<T>& p1, const Vector2<T>& p2) {
  origin.set(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
  size.set(std::max(p1.x, p2.x) - origin.x, std::max(p1.y, p2.y) - origin.y);
}

template <typename T>
inline void Rect<T>::reset() {
  *this = Rect<T>();
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Rect<T>::operator==(const Rect<U>& other) const {
  return origin == other.origin && size == other.size;
}

template <typename T>
template <typename U>
inline bool Rect<T>::operator!=(const Rect<U>& other) const {
  return !operator==(other);
}

template <typename T>
template <typename U>
inline bool Rect<T>::operator<(const Rect<U>& other) const {
  return origin < other.origin || (origin == other.origin && size < other.size);
}

template <typename T>
template <typename U>
inline bool Rect<T>::operator>(const Rect<U>& other) const {
  return origin > other.origin || (origin == other.origin && size > other.size);
}

template <typename T>
template <typename U>
inline bool Rect<T>::operator<=(const Rect<U>& other) const {
  return operator<(other) || operator==(other);
}

template <typename T>
template <typename U>
inline bool Rect<T>::operator>=(const Rect<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Scalar arithmetic

template <typename T>
inline Rect<T>& Rect<T>::operator*=(T scalar) {
  return scale(scalar);
}

template <typename T>
inline Rect<T>& Rect<T>::operator/=(T scalar) {
  assert(scalar);
  return scale(static_cast<Promote<T>>(1) / scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Rect<Promote<T, U>> Rect<T>::operator*(U scalar) const {
  return scaled(scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Rect<Promote<T, U>> Rect<T>::operator/(U scalar) const {
  assert(scalar);
  return scaled(static_cast<Promote<T>>(1) / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Rect<Promote<T, U>> operator*(U scalar, const Rect<T>& rect) {
  return rect * scalar;
}

#pragma mark Attributes

template <typename T>
inline Promote<T> Rect<T>::aspect() const {
  return size.aspect();
}

template <typename T>
inline Promote<T> Rect<T>::diagonal() const {
  return size.diagonal();
}

template <typename T>
inline Promote<T> Rect<T>::area() const {
  return size.area();
}

template <typename T>
inline Promote<T> Rect<T>::circumference() const {
  return 2 * std::abs(Promote<T>(width)) + 2 * std::abs(Promote<T>(height));
}

template <typename T>
inline Vector2<Promote<T>> Rect<T>::centroid() const {
  return origin + Vector2<Promote<T>>(static_cast<Size2<T>>(size) / 2);
}

#pragma mark Edges

template <typename T>
inline T Rect<T>::min_x() const {
  return std::min<T>(x, x + width);
}

template <typename T>
inline T Rect<T>::max_x() const {
  return std::max<T>(x, x + width);
}

template <typename T>
inline T Rect<T>::min_y() const {
  return std::min<T>(y, y + height);
}

template <typename T>
inline T Rect<T>::max_y() const {
  return std::max<T>(y, y + height);
}

template <typename T>
inline T Rect<T>::left() const {
  return min_x();
}

template <typename T>
inline T Rect<T>::right() const {
  return max_x();
}

template <typename T>
inline T Rect<T>::top() const {
  return min_y();
}

template <typename T>
inline T Rect<T>::bottom() const {
  return max_y();
}

#pragma mark Corners

template <typename T>
inline Vector2<T> Rect<T>::top_left() const {
  return Vector2<T>(left(), top());
}

template <typename T>
inline Vector2<T> Rect<T>::top_right() const {
  return Vector2<T>(right(), top());
}

template <typename T>
inline Vector2<T> Rect<T>::bottom_left() const {
  return Vector2<T>(left(), bottom());
}

template <typename T>
inline Vector2<T> Rect<T>::bottom_right() const {
  return Vector2<T>(right(), bottom());
}

#pragma mark Canonical form

template <typename T>
inline Rect<T>& Rect<T>::canonicalize() {
  if (width < 0) {
    x += width;
    width = -width;
  }
  if (height < 0) {
    y += height;
    height = -height;
  }
  return *this;
}

template <typename T>
inline Rect<Promote<T>> Rect<T>::canonicalized() const {
  return Rect<Promote<T>>(*this).canonicalize();
}

#pragma mark Translation

template <typename T>
inline Rect<T>& Rect<T>::translate(T offset) {
  origin += offset;
  return *this;
}

template <typename T>
inline Rect<T>& Rect<T>::translate(T dx, T dy) {
  x += dx;
  y += dy;
  return *this;
}

template <typename T>
inline Rect<T>& Rect<T>::translate(const Vector2<T>& offset) {
  origin += offset;
  return *this;
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::translated(U offset) const {
  return Rect<Promote<T, U>>(*this).translate(offset);
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::translated(U dx, U dy) const {
  return Rect<Promote<T, U>>(*this).translate(dx, dy);
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::translated(const Vector2<U>& offset) const {
  return Rect<Promote<T, U>>(*this).translate(offset);
}

#pragma mark Scaling

template <typename T>
inline Rect<T>& Rect<T>::scale(T scale) {
  size *= scale;
  return *this;
}

template <typename T>
inline Rect<T>& Rect<T>::scale(T sx, T sy) {
  width *= sx;
  height *= sy;
  return *this;
}

template <typename T>
inline Rect<T>& Rect<T>::scale(const Vector2<T>& scale) {
  size *= scale;
  return *this;
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::scaled(U scale) const {
  return Rect<Promote<T, U>>(*this).scale(scale);
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::scaled(U sx, U sy) const {
  return Rect<Promote<T, U>>(*this).scale(sx, sy);
}

template <typename T>
template <typename U>
inline Rect<Promote<T, U>> Rect<T>::scaled(const Vector2<U>& scale) const {
  return Rect<Promote<T, U>>(*this).scale(scale);
}
  
#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Rect<T>& other) {
  return os << "( " << other.origin << ", " << other.size << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_RECT_H_
