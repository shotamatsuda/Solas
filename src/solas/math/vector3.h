//
//  solas/math/vector3.h
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
#ifndef SOLAS_MATH_VECTOR3_H_
#define SOLAS_MATH_VECTOR3_H_

#include <cassert>
#include <cmath>
#include <cstddef>
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
class Vector<T, 3> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 3;

 public:
  // Constructors
  Vector();
  explicit Vector(T value);
  Vector(T x, T y, T z = T());
  explicit Vector(const T *values, std::size_t size = dimensions);
  template <typename... Args>
  Vector(const std::tuple<Args...>& tuple);
  Vector(std::initializer_list<T> list);

  // Implicit conversion
  template <typename U>
  Vector(const Vector3<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Vector(const Vector2<U>& other);
  template <typename U>
  explicit Vector(const Vector4<U>& other);

  // Copy and assign
  Vector(const Vector3<T>& other) = default;
  Vector3<T>& operator=(const Vector3<T>& other) = default;
  template <typename... Args>
  Vector3<T>& operator=(const std::tuple<Args...>& tuple);
  Vector3<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Vector3<T> Min();
  static Vector3<T> Max();
  static Vector3<T> Random();
  static Vector3<T> Random(T max);
  static Vector3<T> Random(T min, T max);

  // Mutators
  void set(T value);
  void set(T x, T y, T z = T());
  void set(const T *values, std::size_t size = dimensions);
  template <typename... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
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
  T& back() { return z; }
  const T& back() const { return z; }

  // Comparison
  template <typename U>
  bool operator==(const Vector3<U>& other) const;
  template <typename U>
  bool operator!=(const Vector3<U>& other) const;
  template <typename U>
  bool operator<(const Vector3<U>& other) const;
  template <typename U>
  bool operator>(const Vector3<U>& other) const;
  template <typename U>
  bool operator<=(const Vector3<U>& other) const;
  template <typename U>
  bool operator>=(const Vector3<U>& other) const;

  // Arithmetic
  Vector3<T>& operator+=(const Vector3<T>& other);
  Vector3<T>& operator-=(const Vector3<T>& other);
  Vector3<T>& operator*=(const Vector3<T>& other);
  Vector3<T>& operator/=(const Vector3<T>& other);
  template <typename U>
  Vector3<Promote<T, U>> operator+(const Vector3<U>& other) const;
  template <typename U>
  Vector3<Promote<T, U>> operator-(const Vector3<U>& other) const;
  template <typename U>
  Vector3<Promote<T, U>> operator*(const Vector3<U>& other) const;
  template <typename U>
  Vector3<Promote<T, U>> operator/(const Vector3<U>& other) const;
  Vector3<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vector3<T>& operator+=(T scalar);
  Vector3<T>& operator-=(T scalar);
  Vector3<T>& operator*=(T scalar);
  Vector3<T>& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector3<Promote<T, U>> operator+(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector3<Promote<T, U>> operator-(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector3<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector3<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y && !z; }

  // Angle
  Promote<T> heading_xy() const;
  Promote<T> heading_yz() const;
  Promote<T> heading_zx() const;
  template <typename U>
  Promote<T> angle(const Vector3<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <typename U>
  Vector3<T>& limit(U limit);
  template <typename U>
  Vector3<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vector3<T>& normalize();
  Vector3<Promote<T>> normalized() const;

  // Inversion
  Vector3<T>& invert();
  Vector3<Promote<T>> inverted() const;

  // Distance
  template <typename U>
  Promote<T> distance(const Vector3<U>& other) const;
  template <typename U>
  Promote<T> distanceSquared(const Vector3<U>& other) const;

  // Product
  template <typename U>
  Promote<T, U> dot(const Vector3<U>& other) const;
  template <typename U>
  Vector3<Promote<T, U>> cross(const Vector3<U>& other) const;

  // Coordinate system conversion
  Vector3<Promote<T>> cartesian() const;
  Vector3<Promote<T>> spherical() const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return ++&z; }
  ConstIterator end() const { return ++&z; }
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
  T z;
};

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

template <typename T>
using Vec3 = Vector3<T>;
using Vec3i = Vector3<int>;
using Vec3f = Vector3<float>;
using Vec3d = Vector3<double>;

#pragma mark -

template <typename T>
inline Vector3<T>::Vector()
    : x(),
      y(),
      z() {}

template <typename T>
inline Vector3<T>::Vector(T value)
    : x(value),
      y(value),
      z(value) {}

template <typename T>
inline Vector3<T>::Vector(T x, T y, T z)
    : x(x),
      y(y),
      z(z) {}

template <typename T>
inline Vector3<T>::Vector(const T *values, std::size_t size) {
  set(values, size);
}

template <typename T>
template <typename... Args>
inline Vector3<T>::Vector(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <typename T>
inline Vector3<T>::Vector(std::initializer_list<T> list) {
  set(std::move(list));
}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Vector3<T>::Vector(const Vector3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Vector3<T>::Vector(const Vector2<U>& other)
    : x(other.x),
      y(other.y),
      z() {}

template <typename T>
template <typename U>
inline Vector3<T>::Vector(const Vector4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

#pragma mark Copy and assign

template <typename T>
template <typename... Args>
inline Vector3<T>& Vector3<T>::operator=(const std::tuple<Args...>& tuple) {
  set(tuple);
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Vector3<T> Vector3<T>::Min() {
  return Vector3<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min());
}

template <typename T>
inline Vector3<T> Vector3<T>::Max() {
  return Vector3<T>(std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max());
}

template <typename T>
inline Vector3<T> Vector3<T>::Random() {
  return Random(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
inline Vector3<T> Vector3<T>::Random(T max) {
  return Random(T(), max);
}

template <typename T>
inline Vector3<T> Vector3<T>::Random(T min, T max) {
  auto& random = math::Random<>::Shared();
  return Vector3<T>(random.uniform<T>(min, max),
                    random.uniform<T>(min, max),
                    random.uniform<T>(min, max));
}

#pragma mark Mutators

template <typename T>
inline void Vector3<T>::set(T value) {
  x = y = z = value;
}

template <typename T>
inline void Vector3<T>::set(T x, T y, T z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

template <typename T>
inline void Vector3<T>::set(const T *values, std::size_t size) {
  reset();
  const auto end = values + size;
  if (values == end) return; x = *values++;
  if (values == end) return; y = *values++;
  if (values == end) return; z = *values;
}

template <typename T>
template <typename... Args>
inline void Vector3<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y, z) = tuple;
}

template <typename T>
inline void Vector3<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = list.begin();
  if (itr == list.end()) return; x = *itr++;
  if (itr == list.end()) return; y = *itr++;
  if (itr == list.end()) return; z = *itr;
}

template <typename T>
inline void Vector3<T>::reset() {
  *this = Vector3<T>();
}

#pragma mark Element access

template <typename T>
inline T& Vector3<T>::at(int index) {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline const T& Vector3<T>::at(int index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline T& Vector3<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <typename T>
inline const T& Vector3<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Vector3<T>::operator==(const Vector3<U>& other) const {
  return x == other.x && y == other.y && z == other.z;
}

template <typename T>
template <typename U>
inline bool Vector3<T>::operator!=(const Vector3<U>& other) const {
  return !operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector3<T>::operator<(const Vector3<U>& other) const {
  return x < other.x || (x == other.x &&
        (y < other.y || (y == other.y && z < other.z)));
}

template <typename T>
template <typename U>
inline bool Vector3<T>::operator>(const Vector3<U>& other) const {
  return x > other.x || (x == other.x &&
        (y > other.y || (y == other.y && z > other.z)));
}

template <typename T>
template <typename U>
inline bool Vector3<T>::operator<=(const Vector3<U>& other) const {
  return operator<(other) || operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector3<T>::operator>=(const Vector3<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& other) {
  assert(other.x && other.y && other.z);
  x /= other.x;
  y /= other.y;
  z /= other.z;
  return *this;
}

template <typename T>
template <typename U>
inline Vector3<Promote<T, U>> Vector3<T>::operator+(
    const Vector3<U>& other) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) + other.x,
                    static_cast<V>(y) + other.y,
                    static_cast<V>(z) + other.z);
}

template <typename T>
template <typename U>
inline Vector3<Promote<T, U>> Vector3<T>::operator-(
    const Vector3<U>& other) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) - other.x,
                    static_cast<V>(y) - other.y,
                    static_cast<V>(z) - other.z);
}

template <typename T>
template <typename U>
inline Vector3<Promote<T, U>> Vector3<T>::operator*(
    const Vector3<U>& other) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) * other.x,
                    static_cast<V>(y) * other.y,
                    static_cast<V>(z) * other.z);
}

template <typename T>
template <typename U>
inline Vector3<Promote<T, U>> Vector3<T>::operator/(
    const Vector3<U>& other) const {
  using V = Promote<T, U>;
  assert(other.x && other.y && other.z);
  return Vector3<V>(static_cast<V>(x) / other.x,
                    static_cast<V>(y) / other.y,
                    static_cast<V>(z) / other.z);
}

template <typename T>
inline Vector3<Promote<T>> Vector3<T>::operator-() const {
  using V = Promote<T>;
  return Vector3<V>(-static_cast<V>(x),
                    -static_cast<V>(y),
                    -static_cast<V>(z));
}

#pragma mark Scalar arithmetic

template <typename T>
inline Vector3<T>& Vector3<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector3<Promote<T, U>> Vector3<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) + scalar,
                    static_cast<V>(y) + scalar,
                    static_cast<V>(z) + scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector3<Promote<T, U>> Vector3<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) - scalar,
                    static_cast<V>(y) - scalar,
                    static_cast<V>(z) - scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector3<Promote<T, U>> Vector3<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(x) * scalar,
                    static_cast<V>(y) * scalar,
                    static_cast<V>(z) * scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector3<Promote<T, U>> Vector3<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vector3<V>(static_cast<V>(x) / scalar,
                    static_cast<V>(y) / scalar,
                    static_cast<V>(z) / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Vector3<Promote<T, U>> operator*(U scalar, const Vector3<T>& vector) {
  return vector * scalar;
}

#pragma mark Angle

template <typename T>
inline Promote<T> Vector3<T>::heading_xy() const {
  return std::atan2(y, x);
}

template <typename T>
inline Promote<T> Vector3<T>::heading_yz() const {
  return std::atan2(z, y);
}

template <typename T>
inline Promote<T> Vector3<T>::heading_zx() const {
  return std::atan2(x, z);
}

template <typename T>
template <typename U>
inline Promote<T> Vector3<T>::angle(const Vector3<U>& other) const {
  return std::acos(normalized().dot(other.normalized()));
}

#pragma mark Magnitude

template <typename T>
inline Promote<T> Vector3<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <typename T>
inline Promote<T> Vector3<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y + z * z;
}

template <typename T>
template <typename U>
inline Vector3<T>& Vector3<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <typename T>
template <typename U>
inline Vector3<Promote<T>> Vector3<T>::limited(U limit) const {
  return Vector3<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <typename T>
inline Vector3<T>& Vector3<T>::normalize() {
  const auto denom = magnitude();
  if (denom) {
    *this /= denom;
  }
  return *this;
}

template <typename T>
inline Vector3<Promote<T>> Vector3<T>::normalized() const {
  return Vector3<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <typename T>
inline Vector3<T>& Vector3<T>::invert() {
  x *= -1;
  y *= -1;
  z *= -1;
  return *this;
}

template <typename T>
inline Vector3<Promote<T>> Vector3<T>::inverted() const {
  return Vector3<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <typename T>
template <typename U>
inline Promote<T> Vector3<T>::distance(const Vector3<U>& other) const {
  return (*this - other).magnitude();
}

template <typename T>
template <typename U>
inline Promote<T> Vector3<T>::distanceSquared(const Vector3<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Product

template <typename T>
template <typename U>
inline Promote<T, U> Vector3<T>::dot(const Vector3<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y + z * other.z;
}

template <typename T>
template <typename U>
inline Vector3<Promote<T, U>> Vector3<T>::cross(const Vector3<U>& other) const {
  using V = Promote<T, U>;
  return Vector3<V>(static_cast<V>(y) * other.z - z * other.y,
                    static_cast<V>(z) * other.x - x * other.z,
                    static_cast<V>(x) * other.y - y * other.x);
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& other) {
  return os << "( " << other.x << ", " << other.y << ", " << other.z << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_VECTOR3_H_
