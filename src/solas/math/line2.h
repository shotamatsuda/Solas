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
#ifndef SOLAS_MATH_LINE2_H_
#define SOLAS_MATH_LINE2_H_

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
class Line<T, 2> final {
 public:
  using Type = T;
  using Iterator = Vector2<T> *;
  using ConstIterator = const Vector2<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static const constexpr auto dimensions = Vector2<T>::dimensions;

 public:
  // Constructors
  Line();
  Line(T x1, T y1, T x2, T y2);
  Line(const Vector2<T>& a, const Vector2<T>& b);
  Line(std::initializer_list<T> list);
  Line(std::initializer_list<Vector2<T>> list);
  template <typename Container>
  explicit Line(const Container& container);
  template <typename InputIterator>
  Line(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Line(const Line2<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Line(const Line3<U>& other);

  // Copy and assign
  Line(const Line2<T>& other) = default;
  Line2<T>& operator=(const Line2<T>& other) = default;
  Line2<T>& operator=(std::initializer_list<T> list);
  Line2<T>& operator=(std::initializer_list<Vector2<T>> list);

  // Mutators
  void set(T x1, T y1, T x2, T y2);
  void set(const Vector2<T>& a, const Vector2<T>& b);
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vector2<T>> list);
  template <typename Container>
  void set(const Container& container);
  template <typename InputIterator>
  void set(InputIterator begin, InputIterator end);
  void reset();

  // Element access
  Vector2<T>& operator[](int index) { return at(index); }
  const Vector2<T>& operator[](int index) const { return at(index); }
  Vector2<T>& at(int index);
  const Vector2<T>& at(int index) const;
  Vector2<T>& front() { return a; }
  const Vector2<T>& front() const { return a; }
  Vector2<T>& back() { return b; }
  const Vector2<T>& back() const { return b; }

  // Comparison
  template <typename U>
  bool operator==(const Line2<U>& other) const;
  template <typename U>
  bool operator!=(const Line2<U>& other) const;

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
  Vector2<T> * ptr() { return &a; }
  const Vector2<T> * ptr() const { return &a; }

 public:
  union {
    Vector2<T> a;
    struct { T x1; T y1; };
  };
  union {
    Vector2<T> b;
    struct { T x2; T y2; };
  };
};

using Line2i = Line2<int>;
using Line2f = Line2<float>;
using Line2d = Line2<double>;

#pragma mark -

template <typename T>
inline Line2<T>::Line()
    : a(),
      b() {}

template <typename T>
inline Line2<T>::Line(T x1, T y1, T x2, T y2)
    : a(x1, y1),
      b(x2, y2) {}

template <typename T>
inline Line2<T>::Line(const Vector2<T>& a, const Vector2<T>& b)
    : a(a),
      b(b) {}

template <typename T>
inline Line2<T>::Line(std::initializer_list<T> list) {
  set(std::move(list));
}

template <typename T>
inline Line2<T>::Line(std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
}

template <typename T>
template <typename Container>
inline Line2<T>::Line(const Container& container) {
  set(container);
}

template <typename T>
template <typename InputIterator>
inline Line2<T>::Line(InputIterator begin, InputIterator end) {
  set(begin, end);
}

#pragma mark Copy and assign

template <typename T>
inline Line2<T>& Line2<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

template <typename T>
inline Line2<T>& Line2<T>::operator=(std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Mutators

template <typename T>
inline void Line2<T>::set(T x1, T y1, T x2, T y2) {
  a.x = x1; a.y = y1;
  b.x = x2; b.y = y2;
}

template <typename T>
inline void Line2<T>::set(const Vector2<T>& a, const Vector2<T>& b) {
  this->a = a;
  this->b = b;
}

template <typename T>
inline void Line2<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = list.begin();
  if (itr == list.end()) return; a.x = *itr++;
  if (itr == list.end()) return; a.y = *itr++;
  if (itr == list.end()) return; b.x = *itr++;
  if (itr == list.end()) return; b.y = *itr++;
}

template <typename T>
inline void Line2<T>::set(std::initializer_list<Vector2<T>> list) {
  set(list.begin(), list.end());
}

template <typename T>
template <typename Container>
inline void Line2<T>::set(const Container& container) {
  set(container.begin(), container.end());
}

template <typename T>
template <typename InputIterator>
inline void Line2<T>::set(InputIterator begin, InputIterator end) {
  reset();
  auto itr = begin;
  if (itr == end) return; a = decltype(a)(*itr++);
  if (itr == end) return; b = decltype(b)(*itr++);
}

template <typename T>
inline void Line2<T>::reset() {
  *this = Line2<T>();
}

#pragma mark Element access

template <typename T>
inline Vector2<T>& Line2<T>::at(int index) {
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
inline const Vector2<T>& Line2<T>::at(int index) const {
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
inline bool Line2<T>::operator==(const Line2<U>& other) const {
  return a == other.a && b == other.b;
}

template <typename T>
template <typename U>
inline bool Line2<T>::operator!=(const Line2<U>& other) const {
  return !operator==(other);
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Line2<T>& other) {
  return os << "( " << other.a << ", " << other.b << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_LINE2_H_
