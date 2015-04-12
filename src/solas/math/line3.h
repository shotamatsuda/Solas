//
//  solas/math/line.h
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
#ifndef SOLAS_MATH_LINE3_H_
#define SOLAS_MATH_LINE3_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <utility>

#include "solas/math/promotion.h"
#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T, int D>
class Line;

template <typename T>
using Line2 = Line<T, 2>;
template <typename T>
using Line3 = Line<T, 3>;

template <typename T>
class Line<T, 3> final {
 public:
  using Type = T;
  using Iterator = Vector3<T> *;
  using ConstIterator = const Vector3<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static const constexpr auto dimensions = Vector3<T>::dimensions;

 public:
  // Constructors
  Line();
  Line(T x1, T y1, T z1, T x2, T y2, T z2);
  Line(const Vector3<T>& a, const Vector3<T>& b);
  Line(std::initializer_list<T> list);
  Line(std::initializer_list<Vector3<T>> list);
  template <typename Container>
  explicit Line(const Container& container);
  template <typename InputIterator>
  Line(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Line(const Line3<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Line(const Line2<U>& other);

  // Copy and assign
  Line(const Line3<T>& other) = default;
  Line3<T>& operator=(const Line3<T>& other) = default;
  Line3<T>& operator=(std::initializer_list<T> list);
  Line3<T>& operator=(std::initializer_list<Vector3<T>> list);

  // Mutators
  void set(T x1, T y1, T z1, T x2, T y2, T z2);
  void set(const Vector3<T>& a, const Vector3<T>& b);
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vector3<T>> list);
  template <typename Container>
  void set(const Container& container);
  template <typename InputIterator>
  void set(InputIterator begin, InputIterator end);
  void reset();

  // Element access
  Vector3<T>& operator[](int index) { return at(index); }
  const Vector3<T>& operator[](int index) const { return at(index); }
  Vector3<T>& at(int index);
  const Vector3<T>& at(int index) const;
  Vector3<T>& front() { return a; }
  const Vector3<T>& front() const { return a; }
  Vector3<T>& back() { return b; }
  const Vector3<T>& back() const { return b; }

  // Comparison
  template <typename U>
  bool operator==(const Line3<U>& other) const;
  template <typename U>
  bool operator!=(const Line3<U>& other) const;

  // Iterator
  Iterator begin() { return &a; }
  ConstIterator begin() const { return &a; }
  Iterator end() { return ++&b; }
  ConstIterator end() const { return ++&b; }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ReverseIterator(end()); }

  // Pointer
  Vector3<T> * ptr() { return &a; }
  const Vector3<T> * ptr() const { return &a; }

 public:
  union {
    Vector3<T> a;
    struct { T x1; T y1; T z1; };
  };
  union {
    Vector3<T> b;
    struct { T x2; T y2; T z2; };
  };
};

using Line3i = Line3<int>;
using Line3f = Line3<float>;
using Line3d = Line3<double>;

#pragma mark -

template <typename T>
inline Line3<T>::Line()
    : a(),
      b() {}

template <typename T>
inline Line3<T>::Line(T x1, T y1, T z1, T x2, T y2, T z2)
    : a(x1, y1, z1),
      b(x2, y2, z2) {}

template <typename T>
inline Line3<T>::Line(const Vector3<T>& a, const Vector3<T>& b)
    : a(a),
      b(b) {}

template <typename T>
inline Line3<T>::Line(std::initializer_list<T> list) {
  set(std::move(list));
}

template <typename T>
inline Line3<T>::Line(std::initializer_list<Vector3<T>> list) {
  set(std::move(list));
}

template <typename T>
template <typename Container>
inline Line3<T>::Line(const Container& container) {
  set(container);
}

template <typename T>
template <typename InputIterator>
inline Line3<T>::Line(InputIterator begin, InputIterator end) {
  set(begin, end);
}

#pragma mark Copy and assign

template <typename T>
inline Line3<T>& Line3<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

template <typename T>
inline Line3<T>& Line3<T>::operator=(std::initializer_list<Vector3<T>> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Mutators

template <typename T>
inline void Line3<T>::set(T x1, T y1, T z1, T x2, T y2, T z2) {
  a.x = x1; a.y = y1; a.z = z1;
  b.x = x2; b.y = y2; b.z = z2;
}

template <typename T>
inline void Line3<T>::set(const Vector3<T>& a, const Vector3<T>& b) {
  this->a = a;
  this->b = b;
}

template <typename T>
inline void Line3<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = list.begin();
  if (itr == list.end()) return; a.x = *itr++;
  if (itr == list.end()) return; a.y = *itr++;
  if (itr == list.end()) return; a.z = *itr++;
  if (itr == list.end()) return; b.x = *itr++;
  if (itr == list.end()) return; b.y = *itr++;
  if (itr == list.end()) return; b.z = *itr++;
}

template <typename T>
inline void Line3<T>::set(std::initializer_list<Vector3<T>> list) {
  set(list.begin(), list.end());
}

template <typename T>
template <typename Container>
inline void Line3<T>::set(const Container& container) {
  set(container.begin(), container.end());
}

template <typename T>
template <typename InputIterator>
inline void Line3<T>::set(InputIterator begin, InputIterator end) {
  reset();
  auto itr = begin;
  if (itr == end) return; a = decltype(a)(*itr++);
  if (itr == end) return; b = decltype(b)(*itr++);
}

template <typename T>
inline void Line3<T>::reset() {
  *this = Line3<T>();
}

#pragma mark Element access

template <typename T>
inline Vector3<T>& Line3<T>::at(int index) {
  switch (index) {
    case 0:
      return a;
    case 1:
      return b;
    default:
      assert(false);
      break;
  }
  return a;
}

template <typename T>
inline const Vector3<T>& Line3<T>::at(int index) const {
  switch (index) {
    case 0:
      return a;
    case 1:
      return b;
    default:
      assert(false);
      break;
  }
  return a;
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Line3<T>::operator==(const Line3<U>& other) const {
  return a == other.a && b == other.b;
}

template <typename T>
template <typename U>
inline bool Line3<T>::operator!=(const Line3<U>& other) const {
  return !operator==(other);
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Line3<T>& other) {
  return os << "( " << other.a << ", " << other.b << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_LINE3_H_
