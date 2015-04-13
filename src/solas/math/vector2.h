//
//  solas/math/vector2.h
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
#ifndef SOLAS_MATH_VECTOR2_H_
#define SOLAS_MATH_VECTOR2_H_

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <ostream>
#include <tuple>
#include <utility>

#include "solas/math/axis.h"
#include "solas/math/promotion.h"
#include "solas/math/random.h"
#include "solas/utility/enablers.h"

namespace solas {
namespace math {

template <typename T, int D>
class Vector;
template <typename T, int D>
using Vec = Vector<T, D>;

template <typename T>
using Vector2 = Vector<T, 2>;
template <typename T>
using Vector3 = Vector<T, 3>;
template <typename T>
using Vector4 = Vector<T, 4>;

template <typename T>
class Vector<T, 2> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static const constexpr int dimensions = 2;

 public:
  // Constructors
  Vector();
  explicit Vector(T value);
  Vector(T x, T y);
  template <typename... Args>
  Vector(const std::tuple<Args...>& tuple);
  Vector(std::initializer_list<T> list);
  template <typename Container>
  explicit Vector(const Container& container);
  template <typename InputIterator>
  Vector(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Vector(const Vector2<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Vector(const Vector3<U>& other);
  template <typename U>
  explicit Vector(const Vector4<U>& other);

  // Copy and assign
  Vector(const Vector2<T>& other) = default;
  Vector2<T>& operator=(const Vector2<T>& other) = default;
  template <typename... Args>
  Vector2<T>& operator=(const std::tuple<Args...>& tuple);
  Vector2<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Vector2<T> Min();
  static Vector2<T> Max();
  static Vector2<T> Random();
  static Vector2<T> Random(T max);
  static Vector2<T> Random(T min, T max);

  // Mutators
  void set(T value);
  void set(T x, T y);
  template <typename... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
  template <typename Container>
  void set(const Container& container);
//  template <typename InputIterator>
//  void set(InputIterator begin, InputIterator end);
  void reset();

  // Element access
  T& operator[](int index) { return at(index); }
  const T& operator[](int index) const { return at(index); }
  T& operator[](Axis axis) { return at(axis); }
  const T& operator[](Axis axis) const { return at(axis); }
  T& at(int index);
  const T& at(int index) const;
  T& at(Axis axis);
  const T& at(Axis axis) const;
  T& front() { return x; }
  const T& front() const { return x; }
  T& back() { return y; }
  const T& back() const { return y; }

  // Comparison
  template <typename U>
  bool operator==(const Vector2<U>& other) const;
  template <typename U>
  bool operator!=(const Vector2<U>& other) const;
  template <typename U>
  bool operator<(const Vector2<U>& other) const;
  template <typename U>
  bool operator>(const Vector2<U>& other) const;
  template <typename U>
  bool operator<=(const Vector2<U>& other) const;
  template <typename U>
  bool operator>=(const Vector2<U>& other) const;

  // Arithmetic
  Vector2<T>& operator+=(const Vector2<T>& other);
  Vector2<T>& operator-=(const Vector2<T>& other);
  Vector2<T>& operator*=(const Vector2<T>& other);
  Vector2<T>& operator/=(const Vector2<T>& other);
  template <typename U>
  Vector2<Promote<T, U>> operator+(const Vector2<U>& other) const;
  template <typename U>
  Vector2<Promote<T, U>> operator-(const Vector2<U>& other) const;
  template <typename U>
  Vector2<Promote<T, U>> operator*(const Vector2<U>& other) const;
  template <typename U>
  Vector2<Promote<T, U>> operator/(const Vector2<U>& other) const;
  Vector2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vector2<T>& operator+=(T scalar);
  Vector2<T>& operator-=(T scalar);
  Vector2<T>& operator*=(T scalar);
  Vector2<T>& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector2<Promote<T, U>> operator+(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector2<Promote<T, U>> operator-(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector2<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector2<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y; }

  // Angle
  Promote<T> heading() const;
  template <typename U>
  Promote<T> angle(const Vector2<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <typename U>
  Vector2<T>& limit(U limit);
  template <typename U>
  Vector2<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vector2<T>& normalize();
  Vector2<Promote<T>> normalized() const;

  // Inversion
  Vector2<T>& invert();
  Vector2<Promote<T>> inverted() const;

  // Distance
  template <typename U>
  Promote<T> distance(const Vector2<U>& other) const;
  template <typename U>
  Promote<T> distanceSquared(const Vector2<U>& other) const;

  // Products
  template <typename U>
  Promote<T, U> dot(const Vector2<U>& other) const;
  template <typename U>
  Promote<T, U> cross(const Vector2<U>& other) const;

  // Coordinate system conversion
  Vector2<Promote<T>> cartesian() const;
  Vector2<Promote<T>> polar() const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return ++&y; }
  ConstIterator end() const { return ++&y; }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

  // Pointer
  T * ptr() { return &x; }
  const T * ptr() const { return &x; }

 public:
  T x;
  T y;
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

template <typename T>
using Vec2 = Vector2<T>;
using Vec2i = Vector2<int>;
using Vec2f = Vector2<float>;
using Vec2d = Vector2<double>;

#pragma mark -

template <typename T>
inline Vector2<T>::Vector()
    : x(),
      y() {}

template <typename T>
inline Vector2<T>::Vector(T value)
    : x(value),
      y(value) {}

template <typename T>
inline Vector2<T>::Vector(T x, T y)
    : x(x),
      y(y) {}

template <typename T>
template <typename... Args>
inline Vector2<T>::Vector(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <typename T>
inline Vector2<T>::Vector(std::initializer_list<T> list) {
  set(std::move(list));
}

template <typename T>
template <typename Container>
inline Vector2<T>::Vector(const Container& container) {
  set(container);
}

template <typename T>
template <typename InputIterator>
inline Vector2<T>::Vector(InputIterator begin, InputIterator end) {
  set(begin, end);
}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Vector2<T>::Vector(const Vector2<U>& other)
    : x(other.x),
      y(other.y) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Vector2<T>::Vector(const Vector3<U>& other)
    : x(other.x),
      y(other.y) {}

template <typename T>
template <typename U>
inline Vector2<T>::Vector(const Vector4<U>& other)
    : x(other.x),
      y(other.y) {}

#pragma mark Copy and assign

template <typename T>
template <typename... Args>
inline Vector2<T>& Vector2<T>::operator=(const std::tuple<Args...>& tuple) {
  set(tuple);
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Vector2<T> Vector2<T>::Min() {
  return Vector2<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min());
}

template <typename T>
inline Vector2<T> Vector2<T>::Max() {
  return Vector2<T>(std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max());
}

template <typename T>
inline Vector2<T> Vector2<T>::Random() {
  return Random(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
inline Vector2<T> Vector2<T>::Random(T max) {
  return Random(T(), max);
}

template <typename T>
inline Vector2<T> Vector2<T>::Random(T min, T max) {
  auto& random = math::Random<>::Shared();
  return Vector2<T>(random.uniform<T>(min, max),
                    random.uniform<T>(min, max));
}

#pragma mark Mutators

template <typename T>
inline void Vector2<T>::set(T value) {
  x = y = value;
}

template <typename T>
inline void Vector2<T>::set(T x, T y) {
  this->x = x;
  this->y = y;
}

template <typename T>
template <typename... Args>
inline void Vector2<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y) = tuple;
}

template <typename T>
inline void Vector2<T>::set(std::initializer_list<T> list) {
//  set(list.begin(), list.end());
  reset();
  const auto begin = list.begin();
  const auto end = list.end();
  auto itr = begin;
  if (itr == end) return; x = *itr++;
  if (itr == end) return; y = *itr++;
}

template <typename T>
template <typename Container>
inline void Vector2<T>::set(const Container& container) {
  set(container.begin(), container.end());
}

//template <typename T>
//template <typename InputIterator>
//inline void Vector2<T>::set(InputIterator begin, InputIterator end) {
//  reset();
//  auto itr = begin;
//  if (itr == end) return; x = *itr++;
//  if (itr == end) return; y = *itr++;
//}

template <typename T>
inline void Vector2<T>::reset() {
  *this = Vector2<T>();
}

#pragma mark Element access

template <typename T>
inline T& Vector2<T>::at(int index) {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline const T& Vector2<T>::at(int index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline T& Vector2<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <typename T>
inline const T& Vector2<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Vector2<T>::operator==(const Vector2<U>& other) const {
  return x == other.x && y == other.y;
}

template <typename T>
template <typename U>
inline bool Vector2<T>::operator!=(const Vector2<U>& other) const {
  return !operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector2<T>::operator<(const Vector2<U>& other) const {
  return x < other.x || (x == other.x && y < other.y);
}

template <typename T>
template <typename U>
inline bool Vector2<T>::operator>(const Vector2<U>& other) const {
  return x > other.x || (x == other.x && y > other.y);
}

template <typename T>
template <typename U>
inline bool Vector2<T>::operator<=(const Vector2<U>& other) const {
  return operator<(other) || operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector2<T>::operator>=(const Vector2<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& other) {
  assert(other.x && other.y);
  x /= other.x;
  y /= other.y;
  return *this;
}

template <typename T>
template <typename U>
inline Vector2<Promote<T, U>> Vector2<T>::operator+(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) + other.x,
                    static_cast<V>(y) + other.y);
}

template <typename T>
template <typename U>
inline Vector2<Promote<T, U>> Vector2<T>::operator-(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) - other.x,
                    static_cast<V>(y) - other.y);
}

template <typename T>
template <typename U>
inline Vector2<Promote<T, U>> Vector2<T>::operator*(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) * other.x,
                    static_cast<V>(y) * other.y);
}

template <typename T>
template <typename U>
inline Vector2<Promote<T, U>> Vector2<T>::operator/(
    const Vector2<U>& other) const {
  assert(other.x && other.y);
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) / other.x,
                    static_cast<V>(y) / other.y);
}

template <typename T>
inline Vector2<Promote<T>> Vector2<T>::operator-() const {
  using V = Promote<T>;
  return Vector2<V>(-static_cast<V>(x),
                    -static_cast<V>(y));
}

#pragma mark Scalar arithmetic

template <typename T>
inline Vector2<T>& Vector2<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  return *this;
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector2<Promote<T, U>> Vector2<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) + scalar,
                    static_cast<V>(y) + scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector2<Promote<T, U>> Vector2<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) - scalar,
                    static_cast<V>(y) - scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector2<Promote<T, U>> Vector2<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) * scalar,
                    static_cast<V>(y) * scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector2<Promote<T, U>> Vector2<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vector2<V>(static_cast<V>(x) / scalar,
                    static_cast<V>(y) / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Vector2<Promote<T, U>> operator*(U scalar, const Vector2<T>& vector) {
  return vector * scalar;
}

#pragma mark Angle

template <typename T>
inline Promote<T> Vector2<T>::heading() const {
  return std::atan2(y, x);
}

template <typename T>
template <typename U>
inline Promote<T> Vector2<T>::angle(const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return std::atan2(static_cast<V>(x) * other.y - y * other.x,
                    static_cast<V>(x) * other.x + y * other.y);
}

#pragma mark Magnitude

template <typename T>
inline Promote<T> Vector2<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <typename T>
inline Promote<T> Vector2<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y;
}

template <typename T>
template <typename U>
inline Vector2<T>& Vector2<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <typename T>
template <typename U>
inline Vector2<Promote<T>> Vector2<T>::limited(U limit) const {
  return Vector2<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <typename T>
inline Vector2<T>& Vector2<T>::normalize() {
  const auto denom = magnitude();
  if (denom) {
    *this /= denom;
  }
  return *this;
}

template <typename T>
inline Vector2<Promote<T>> Vector2<T>::normalized() const {
  return Vector2<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <typename T>
inline Vector2<T>& Vector2<T>::invert() {
  x *= -1;
  y *= -1;
  return *this;
}

template <typename T>
inline Vector2<Promote<T>> Vector2<T>::inverted() const {
  return Vector2<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <typename T>
template <typename U>
inline Promote<T> Vector2<T>::distance(const Vector2<U>& other) const {
  return (*this - other).magnitude();
}

template <typename T>
template <typename U>
inline Promote<T> Vector2<T>::distanceSquared(const Vector2<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <typename T>
template <typename U>
inline Promote<T, U> Vector2<T>::dot(const Vector2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y;
}

template <typename T>
template <typename U>
inline Promote<T, U> Vector2<T>::cross(const Vector2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.y - y * other.x;
}

#pragma mark Coordinate system conversion

template <typename T>
inline Vector2<Promote<T>> Vector2<T>::cartesian() const {
  using V = Promote<T>;
  return Vector2<V>(static_cast<V>(x) * std::cos(y),
                    static_cast<V>(x) * std::sin(y));
}
  
template <typename T>
inline Vector2<Promote<T>> Vector2<T>::polar() const {
  return Vector2<Promote<T>>(magnitude(), heading());
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& other) {
  return os << "( " << other.x << ", " << other.y << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_VECTOR2_H_
