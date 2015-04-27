//
//  solas/math/vector4.h
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
#ifndef SOLAS_MATH_VECTOR4_H_
#define SOLAS_MATH_VECTOR4_H_

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
class Vector<T, 4> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 4;

 public:
  // Constructors
  Vector();
  explicit Vector(T value);
  Vector(T x, T y, T z = T(), T w = T());
  explicit Vector(const T *values, std::size_t size = dimensions);
  template <typename... Args>
  Vector(const std::tuple<Args...>& tuple);
  Vector(std::initializer_list<T> list);

  // Implicit conversion
  template <typename U>
  Vector(const Vector4<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Vector(const Vector2<U>& other);
  template <typename U>
  explicit Vector(const Vector3<U>& other);

  // Copy and assign
  Vector(const Vector4<T>& other) = default;
  Vector4<T>& operator=(const Vector4<T>& other) = default;
  template <typename... Args>
  Vector4<T>& operator=(const std::tuple<Args...>& tuple);
  Vector4<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Vector4<T> Min();
  static Vector4<T> Max();
  static Vector4<T> Random();
  static Vector4<T> Random(T max);
  static Vector4<T> Random(T min, T max);

  // Mutators
  void set(T value);
  void set(T x, T y, T z = T(), T w = T());
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
  T& back() { return w; }
  const T& back() const { return w; }

  // Comparison
  template <typename U>
  bool operator==(const Vector4<U>& other) const;
  template <typename U>
  bool operator!=(const Vector4<U>& other) const;
  template <typename U>
  bool operator<(const Vector4<U>& other) const;
  template <typename U>
  bool operator>(const Vector4<U>& other) const;
  template <typename U>
  bool operator<=(const Vector4<U>& other) const;
  template <typename U>
  bool operator>=(const Vector4<U>& other) const;

  // Arithmetic
  Vector4<T>& operator+=(const Vector4<T>& other);
  Vector4<T>& operator-=(const Vector4<T>& other);
  Vector4<T>& operator*=(const Vector4<T>& other);
  Vector4<T>& operator/=(const Vector4<T>& other);
  template <typename U>
  Vector4<Promote<T, U>> operator+(const Vector4<U>& other) const;
  template <typename U>
  Vector4<Promote<T, U>> operator-(const Vector4<U>& other) const;
  template <typename U>
  Vector4<Promote<T, U>> operator*(const Vector4<U>& other) const;
  template <typename U>
  Vector4<Promote<T, U>> operator/(const Vector4<U>& other) const;
  Vector4<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vector4<T>& operator+=(T scalar);
  Vector4<T>& operator-=(T scalar);
  Vector4<T>& operator*=(T scalar);
  Vector4<T>& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector4<Promote<T, U>> operator+(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector4<Promote<T, U>> operator-(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector4<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Vector4<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y && !z && !w; }

  // Angle
  Promote<T> headingXY() const;
  Promote<T> headingYZ() const;
  Promote<T> headingZX() const;
  template <typename U>
  Promote<T> angle(const Vector4<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <typename U>
  Vector4<T>& limit(U limit);
  template <typename U>
  Vector4<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vector4<T>& normalize();
  Vector4<Promote<T>> normalized() const;

  // Inversion
  Vector4<T>& invert();
  Vector4<Promote<T>> inverted() const;

  // Distance
  template <typename U>
  Promote<T> distance(const Vector4<U>& other) const;
  template <typename U>
  Promote<T> distanceSquared(const Vector4<U>& other) const;

  // Product
  template <typename U>
  Promote<T, U> dot(const Vector4<U>& other) const;
  template <typename U>
  Vector4<Promote<T, U>> cross(const Vector4<U>& other) const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return &w + 1; }
  ConstIterator end() const { return &w + 1; }
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
  T w;
};

using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template <typename T>
using Vec4 = Vector4<T>;
using Vec4i = Vector4<int>;
using Vec4f = Vector4<float>;
using Vec4d = Vector4<double>;

#pragma mark -

template <typename T>
inline Vector4<T>::Vector()
    : x(),
      y(),
      z(),
      w() {}

template <typename T>
inline Vector4<T>::Vector(T value)
    : x(value),
      y(value),
      z(value),
      w(value) {}

template <typename T>
inline Vector4<T>::Vector(T x, T y, T z, T w)
    : x(x),
      y(y),
      z(z),
      w(w) {}

template <typename T>
inline Vector4<T>::Vector(const T *values, std::size_t size) {
  set(values, size);
}

template <typename T>
template <typename... Args>
inline Vector4<T>::Vector(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <typename T>
inline Vector4<T>::Vector(std::initializer_list<T> list) {
  set(std::move(list));
}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Vector4<T>::Vector(const Vector4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Vector4<T>::Vector(const Vector2<U>& other)
    : x(other.x),
      y(other.y),
      z(),
      w() {}

template <typename T>
template <typename U>
inline Vector4<T>::Vector(const Vector3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w() {}

#pragma mark Copy and assign

template <typename T>
template <typename... Args>
inline Vector4<T>& Vector4<T>::operator=(const std::tuple<Args...>& tuple) {
  set(tuple);
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Vector4<T> Vector4<T>::Min() {
  return Vector4<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min());
}

template <typename T>
inline Vector4<T> Vector4<T>::Max() {
  return Vector4<T>(std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max());
}

template <typename T>
inline Vector4<T> Vector4<T>::Random() {
  return Random(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
inline Vector4<T> Vector4<T>::Random(T max) {
  return Random(T(), max);
}

template <typename T>
inline Vector4<T> Vector4<T>::Random(T min, T max) {
  auto& random = math::Random<>::Shared();
  return Vector4<T>(random.uniform<T>(min, max),
                    random.uniform<T>(min, max),
                    random.uniform<T>(min, max),
                    random.uniform<T>(min, max));
}

#pragma mark Mutators

template <typename T>
inline void Vector4<T>::set(T value) {
  x = y = z = w = value;
}

template <typename T>
inline void Vector4<T>::set(T x, T y, T z, T w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

template <typename T>
inline void Vector4<T>::set(const T *values, std::size_t size) {
  reset();
  const auto end = values + size;
  if (values == end) return; x = *values++;
  if (values == end) return; y = *values++;
  if (values == end) return; z = *values++;
  if (values == end) return; w = *values;
}

template <typename T>
template <typename... Args>
inline void Vector4<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y, z, w) = tuple;
}

template <typename T>
inline void Vector4<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = list.begin();
  if (itr == list.end()) return; x = *itr++;
  if (itr == list.end()) return; y = *itr++;
  if (itr == list.end()) return; z = *itr++;
  if (itr == list.end()) return; w = *itr;
}

template <typename T>
inline void Vector4<T>::reset() {
  *this = Vector4<T>();
}

#pragma mark Element access

template <typename T>
inline T& Vector4<T>::at(int index) {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline const T& Vector4<T>::at(int index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      assert(false);
      break;
  }
  return x;
}

template <typename T>
inline T& Vector4<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <typename T>
inline const T& Vector4<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Vector4<T>::operator==(const Vector4<U>& other) const {
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <typename T>
template <typename U>
inline bool Vector4<T>::operator!=(const Vector4<U>& other) const {
  return !operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector4<T>::operator<(const Vector4<U>& other) const {
  return x < other.x || (x == other.x &&
        (y < other.y || (y == other.y &&
        (z < other.y || (z == other.y && w < other.w)))));
}

template <typename T>
template <typename U>
inline bool Vector4<T>::operator>(const Vector4<U>& other) const {
  return x > other.x || (x == other.x &&
        (y > other.y || (y == other.y &&
        (z > other.y || (z == other.y && w > other.w)))));
}

template <typename T>
template <typename U>
inline bool Vector4<T>::operator<=(const Vector4<U>& other) const {
  return operator<(other) || operator==(other);
}

template <typename T>
template <typename U>
inline bool Vector4<T>::operator>=(const Vector4<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <typename T>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  w *= other.w;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& other) {
  assert(other.x && other.y && other.z && other.w);
  x /= other.x;
  y /= other.y;
  z /= other.z;
  w /= other.w;
  return *this;
}

template <typename T>
template <typename U>
inline Vector4<Promote<T, U>> Vector4<T>::operator+(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) + other.x,
                    static_cast<V>(y) + other.y,
                    static_cast<V>(z) + other.z,
                    static_cast<V>(w) + other.w);
}

template <typename T>
template <typename U>
inline Vector4<Promote<T, U>> Vector4<T>::operator-(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) - other.x,
                    static_cast<V>(y) - other.y,
                    static_cast<V>(z) - other.z,
                    static_cast<V>(w) - other.w);
}

template <typename T>
template <typename U>
inline Vector4<Promote<T, U>> Vector4<T>::operator*(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) * other.x,
                    static_cast<V>(y) * other.y,
                    static_cast<V>(z) * other.z,
                    static_cast<V>(w) * other.w);
}

template <typename T>
template <typename U>
inline Vector4<Promote<T, U>> Vector4<T>::operator/(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  assert(other.x && other.y && other.z && other.w);
  return Vector4<V>(static_cast<V>(x) / other.x,
                    static_cast<V>(y) / other.y,
                    static_cast<V>(z) / other.z,
                    static_cast<V>(w) / other.w);
}

template <typename T>
inline Vector4<Promote<T>> Vector4<T>::operator-() const {
  using V = Promote<T>;
  return Vector4<V>(-static_cast<V>(x),
                    -static_cast<V>(y),
                    -static_cast<V>(z),
                    -static_cast<V>(w));
}

#pragma mark Scalar arithmetic

template <typename T>
inline Vector4<T>& Vector4<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  w += scalar;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  w -= scalar;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector4<Promote<T, U>> Vector4<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) + scalar,
                    static_cast<V>(y) + scalar,
                    static_cast<V>(z) + scalar,
                    static_cast<V>(w) + scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector4<Promote<T, U>> Vector4<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) - scalar,
                    static_cast<V>(y) - scalar,
                    static_cast<V>(z) - scalar,
                    static_cast<V>(w) - scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector4<Promote<T, U>> Vector4<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) * scalar,
                    static_cast<V>(y) * scalar,
                    static_cast<V>(z) * scalar,
                    static_cast<V>(w) * scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Vector4<Promote<T, U>> Vector4<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vector4<V>(static_cast<V>(x) / scalar,
                    static_cast<V>(y) / scalar,
                    static_cast<V>(z) / scalar,
                    static_cast<V>(w) / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Vector4<Promote<T, U>> operator*(U scalar, const Vector4<T>& vector) {
  return vector * scalar;
}

#pragma mark Attributes

template <typename T>
inline Promote<T> Vector4<T>::headingXY() const {
  return std::atan2(y, x);
}

template <typename T>
inline Promote<T> Vector4<T>::headingYZ() const {
  return std::atan2(z, y);
}

template <typename T>
inline Promote<T> Vector4<T>::headingZX() const {
  return std::atan2(x, z);
}

template <typename T>
template <typename U>
inline Promote<T> Vector4<T>::angle(const Vector4<U>& other) const {
  return std::acos(normalized().dot(other.normalized()));
}

#pragma mark Magnitude

template <typename T>
inline Promote<T> Vector4<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <typename T>
inline Promote<T> Vector4<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y + z * z + w * w;
}

template <typename T>
template <typename U>
inline Vector4<T>& Vector4<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <typename T>
template <typename U>
inline Vector4<Promote<T>> Vector4<T>::limited(U limit) const {
  return Vector4<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <typename T>
inline Vector4<T>& Vector4<T>::normalize() {
  const auto denom = magnitude();
  if (denom) {
    *this /= denom;
  }
  return *this;
}

template <typename T>
inline Vector4<Promote<T>> Vector4<T>::normalized() const {
  return Vector4<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <typename T>
inline Vector4<T>& Vector4<T>::invert() {
  x *= -1;
  y *= -1;
  z *= -1;
  w *= -1;
  return *this;
}

template <typename T>
inline Vector4<Promote<T>> Vector4<T>::inverted() const {
  return Vector4<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <typename T>
template <typename U>
inline Promote<T> Vector4<T>::distance(const Vector4<U>& other) const {
  return (*this - other).magnitude();
}

template <typename T>
template <typename U>
inline Promote<T> Vector4<T>::distanceSquared(const Vector4<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Product

template <typename T>
template <typename U>
inline Promote<T, U> Vector4<T>::dot(const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return static_cast<V>(x) * other.x + y * other.y + z * other.z + w * other.w;
}

template <typename T>
template <typename U>
inline Vector4<Promote<T, U>> Vector4<T>::cross(const Vector4<U>& other) const {
  return Vector3<T>(*this).cross(Vector3<T>(other));
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector4<T>& other) {
  return os << "( " << other.x << ", " << other.y << ", " << other.z
            << ", " << other.w << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_VECTOR4_H_
