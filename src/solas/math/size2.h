//
//  solas/math/size2.h
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
#ifndef SOLAS_MATH_SIZE2_H_
#define SOLAS_MATH_SIZE2_H_

#include <cmath>
#include <initializer_list>
#include <ostream>
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
class Size<T, 2> final {
 public:
  using Type = T;
  using Index = typename Vector2<T>::Index;
  using Iterator = typename Vector2<T>::Iterator;
  using ConstIterator = typename Vector2<T>::ConstIterator;
  using ReverseIterator = typename Vector2<T>::ReverseIterator;
  using ConstReverseIterator = typename Vector2<T>::ConstReverseIterator;
  static constexpr auto dimensions = Vector2<T>::dimensions;

 public:
  // Constructors
  Size();
  explicit Size(T value);
  Size(T width, T height);
  Size(std::initializer_list<T> list);
  template <typename Container>
  explicit Size(const Container& container);
  template <typename InputIterator>
  Size(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Size(const Size2<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Size(const Size3<U>& other);
  explicit Size(const Vector2<T>& other);
  explicit Size(const Vector3<T>& other);
  explicit Size(const Vector4<T>& other);

  // Copy and assign
  Size(const Size2<T>& other);
  Size2<T>& operator=(const Size2<T>& other);
  Size2<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Size2<T> Min();
  static Size2<T> Max();
  static Size2<T> Random();
  static Size2<T> Random(T max);
  static Size2<T> Random(T min, T max);

  // Mutators
  void set(T value);
  void set(T width, T height);
  void set(std::initializer_list<T> list);
  template <typename Container>
  void set(const Container& container);
  template <typename InputIterator>
  void set(InputIterator begin, InputIterator end);
  void reset();

  // Element access
  T& operator[](Index index) { return at(index); }
  const T& operator[](Index index) const { return at(index); }
  T& operator[](Axis axis) { return at(axis); }
  const T& operator[](Axis axis) const { return at(axis); }
  T& at(Index index);
  const T& at(Index index) const;
  T& at(Axis axis);
  const T& at(Axis axis) const;
  T& front() { return vector.front(); }
  const T& front() const { return vector.front(); }
  T& back() { return vector.back(); }
  const T& back() const { return vector.back(); }

  // Comparison
  template <typename U>
  bool operator==(const Size2<U>& other) const;
  template <typename U>
  bool operator!=(const Size2<U>& other) const;
  template <typename U>
  bool operator<(const Size2<U>& other) const;
  template <typename U>
  bool operator>(const Size2<U>& other) const;
  template <typename U>
  bool operator<=(const Size2<U>& other) const;
  template <typename U>
  bool operator>=(const Size2<U>& other) const;

  // Arithmetic
  Size2<T>& operator+=(const Size2<T>& other);
  Size2<T>& operator-=(const Size2<T>& other);
  Size2<T>& operator*=(const Size2<T>& other);
  Size2<T>& operator/=(const Size2<T>& other);
  template <typename U>
  Size2<Promote<T, U>> operator+(const Size2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator-(const Size2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator*(const Size2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator/(const Size2<U>& other) const;
  Size2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Size2<T>& operator+=(T scalar);
  Size2<T>& operator-=(T scalar);
  Size2<T>& operator*=(T scalar);
  Size2<T>& operator/=(T scalar);
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator+(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator-(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator*(U scalar) const;
  template <typename U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator/(U scalar) const;

  // Vector arithmetic
  Size2<T>& operator+=(const Vector2<T>& other);
  Size2<T>& operator-=(const Vector2<T>& other);
  Size2<T>& operator*=(const Vector2<T>& other);
  Size2<T>& operator/=(const Vector2<T>& other);
  template <typename U>
  Size2<Promote<T, U>> operator+(const Vector2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator-(const Vector2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator*(const Vector2<U>& other) const;
  template <typename U>
  Size2<Promote<T, U>> operator/(const Vector2<U>& other) const;

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspect() const;
  Promote<T> area() const;
  Promote<T> diagonal() const;

  // Conversion
  template <typename U>
  explicit operator Vector2<U>&() { return vector; }
  template <typename U>
  explicit operator const Vector2<U>&() const { return vector; }

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
    Vector2<T> vector;
    struct { T width; T height; };
    struct { T w; T h; };
  };
};

using Size2i = Size2<int>;
using Size2f = Size2<float>;
using Size2d = Size2<double>;

#pragma mark -

template < typename T>
inline Size2<T>::Size()
    : vector() {}

template <typename T>
inline Size2<T>::Size(T value)
    : vector(value) {}

template <typename T>
inline Size2<T>::Size(T width, T height)
    : vector(width, height) {}

template <typename T>
inline Size2<T>::Size(std::initializer_list<T> list)
    : vector(list) {}

template <typename T>
template <typename Container>
inline Size2<T>::Size(const Container& container)
    : vector(container) {}

template <typename T>
template <typename InputIterator>
inline Size2<T>::Size(InputIterator begin, InputIterator end)
    : vector(begin, end) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Size2<T>::Size(const Size2<U>& other)
    : vector(other.vector) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Size2<T>::Size(const Size3<U>& other)
    : vector(other.vector) {}

template <typename T>
inline Size2<T>::Size(const Vector2<T>& other)
    : vector(other) {}

template <typename T>
inline Size2<T>::Size(const Vector3<T>& other)
    : vector(other) {}

template <typename T>
inline Size2<T>::Size(const Vector4<T>& other)
    : vector(other) {}

#pragma mark Copy and assign

template <typename T>
inline Size2<T>::Size(const Size2<T>& other)
    : vector(other.vector) {}

template <typename T>
inline Size2<T>& Size2<T>::operator=(const Size2<T>& other) {
  if (&other != this) {
    vector = other.vector;
  }
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator=(std::initializer_list<T> list) {
  vector.set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Size2<T> Size2<T>::Min() {
  return static_cast<Size2<T>>(Vector2<T>::Min());
}

template <typename T>
inline Size2<T> Size2<T>::Max() {
  return static_cast<Size2<T>>(Vector2<T>::Max());
}

template <typename T>
inline Size2<T> Size2<T>::Random() {
  return static_cast<Size2<T>>(Vector2<T>::Random());
}

template <typename T>
inline Size2<T> Size2<T>::Random(T max) {
  return static_cast<Size2<T>>(Vector2<T>::Random(max));
}

template <typename T>
inline Size2<T> Size2<T>::Random(T min, T max) {
  return static_cast<Size2<T>>(Vector2<T>::Random(min, max));
}

#pragma mark Mutators

template <typename T>
inline void Size2<T>::set(T value) {
  vector.set(value);
}

template <typename T>
inline void Size2<T>::set(T width, T height) {
  vector.set(width, height);
}

template <typename T>
inline void Size2<T>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <typename T>
template <typename Container>
inline void Size2<T>::set(const Container& container) {
  vector.set(container);
}

template <typename T>
template <typename InputIterator>
inline void Size2<T>::set(InputIterator begin, InputIterator end) {
  vector.set(begin, end);
}

template <typename T>
inline void Size2<T>::reset() {
  vector.reset();
}

#pragma mark Element access

template <typename T>
inline T& Size2<T>::at(Index index) {
  return vector.at(index);
}

template <typename T>
inline const T& Size2<T>::at(Index index) const {
  return vector.at(index);
}

template <typename T>
inline T& Size2<T>::at(Axis axis) {
  return at(static_cast<Index>(axis));
}

template <typename T>
inline const T& Size2<T>::at(Axis axis) const {
  return at(static_cast<Index>(axis));
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Size2<T>::operator==(const Size2<U>& other) const {
  return vector == other.vector;
}

template <typename T>
template <typename U>
inline bool Size2<T>::operator!=(const Size2<U>& other) const {
  return vector != other.vector;
}

template <typename T>
template <typename U>
inline bool Size2<T>::operator<(const Size2<U>& other) const {
  return vector < other.vector;
}

template <typename T>
template <typename U>
inline bool Size2<T>::operator>(const Size2<U>& other) const {
  return vector > other.vector;
}

template <typename T>
template <typename U>
inline bool Size2<T>::operator<=(const Size2<U>& other) const {
  return vector <= other.vector;
}

template <typename T>
template <typename U>
inline bool Size2<T>::operator>=(const Size2<U>& other) const {
  return vector >= other.vector;
}

#pragma mark Arithmetic

template <typename T>
inline Size2<T>& Size2<T>::operator+=(const Size2<T>& other) {
  vector += other.vector;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator-=(const Size2<T>& other) {
  vector -= other.vector;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator*=(const Size2<T>& other) {
  vector *= other.vector;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator/=(const Size2<T>& other) {
  vector /= other.vector;
  return *this;
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator+(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector + other.vector);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator-(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector - other.vector);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator*(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector * other.vector);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator/(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector / other.vector);
}

template <typename T>
inline Size2<Promote<T>> Size2<T>::operator-() const {
  return Size2<Promote<T>>(-vector);
}

#pragma mark Scalar arithmetic

template <typename T>
inline Size2<T>& Size2<T>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <typename T>
inline Size2<T>& Size2<T>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator+(U scalar) const {
  return Size2<Promote<T, U>>(vector + scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator-(U scalar) const {
  return Size2<Promote<T, U>>(vector - scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator*(U scalar) const {
  return Size2<Promote<T, U>>(vector * scalar);
}

template <typename T>
template <typename U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator/(U scalar) const {
  return Size2<Promote<T, U>>(vector / scalar);
}

template <typename T, typename U, EnableIfScalar<U> * = nullptr>
inline Size2<Promote<T, U>> operator*(U scalar, const Size2<T>& size) {
  return size * scalar;
}

#pragma mark Vector arithmetic

template <typename T>
inline Size2<T>& Size2<T>::operator+=(const Vector2<T>& other) {
  vector += other;
}

template <typename T>
inline Size2<T>& Size2<T>::operator-=(const Vector2<T>& other) {
  vector -= other;
}

template <typename T>
inline Size2<T>& Size2<T>::operator*=(const Vector2<T>& other) {
  vector *= other;
}

template <typename T>
inline Size2<T>& Size2<T>::operator/=(const Vector2<T>& other) {
  vector /= other;
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator+(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector + other);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator-(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector - other);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator*(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector * other);
}

template <typename T>
template <typename U>
inline Size2<Promote<T, U>> Size2<T>::operator/(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector / other);
}

template <typename T, typename U>
inline Size2<Promote<T, U>> operator*(
    const Vector2<U>& vector, const Size2<T>& size) {
  return size * vector;
}

#pragma mark Attributes

template <typename T>
inline Promote<T> Size2<T>::aspect() const {
  return static_cast<Promote<T>>(width) / height;
}

template <typename T>
inline Promote<T> Size2<T>::area() const {
  return std::abs(static_cast<Promote<T>>(width) * height);
}

template <typename T>
inline Promote<T> Size2<T>::diagonal() const {
  return vector.length();
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Size2<T>& other) {
  return os << other.vector;
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_SIZE2_H_
