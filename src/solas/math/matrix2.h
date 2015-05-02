//
//  solas/math/matrix2.h
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//
//  All information contained herein is, and remains the property of takram
//  design engineering and its suppliers, if any. The intellectual and
//  technical concepts contained herein are proprietary to takram design
//  engineering and its suppliers and may be covered by U.S. and Foreign
//  Patents, patents in process, and are protected by trade secret or copyright
//  law. Dissemination of this information or reproduction of this material is
//  strictly forbidden unless prior written permission is obtained from takram
//  design engineering.
//

#pragma once
#ifndef SOLAS_MATH_MATRIX2_H_
#define SOLAS_MATH_MATRIX2_H_

#include <array>
#include <initializer_list>
#include <iterator>
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
class Matrix;

template <typename T>
using Matrix2 = Matrix<T, 2>;
template <typename T>
using Matrix3 = Matrix<T, 3>;

template <typename T>
class Matrix<T, 2> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 2;

 public:
  // Constructors
  Matrix();
  Matrix(T v00, T v01, T v02,
         T v03, T v04, T v05,
         T v06, T v07, T v08);
  Matrix(const Vector3<T>& vx, const Vector3<T>& vy,
         const Vector3<T>& vz = Vector3<T>(0, 0, 1));

  // Implicit conversion
  template <typename U>
  Matrix(const Matrix2<U>& other);

  // Copy and assign
  Matrix(const Matrix2<T>& other);
  Matrix2<T>& operator=(const Matrix2<T>& other);

  // Iterator
  Iterator begin() { return m.begin(); }
  ConstIterator begin() const { return m.begin(); }
  Iterator end() { return m.end(); }
  ConstIterator end() const { return m.end(); }
  ReverseIterator rbegin() { return m.rbegin(); }
  ConstReverseIterator rbegin() const { return m.rbegin(); }
  ReverseIterator rend() { return m.rend(); }
  ConstReverseIterator rend() const { return m.rend(); }

  // Pointer
  T * ptr() { return m.data(); }
  const T * ptr() const { return m.data(); }

 public:
  union {
    struct {
      Vector4<T> c1;
      Vector4<T> c2;
      Vector4<T> c3;
    };
    struct {
      T m00, m10, m20;
      T m01, m11, m21;
      T m02, m12, m22;
    };
    std::array<T, 9> m;
  };
};

using Matrix2i = Matrix2<int>;
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;

#pragma mark -

template <typename T>
inline Matrix2<T>::Matrix() : c1(), c2(), c3() {}

template <typename T>
inline Matrix2<T>::Matrix(T v00, T v01, T v02,
                          T v03, T v04, T v05,
                          T v06, T v07, T v08)
    : c1(v00, v01, v02),
      c2(v03, v04, v05),
      c3(v06, v07, v08) {}

template <typename T>
inline Matrix2<T>::Matrix(const Vector3<T>& vx,
                          const Vector3<T>& vy,
                          const Vector3<T>& vz)
    : c1(vx.x, vy.x, vz.x),
      c2(vx.y, vy.y, vz.y),
      c3(vx.z, vy.z, vz.z) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Matrix2<T>::Matrix(const Matrix2<U>& other)
    : m(other.m) {}

#pragma mark Copy and assign

template <typename T>
inline Matrix2<T>::Matrix(const Matrix2<T>& other)
    : m(other.m) {}

template <typename T>
inline Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& other) {
  if (&other != this) {
    m = other.m;
  }
  return *this;
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_MATRIX2_H_
