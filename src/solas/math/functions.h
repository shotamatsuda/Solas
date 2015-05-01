//
//  solas/math/functions.h
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
#ifndef SOLAS_MATH_FUNCTIONS_H_
#define SOLAS_MATH_FUNCTIONS_H_

namespace solas {
namespace math {

template <typename T, typename U, typename V>
constexpr T Lerp(T start, U stop, V amount);
template <typename T, typename U, typename V>
constexpr T Norm(T amount, U start, V stop);
template <typename T, typename U, typename V>
constexpr T Clamp(T value, U min, V max);
template <typename T, typename U, typename V>
constexpr T Map(T value, U min1, U max1, V min2, V max2);

#pragma mark -

template <typename T, typename U, typename V>
constexpr T Lerp(T start, U stop, V amount) {
  return start + (stop - start) * amount;
}

template <typename T, typename U, typename V>
constexpr T Norm(T amount, U start, V stop) {
  return (amount - start) / (stop - start);
}

template <typename T, typename U, typename V>
constexpr T Clamp(T value, U min, V max) {
  return (value < min ? min : (value > max ? max : value));
}

template <typename T, typename U, typename V>
constexpr T Map(T value, U min1, U max1, V min2, V max2) {
  return min2 + (max2 - min2) * ((value - min1) / (max1 - min1));
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_FUNCTIONS_H_
