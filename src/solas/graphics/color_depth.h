//
//  solas/graphics/color_depth.h
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
#ifndef SOLAS_GRAPHICS_COLOR_DEPTH_H_
#define SOLAS_GRAPHICS_COLOR_DEPTH_H_

#include <cmath>
#include <limits>

#include "solas/math/functions.h"
#include "solas/utility/enablers.h"

namespace solas {
namespace graphics {

template <typename T, typename Enable = void>
struct ColorDepth {};

template <typename T>
using IntegralColorDepth = ColorDepth<T, EnableIfIntegral<T>>;
template <typename T>
using FloatingColorDepth = ColorDepth<T, EnableIfFloating<T>>;

template <typename T>
struct ColorDepth<T, EnableIfIntegral<T>> {
  static constexpr const int bits = std::numeric_limits<T>::digits;
  static constexpr const T min = std::numeric_limits<T>::min();
  static constexpr const T max = std::numeric_limits<T>::max();

  // Conversions
  static T Clamp(T value);
  template <typename U>
  static EnableIfIntegral<U, T> Convert(U value);
  template <typename U>
  static EnableIfFloating<U, T> Convert(U value);
};

template <typename T>
struct ColorDepth<T, EnableIfFloating<T>> {
  static constexpr const int bits = sizeof(T) * 8;
  static constexpr const T min = 0.0;
  static constexpr const T max = 1.0;

  // Conversions
  static T Clamp(T value);
  template <typename U>
  static EnableIfIntegral<U, T> Convert(U value);
  template <typename U>
  static EnableIfFloating<U, T> Convert(U value);
};

#pragma mark -

#pragma mark Conversions

template <typename T>
inline T IntegralColorDepth<T>::Clamp(T value) {
  return math::Clamp(value, min, max);
}

template <typename T>
inline T FloatingColorDepth<T>::Clamp(T value) {
  return math::Clamp(value, min, max);
}

template <typename T>
template <typename U>
inline EnableIfIntegral<U, T> IntegralColorDepth<T>::Convert(U value) {
  if (ColorDepth<U>::bits < bits) {
    return (static_cast<T>(value) << (bits - ColorDepth<U>::bits)) | value;
  } else if (ColorDepth<U>::bits > bits) {
    return value >> (ColorDepth<U>::bits - bits);
  }
  return value;
}

template <typename T>
template <typename U>
inline EnableIfFloating<U, T> IntegralColorDepth<T>::Convert(U value) {
  return std::round(max * value);
}

template <typename T>
template <typename U>
inline EnableIfIntegral<U, T> FloatingColorDepth<T>::Convert(U value) {
  return static_cast<T>(value) / ColorDepth<U>::max;
}

template <typename T>
template <typename U>
inline EnableIfFloating<U, T> FloatingColorDepth<T>::Convert(U value) {
  return value;
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_COLOR_DEPTH_H_
