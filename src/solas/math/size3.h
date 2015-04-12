//
//  solas/math/size3.h
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
#ifndef SOLAS_MATH_SIZE3_H_
#define SOLAS_MATH_SIZE3_H_

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <tuple>
#include <utility>

#include "solas/math/axis.h"
#include "solas/math/promotion.h"
#include "solas/math/vector.h"
#include "solas/utility/enablers.h"

namespace solas {
namespace math {

template <typename T, int D>
class Size;

template <typename T>
using Size2 = Size<T, 2>;
template <typename T>
using Size3 = Size<T, 3>;

template <typename T>
class Size<T, 3> final {
 public:
  using Type = T;
  using Iterator = typename Vector3<T>::Iterator;
  using ConstIterator = typename Vector3<T>::ConstIterator;
  using ReverseIterator = typename Vector3<T>::ReverseIterator;
  using ConstReverseIterator = typename Vector3<T>::ConstReverseIterator;
  static const constexpr auto dimensions = Vector3<T>::dimensions;

 public:
  // Constructors
  Size();
  explicit Size(T value);
  Size(T width, T height, T depth = T());
  template <typename... Args>
  Size(const std::tuple<Args...>& tuple);
  Size(std::initializer_list<T> list);
  template <typename Container>
  explicit Size(const Container& container);
  template <typename InputIterator>
  Size(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Size(const Size3<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Size(const Size2<U>& other);
  explicit Size(const Vector2<T>& other);
  explicit Size(const Vector3<T>& other);
  explicit Size(const Vector4<T>& other);

  // Copy and assign
  Size(const Size3<T>& other);
  Size3<T>& operator=(const Size3<T>& other);
  template <typename... Args>
  Size3<T>& operator=(const std::tuple<Args...>& tuple);
  Size3<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Size3<T> Min();
  static Size3<T> Max();
  static Size3<T> Random();
  static Size3<T> Random(T max);
  static Size3<T> Random(T min, T max);

  // Mutators
  void set(T value);
  void set(T width, T height, T depth = T());
  template <typename... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
  template <typename Container>
  void set(const Container& container);
  template <typename InputIterator>
  void set(InputIterator begin, InputIterator end);
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
  T& front() { return vector.front(); }
  const T& front() const { return vector.front(); }
  T& back() { return vector.back(); }
  const T& back() const { return vector.back(); }

  // Comparison
  template <typename U>
  bool operator==(const Size3<U>& other) const;
  template <typename U>
  bool operator!=(const Size3<U>& other) const;
  template <typename U>
  bool operator<(const Size3<U>& other) const;
  template <typename U>
  bool operator>(const Size3<U>& other) const;
  template <typename U>
  bool operator<=(const Size3<U>& other) const;
  template <typename U>
  bool operator>=(const Size3<U>& other) const;

  // Arithmetic
  Size3<T>& operator+=(const Size3<T>& other);
  Size3<T>& operator-=(const Size3<T>& other);
  Size3<T>& operator*=(const Size3<T>& other);
  Size3<T>& operator/=(const Size3<T>& other);
  template <typename U>
  Size3<Promote<T, U>> operator+(const Size3<U>& other) const;
  template <typename U>
  Size3<Promote<T, U>> operator-(const Size3<U>& other) const;
  template <typename U>
  Size3<Promote<T, U>> operator*(const Size3<U>& other) const;
  template <typename U>
  Size3<Promote<T, U>> operator/(const Size3<U>& other) const;
  Size3<Promote<T>> operator-() const;

  // Scalar arithmetic
  Size3<T>& operator+=(T scalar);
  Size3<T>& operator-=(T scalar);
  Size3<T>& operator*=(T scalar);
  Size3<T>& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator+(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator-(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator/(U scalar) const;

  // Vector arithmetic
  Size3<T>& operator+=(const Vector3<T>& vector);
  Size3<T>& operator-=(const Vector3<T>& vector);
  Size3<T>& operator*=(const Vector3<T>& vector);
  Size3<T>& operator/=(const Vector3<T>& vector);
  template <typename U>
  Size3<Promote<T, U>> operator+(const Vector3<U>& vector) const;
  template <typename U>
  Size3<Promote<T, U>> operator-(const Vector3<U>& vector) const;
  template <typename U>
  Size3<Promote<T, U>> operator*(const Vector3<U>& vector) const;
  template <typename U>
  Size3<Promote<T, U>> operator/(const Vector3<U>& vector) const;

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspect_xy() const;
  Promote<T> aspect_yz() const;
  Promote<T> aspect_zx() const;
  Promote<T> volume() const;
  Promote<T> diagonal() const;

  // Conversion
  template <typename U>
  explicit operator Vector3<U>&() { return vector; }
  template <typename U>
  explicit operator const Vector3<U>&() const { return vector; }

  // Iterator
  Iterator begin() { return vector.begin(); }
  ConstIterator begin() const { return vector.begin(); }
  Iterator end() { return vector.end(); }
  ConstIterator end() const { return vector.end(); }
  ReverseIterator rbegin() { return vector.rbegin(); }
  ConstReverseIterator rbegin() const { return vector.rbegin(); }
  ReverseIterator rend() { return vector.rend(); }
  ConstReverseIterator rend() const { return vector.rend(); }

  // Pointer
  T * ptr() { return vector.ptr(); }
  const T * ptr() const { return vector.ptr(); }

 public:
  union {
    Vector3<T> vector;
    struct { T width; T height; T depth; };
    struct { T w; T h; T d; };
  };
};

using Size3i = Size3<int>;
using Size3f = Size3<float>;
using Size3d = Size3<double>;

#pragma mark -

template <typename T>
inline Size3<T>::Size()
    : vector() {}

template <typename T>
inline Size3<T>::Size(T value)
    : vector(value) {}

template <typename T>
inline Size3<T>::Size(T width, T height, T depth)
    : vector(width, height, depth) {}

template <typename T>
template <typename... Args>
inline Size3<T>::Size(const std::tuple<Args...>& tuple)
    : vector(tuple) {}

template <typename T>
inline Size3<T>::Size(std::initializer_list<T> list)
    : vector(list) {}

template <typename T>
template <typename Container>
inline Size3<T>::Size(const Container& container)
    : vector(container) {}

template <typename T>
template <typename InputIterator>
inline Size3<T>::Size(InputIterator begin, InputIterator end)
    : vector(begin, end) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Size3<T>::Size(const Size3<U>& other)
    : vector(other.vector) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Size3<T>::Size(const Size2<U>& other)
    : vector(other.vector) {}

template <typename T>
inline Size3<T>::Size(const Vector2<T>& other)
    : vector(other) {}

template <typename T>
inline Size3<T>::Size(const Vector3<T>& other)
    : vector(other) {}

template <typename T>
inline Size3<T>::Size(const Vector4<T>& other)
    : vector(other) {}

#pragma mark Copy and assign

template <typename T>
inline Size3<T>::Size(const Size3<T>& other)
    : vector(other.vector) {}

template <typename T>
inline Size3<T>& Size3<T>::operator=(const Size3<T>& other) {
  if (&other != this) {
    vector = other.vector;
  }
  return *this;
}

template <typename T>
template <typename... Args>
inline Size3<T>& Size3<T>::operator=(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator=(std::initializer_list<T> list) {
  vector.set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Size3<T> Size3<T>::Min() {
  return static_cast<Size3<T>>(Vector3<T>::Min());
}

template <typename T>
inline Size3<T> Size3<T>::Max() {
  return static_cast<Size3<T>>(Vector3<T>::Max());
}

template <typename T>
inline Size3<T> Size3<T>::Random() {
  return static_cast<Size3<T>>(Vector3<T>::Random());
}

template <typename T>
inline Size3<T> Size3<T>::Random(T max) {
  return static_cast<Size3<T>>(Vector3<T>::Random(max));
}

template <typename T>
inline Size3<T> Size3<T>::Random(T min, T max) {
  return static_cast<Size3<T>>(Vector3<T>::Random(min, max));
}

#pragma mark Mutators

template <typename T>
inline void Size3<T>::set(T value) {
  vector.set(value);
}

template <typename T>
inline void Size3<T>::set(T width, T height, T depth) {
  vector.set(width, height, depth);
}

template <typename T>
template <typename... Args>
inline void Size3<T>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <typename T>
inline void Size3<T>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <typename T>
template <typename Container>
inline void Size3<T>::set(const Container& container) {
  vector.set(container);
}

template <typename T>
template <typename InputIterator>
inline void Size3<T>::set(InputIterator begin, InputIterator end) {
  vector.set(begin, end);
}

template <typename T>
inline void Size3<T>::reset() {
  vector.reset();
}

#pragma mark Element access

template <typename T>
inline T& Size3<T>::at(int index) {
  return vector.at(index);
}

template <typename T>
inline const T& Size3<T>::at(int index) const {
  return vector.at(index);
}

template <typename T>
inline T& Size3<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <typename T>
inline const T& Size3<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Size3<T>::operator==(const Size3<U>& other) const {
  return vector == other.vector;
}

template <typename T>
template <typename U>
inline bool Size3<T>::operator!=(const Size3<U>& other) const {
  return vector != other.vector;
}

template <typename T>
template <typename U>
inline bool Size3<T>::operator<(const Size3<U>& other) const {
  return vector < other.vector;
}

template <typename T>
template <typename U>
inline bool Size3<T>::operator>(const Size3<U>& other) const {
  return vector > other.vector;
}

template <typename T>
template <typename U>
inline bool Size3<T>::operator<=(const Size3<U>& other) const {
  return vector <= other.vector;
}

template <typename T>
template <typename U>
inline bool Size3<T>::operator>=(const Size3<U>& other) const {
  return vector >= other.vector;
}

#pragma mark Arithmetic

template <typename T>
inline Size3<T>& Size3<T>::operator+=(const Size3<T>& other) {
  vector += other.vector;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator-=(const Size3<T>& other) {
  vector -= other.vector;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator*=(const Size3<T>& other) {
  vector *= other.vector;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator/=(const Size3<T>& other) {
  vector /= other.vector;
  return *this;
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator+(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other.vector);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator-(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other.vector);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator*(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other.vector);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator/(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other.vector);
}

template <typename T>
inline Size3<Promote<T>> Size3<T>::operator-() const {
  return Size3<Promote<T>>(-vector);
}

#pragma mark Scalar arithmetic

template <typename T>
inline Size3<T>& Size3<T>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <typename T>
inline Size3<T>& Size3<T>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size3<T>::operator+(U scalar) const {
  return Size3<Promote<T, U>>(vector + scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size3<T>::operator-(U scalar) const {
  return Size3<Promote<T, U>>(vector - scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size3<T>::operator*(U scalar) const {
  return Size3<Promote<T, U>>(vector * scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size3<T>::operator/(U scalar) const {
  return Size3<Promote<T, U>>(vector / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Size3<Promote<T, U>> operator*(U scalar, const Size3<T>& size) {
  return size * scalar;
}

#pragma mark Vector arithmetic

template <typename T>
inline Size3<T>& Size3<T>::operator+=(const Vector3<T>& other) {
  vector += other;
}

template <typename T>
inline Size3<T>& Size3<T>::operator-=(const Vector3<T>& other) {
  vector -= other;
}

template <typename T>
inline Size3<T>& Size3<T>::operator*=(const Vector3<T>& other) {
  vector *= other;
}

template <typename T>
inline Size3<T>& Size3<T>::operator/=(const Vector3<T>& other) {
  vector /= other;
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator+(const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator-(const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator*(const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other);
}

template <typename T>
template <typename U>
inline Size3<Promote<T, U>> Size3<T>::operator/(const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other);
}

template <typename T, typename U>
inline Size3<Promote<T, U>> operator*(
    const Vector3<U>& vector, const Size3<T>& size) {
  return size * vector;
}

#pragma mark Attributes

template <typename T>
inline Promote<T> Size3<T>::aspect_xy() const {
  return static_cast<Promote<T>>(width) / height;
}

template <typename T>
inline Promote<T> Size3<T>::aspect_yz() const {
  return static_cast<Promote<T>>(height) / depth;
}

template <typename T>
inline Promote<T> Size3<T>::aspect_zx() const {
  return static_cast<Promote<T>>(depth) / width;
}

template <typename T>
inline Promote<T> Size3<T>::volume() const {
  return std::abs(static_cast<Promote<T>>(width) * height * depth);
}

template <typename T>
inline Promote<T> Size3<T>::diagonal() const {
  return vector.length();
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Size3<T>& other) {
  return os << other.vector;
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_SIZE3_H_
