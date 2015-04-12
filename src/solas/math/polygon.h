//
//  solas/math/polygon.h
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
#ifndef SOLAS_MATH_POLYGON_H_
#define SOLAS_MATH_POLYGON_H_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

#include "solas/math/promotion.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T>
class Polygon final {
 public:
  using Type = T;
  using Iterator = typename std::vector<Vector2<T>>::iterator;
  using ConstIterator = typename std::vector<Vector2<T>>::const_iterator;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 public:
  // Constructors
  Polygon() = default;
  Polygon(std::initializer_list<T> list);
  Polygon(std::initializer_list<Vector2<T>> list);
  template <typename Container>
  explicit Polygon(const Container& container);
  template <typename InputIterator>
  Polygon(InputIterator begin, InputIterator end);

  // Implicit conversion
  template <typename U>
  Polygon(const Polygon<U>& other);

  // Copy and assign
  Polygon(const Polygon& other) = default;
  Polygon(Polygon&& other) = default;
  Polygon& operator=(const Polygon& other) = default;
  Polygon& operator=(Polygon&& other) = default;
  Polygon& operator=(std::initializer_list<T> list);
  Polygon& operator=(std::initializer_list<Vector2<T>> list);

  // Mutators
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vector2<T>> list);
  template <typename Container>
  void set(const Container& container);
  template <typename InputIterator>
  void set(InputIterator begin, InputIterator end);
  void reset();

  // Element access
  Vector2<T>& operator[](std::size_t index) { return at(index); }
  const Vector2<T>& operator[](std::size_t index) const { return at(index); }
  Vector2<T>& at(std::size_t index);
  const Vector2<T>& at(std::size_t index) const;
  Vector2<T>& front();
  const Vector2<T>& front() const;
  Vector2<T>& back();
  const Vector2<T>& back() const;

  // Comparison
  template <typename U>
  bool operator==(const Polygon<U>& other) const;
  template <typename U>
  bool operator!=(const Polygon<U>& other) const;

  // Modifiers
  void add(T x, T y);
  void add(const Vector2<T>& vertex);
  void insert(T x, T y, std::size_t index);
  void insert(const Vector2<T>& vertex, std::size_t index);

  // Attributes
  bool empty() const { return vertices_.empty(); }
  Promote<T> apothem() const;
  Promote<T> area() const;
  Promote<T> circumference() const;
  Vector2<Promote<T>> centroid() const;
  Rect<Promote<T>> bounds() const;

  // Iterator
  Iterator begin() { return vertices_.begin(); }
  ConstIterator begin() const { return vertices_.begin(); }
  Iterator end() { return vertices_.end(); }
  ConstIterator end() const { return vertices_.end(); }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ReverseIterator(end()); }

  // Pointer
  Vector2<T> * ptr() { return vertices_.data(); }
  const Vector2<T> * ptr() const { return vertices_.data(); }

 private:
  std::vector<Vector2<T>> vertices_;
};

#pragma mark -

template <typename T>
inline Polygon<T>::Polygon(std::initializer_list<T> list) {
  set(std::move(list));
}

template <typename T>
inline Polygon<T>::Polygon(std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
}

template <typename T>
template <typename Container>
inline Polygon<T>::Polygon(const Container& container) {
  set(container);
}

template <typename T>
template <typename InputIterator>
inline Polygon<T>::Polygon(InputIterator begin, InputIterator end) {
  set(begin, end);
}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Polygon<T>::Polygon(const Polygon<U>& other) {
  std::copy(other.vertices_.begin(), other.vertices_.end(), vertices_.begin());
}

#pragma mark Copy and assign

template <typename T>
inline Polygon<T>& Polygon<T>::operator=(std::initializer_list<T> list) {
  set(std::move(list));
  return *this;
}
  
template <typename T>
inline Polygon<T>& Polygon<T>::operator=(
    std::initializer_list<Vector2<T>> list) {
  set(std::move(list));
  return *this;
}

#pragma mark Mutators

template <typename T>
inline void Polygon<T>::set(std::initializer_list<T> list) {
  // TODO(sgss):
}
  
template <typename T>
inline void Polygon<T>::set(std::initializer_list<Vector2<T>> list) {
  set(list.begin(), list.end());
}

template <typename T>
template <typename Container>
inline void Polygon<T>::set(const Container& container) {
  set(container.begin(), container.end());
}

template <typename T>
template <typename InputIterator>
inline void Polygon<T>::set(InputIterator begin, InputIterator end) {
  reset();
  vertices_.resize(std::distance(begin, end));
  std::copy(begin, end, vertices_.begin());
}

template <typename T>
inline void Polygon<T>::reset() {
  *this = Polygon<T>();
}

#pragma mark Element access

template <typename T>
inline Vector2<T>& Polygon<T>::at(std::size_t index) {
  assert(index < vertices_.size());
  return vertices_.at(index);
}

template <typename T>
inline const Vector2<T>& Polygon<T>::at(std::size_t index) const {
  assert(index < vertices_.size());
  return vertices_.at(index);
}

template <typename T>
inline Vector2<T>& Polygon<T>::front() {
  assert(!vertices_.empty());
  return vertices_.front();
}

template <typename T>
inline const Vector2<T>& Polygon<T>::front() const {
  assert(!vertices_.empty());
  return vertices_.front();
}

template <typename T>
inline Vector2<T>& Polygon<T>::back() {
  assert(!vertices_.empty());
  return vertices_.back();
}

template <typename T>
inline const Vector2<T>& Polygon<T>::back() const {
  assert(!vertices_.empty());
  return vertices_.back();
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Polygon<T>::operator==(const Polygon<U>& other) const {
  return vertices_ == other.vertices_;
}

template <typename T>
template <typename U>
inline bool Polygon<T>::operator!=(const Polygon<U>& other) const {
  return !operator==(other);
}

#pragma mark Modifiers

template <typename T>
inline void Polygon<T>::add(T x, T y) {
  // TODO(sgss):
}

template <typename T>
inline void Polygon<T>::add(const Vector2<T>& vertex) {
  // TODO(sgss):
}

template <typename T>
inline void Polygon<T>::insert(T x, T y, std::size_t index) {
  // TODO(sgss):
}

template <typename T>
inline void Polygon<T>::insert(const Vector2<T>& vertex, std::size_t index) {
  // TODO(sgss):
}

#pragma mark Attributes

template <typename T>
inline Promote<T> Polygon<T>::apothem() const {
  // TODO(sgss):
}

template <typename T>
inline Promote<T> Polygon<T>::area() const {
  // TODO(sgss):
}

template <typename T>
inline Promote<T> Polygon<T>::circumference() const {
  // TODO(sgss):
}

template <typename T>
inline Vector2<Promote<T>> Polygon<T>::centroid() const {
  // TODO(sgss):
}

template <typename T>
inline Rect<Promote<T>> Polygon<T>::bounds() const {
  // TODO(sgss):
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Polygon<T>& other) {
  os << "( ";
  const auto& back = other.back();
  for (const auto& vertex : other) {
    os << vertex;
    if (&vertex == &back) {
      os << " ";
    } else {
      os << ", ";
    }
  }
  return os << ")";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_POLYGON_H_
