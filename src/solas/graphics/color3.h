//
//  solas/graphics/color3.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
#ifndef SOLAS_GRAPHICS_COLOR3_H_
#define SOLAS_GRAPHICS_COLOR3_H_

#include <cstdint>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <tuple>
#include <utility>

#include "solas/graphics/color_depth.h"
#include "solas/math/vector.h"

namespace solas {
namespace graphics {

template <typename T, int C>
class Color;

template <typename T>
using Color3 = Color<T, 3>;
template <typename T>
using Color4 = Color<T, 4>;

template <typename T>
class Color<T, 3> final {
 public:
  using Type = T;
  using Iterator = typename math::Vec3<T>::Iterator;
  using ConstIterator = typename math::Vec3<T>::ConstIterator;
  using ReverseIterator = typename math::Vec3<T>::ReverseIterator;
  using ConstReverseIterator = typename math::Vec3<T>::ConstReverseIterator;
  static constexpr const auto channels = math::Vec3<T>::dimensions;

 public:
  // Constructors
  Color();
  explicit Color(T gray);
  Color(T red, T green, T blue);
  explicit Color(const T *values, std::size_t size = channels);
  template <typename... Args>
  Color(const std::tuple<Args...>& tuple);
  Color(std::initializer_list<T> list);

  // Implicit conversion
  template <typename U>
  Color(const Color3<U>& other);

  // Explicit conversion
  template <typename U>
  explicit Color(const Color4<U>& other);
  explicit Color(const math::Vec3<T>& other);
  explicit Color(const math::Vec4<T>& other);

  // Copy and assign
  Color(const Color3<T>& other);
  Color3<T>& operator=(const Color3<T>& other);
  template <typename... Args>
  Color3<T>& operator=(const std::tuple<Args...>& tuple);
  Color3<T>& operator=(std::initializer_list<T> list);

  // Factory
  static Color3<T> White();
  static Color3<T> Black();
  static Color3<T> Hex(std::uint32_t hex);

  // Mutators
  void set(T gray);
  void set(T red, T green, T blue);
  void set(const T *values, std::size_t size = channels);
  template <typename... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
  void reset();

  // Element access
  T& operator[](int index) { return at(index); }
  const T& operator[](int index) const { return at(index); }
  T& at(int index);
  const T& at(int index) const;
  T& front() { return vector.front(); }
  const T& front() const { return vector.front(); }
  T& back() { return vector.back(); }
  const T& back() const { return vector.back(); }

  // Comparison
  template <typename U>
  bool operator==(const Color3<U>& other) const;
  template <typename U>
  bool operator!=(const Color3<U>& other) const;

  // Conversion
  template <typename U>
  explicit operator math::Vec3<U>&() { return vector; }
  template <typename U>
  explicit operator const math::Vec3<U>&() const { return vector; }
  explicit operator std::uint32_t() const;

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
    math::Vec3<T> vector;
    struct { T red; T green; T blue; };
    struct { T r; T g; T b; };
  };
};

using Color3u = Color3<std::uint8_t>;
using Color3s = Color3<std::uint16_t>;
using Color3i = Color3<std::uint32_t>;
using Color3f = Color3<float>;
using Color3d = Color3<double>;

#pragma mark -

template <typename T>
inline Color3<T>::Color()
    : vector() {}

template <typename T>
inline Color3<T>::Color(T gray)
    : vector(gray, gray, gray) {}

template <typename T>
inline Color3<T>::Color(T red, T green, T blue)
    : vector(red, green, blue) {}

template <typename T>
inline Color3<T>::Color(const T *values, std::size_t size)
    : vector(values, size) {}

template <typename T>
template <typename... Args>
inline Color3<T>::Color(const std::tuple<Args...>& tuple)
    : vector(tuple) {}

template <typename T>
inline Color3<T>::Color(std::initializer_list<T> list)
    : vector(list) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Color3<T>::Color(const Color3<U>& other)
    : vector(other.vector) {}

#pragma mark Explicit conversion

template <typename T>
template <typename U>
inline Color3<T>::Color(const Color4<U>& other)
    : vector(other.vector) {}

template <typename T>
inline Color3<T>::Color(const math::Vec3<T>& other)
    : vector(other.vector) {}

template <typename T>
inline Color3<T>::Color(const math::Vec4<T>& other)
    : vector(other) {}

#pragma mark Copy and assign

template <typename T>
inline Color3<T>::Color(const Color3<T>& other)
    : vector(other.vector) {}

template <typename T>
inline Color3<T>& Color3<T>::operator=(const Color3<T>& other) {
  if (&other != this) {
    vector = other.vector;
  }
  return *this;
}

template <typename T>
template <typename... Args>
inline Color3<T>& Color3<T>::operator=(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
  return *this;
}

template <typename T>
inline Color3<T>& Color3<T>::operator=(std::initializer_list<T> list) {
  vector.set(std::move(list));
  return *this;
}

#pragma mark Factory

template <typename T>
inline Color3<T> Color3<T>::White() {
  return Color3<T>(ColorDepth<T>::max);
}

template <typename T>
inline Color3<T> Color3<T>::Black() {
  return Color3<T>(ColorDepth<T>::min);
}

template <typename T>
inline Color3<T> Color3<T>::Hex(std::uint32_t hex) {
  return Color3<T>(
    ColorDepth<T>::Convert(static_cast<std::uint8_t>(0xff & (hex >> 16))),
    ColorDepth<T>::Convert(static_cast<std::uint8_t>(0xff & (hex >> 8))),
    ColorDepth<T>::Convert(static_cast<std::uint8_t>(0xff & (hex >> 0)))
  );
}

#pragma mark Mutators

template <typename T>
inline void Color3<T>::set(T gray) {
  vector.set(gray, gray, gray);
}

template <typename T>
inline void Color3<T>::set(T red, T green, T blue) {
  vector.set(red, green, blue);
}

template <typename T>
inline void Color3<T>::set(const T *values, std::size_t size) {
  vector.set(values, size);
}

template <typename T>
template <typename... Args>
inline void Color3<T>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <typename T>
inline void Color3<T>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <typename T>
inline void Color3<T>::reset() {
  vector.reset();
}

#pragma mark Element access

template <typename T>
inline T& Color3<T>::at(int index) {
  return vector.at(index);
}

template <typename T>
inline const T& Color3<T>::at(int index) const {
  return vector.at(index);
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Color3<T>::operator==(const Color3<U>& other) const {
  return vector == other.vector;
}

template <typename T>
template <typename U>
inline bool Color3<T>::operator!=(const Color3<U>& other) const {
  return vector != other.vector;
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Color3<T>& other) {
  return os << other.vector;
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_COLOR3_H_
