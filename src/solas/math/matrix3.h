//
//  solas/math/matrix3.h
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
#ifndef SOLAS_MATH_MATRIX3_H_
#define SOLAS_MATH_MATRIX3_H_

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
class Matrix<T, 3> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 3;

 public:
  // Constructors
  Matrix();
  Matrix(T v00, T v01, T v02, T v03,
         T v04, T v05, T v06, T v07,
         T v08, T v09, T v10, T v11,
         T v12, T v13, T v14, T v15);
  Matrix(const Vector4<T>& vx, const Vector4<T>& vy, const Vector4<T>& vz,
         const Vector4<T>& vw = Vector4<T>(0, 0, 0, 1));

  // Implicit conversion
  template <typename U>
  Matrix(const Matrix3<U>& other);

  // Copy and assign
  Matrix(const Matrix3<T>& other);
  Matrix3<T>& operator=(const Matrix3<T>& other);

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
      Vector4<T> c4;
    };
    struct {
      T m00, m10, m20, m30;
      T m01, m11, m21, m31;
      T m02, m12, m22, m32;
      T m03, m13, m23, m33;
    };
    std::array<T, 16> m;
  };
};

using Matrix3i = Matrix3<int>;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;

#pragma mark -

template <typename T>
inline Matrix3<T>::Matrix() : c1(), c2(), c3(), c4() {}

template <typename T>
inline Matrix3<T>::Matrix(T v00, T v01, T v02, T v03,
                          T v04, T v05, T v06, T v07,
                          T v08, T v09, T v10, T v11,
                          T v12, T v13, T v14, T v15)
    : c1(v00, v01, v02, v03),
      c2(v04, v05, v06, v07),
      c3(v08, v09, v10, v11),
      c4(v12, v13, v14, v15) {}

template <typename T>
inline Matrix3<T>::Matrix(const Vector4<T>& vx,
                          const Vector4<T>& vy,
                          const Vector4<T>& vz,
                          const Vector4<T>& vw)
    : c1(vx.x, vy.x, vz.x, vw.x),
      c2(vx.y, vy.y, vz.y, vw.y),
      c3(vx.z, vy.z, vz.z, vw.z),
      c4(vx.w, vy.w, vz.w, vw.w) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Matrix3<T>::Matrix(const Matrix3<U>& other)
    : m(other.m) {}

#pragma mark Copy and assign

template <typename T>
inline Matrix3<T>::Matrix(const Matrix3<T>& other)
    : m(other.m) {}

template <typename T>
inline Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& other) {
  if (&other != this) {
    m = other.m;
  }
  return *this;
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_MATRIX3_H_
