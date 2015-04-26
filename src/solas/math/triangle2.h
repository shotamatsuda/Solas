//
//  solas/math/triangle2.h
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
#ifndef SOLAS_MATH_TRIANGLE2_H_
#define SOLAS_MATH_TRIANGLE2_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <utility>

#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T, int D>
class Triangle;

template <typename T>
using Triangle2 = Triangle<T, 2>;
template <typename T>
using Triangle3 = Triangle<T, 3>;

template <typename T>
class Triangle<T, 2> final {
 public:
  using Type = T;
  using Iterator = Vector2<T> *;
  using ConstIterator = const Vector2<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const auto dimensions = Vector2<T>::dimensions;

 public:
  // Constructors
  Triangle();
  Triangle(T x1, T y1, T x2, T y2, T x3, T y3);
  Triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c);
  Triangle(std::initializer_list<T> list);
  Triangle(std::initializer_list<Vector2<T>> list);

  // Implicit conversion
  template <typename U>
  Triangle(const Triangle2<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Triangle(const Triangle3<U>& other);

  // Copy and assign
  Triangle(const Triangle2<T>& other) = default;
  Triangle2<T>& operator=(const Triangle2<T>& other) = default;
  Triangle2<T>& operator=(std::initializer_list<T> list);
  Triangle2<T>& operator=(std::initializer_list<Vector2<T>> list);

  // Mutators
  void set(T x1, T y1, T x2, T y2, T x3, T y3);
  void set(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c);
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vector2<T>> list);
  void reset();

  // Element access
  Vector2<T>& operator[](int index) { return at(index); }
  const Vector2<T>& operator[](int index) const { return at(index); }
  Vector2<T>& at(int index);
  const Vector2<T>& at(int index) const;
  Vector2<T>& front() { return a; }
  const Vector2<T>& front() const { return a; }
  Vector2<T>& back() { return c; }
  const Vector2<T>& back() const { return c; }

  // Comparison
  template <typename U>
  bool operator==(const Triangle2<U>& other) const;
  template <typename U>
  bool operator!=(const Triangle2<U>& other) const;

  // Iterator
  Iterator begin() { return &a; }
  ConstIterator begin() const { return &a; }
  Iterator end() { return ++&c; }
  ConstIterator end() const { return ++&c; }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

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
  union {
    Vector2<T> c;
    struct { T x3; T y3; };
  };
};

using Triangle2i = Triangle2<int>;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;

#pragma mark -

template <typename T>
inline Triangle2<T>::Triangle()
    : a(),
      b(),
      c() {}

template <typename T>
inline Triangle2<T>::Triangle(T x1, T y1, T x2, T y2, T x3, T y3)
    : a(x1, y1),
      b(x2, y2),
      c(x3, y3) {}

template <typename T>
inline Triangle2<T>::Triangle(const Vector2<T>& a,
                              const Vector2<T>& b,
                              const Vector2<T>& c)
    : a(a),
      b(b),
      c(c) {}

template <typename T>
inline Triangle2<T>::Triangle(std::initializer_list<T> list) {
  set(std::move(list));
}

template <typename T>
inline Triangle2<T>::Triangle(std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
}

#pragma mark Copy and assign

template <typename T>
inline Triangle2<T>& Triangle2<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}

template <typename T>
inline Triangle2<T>& Triangle2<T>::operator=(
    std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Mutators

template <typename T>
inline void Triangle2<T>::set(T x1, T y1, T x2, T y2, T x3, T y3) {
  a.x = x1; a.y = y1;
  b.x = x2; b.y = y2;
  c.x = x3; c.y = y3;
}

template <typename T>
inline void Triangle2<T>::set(const Vector2<T>& a,
                              const Vector2<T>& b,
                              const Vector2<T>& c) {
  this->a = a;
  this->b = b;
  this->c = c;
}

template <typename T>
inline void Triangle2<T>::set(std::initializer_list<T> list) {
  auto itr = list.begin();
  if (itr == list.end()) return; a.x = *itr++;
  if (itr == list.end()) return; a.y = *itr++;
  if (itr == list.end()) return; b.x = *itr++;
  if (itr == list.end()) return; b.y = *itr++;
  if (itr == list.end()) return; c.x = *itr++;
  if (itr == list.end()) return; c.y = *itr;
}

template <typename T>
inline void Triangle2<T>::set(std::initializer_list<Vector2<T>> list) {
  auto itr = list.begin();
  if (itr == list.end()) return; a = decltype(a)(*itr++);
  if (itr == list.end()) return; b = decltype(b)(*itr++);
  if (itr == list.end()) return; c = decltype(c)(*itr++);
}

template <typename T>
inline void Triangle2<T>::reset() {
  *this = Triangle2<T>();
}

#pragma mark Element access

template <typename T>
inline Vector2<T>& Triangle2<T>::at(int index) {
  switch (index) {
    case 0:
      return a;
    case 1:
      return b;
    case 2:
      return c;
    default:
      assert(false);
      break;
  }
  return a;
}

template <typename T>
inline const Vector2<T>& Triangle2<T>::at(int index) const {
  switch (index) {
    case 0:
      return a;
    case 1:
      return b;
    case 2:
      return c;
    default:
      assert(false);
      break;
  }
  return a;
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Triangle2<T>::operator==(const Triangle2<U>& other) const {
  return a == other.a && b == other.b && c == other.c;
}

template <typename T>
template <typename U>
inline bool Triangle2<T>::operator!=(const Triangle2<U>& other) const {
  return !operator==(other);
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Triangle2<T>& other) {
  return os << "( " << other.a << ", " << other.b << ", " << other.c << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_TRIANGLE2_H_
