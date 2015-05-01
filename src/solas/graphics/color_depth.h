//
//  solas/graphics/color_depth.h
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

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_COLOR_DEPTH_H_
