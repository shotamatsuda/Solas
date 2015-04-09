//
//  solas/math/functions.h
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
#ifndef SOLAS_MATH_FUNCTIONS_H_
#define SOLAS_MATH_FUNCTIONS_H_

namespace solas {
namespace math {

template <typename T>
constexpr T Lerp(T start, T stop, T amount);
template <typename T>
constexpr T Norm(T amount, T start, T stop);
template <typename T>
constexpr T Clamp(T value, T min, T max);
template <typename T>
constexpr T Map(T value, T min1, T max1, T min2, T max2);

#pragma mark -

template <typename T>
constexpr T Lerp(T start, T stop, T amount) {
  return start + (stop - start) * amount;
}

template <typename T>
constexpr T Norm(T amount, T start, T stop) {
  return (amount - start) / (stop - start);
}

template <typename T>
constexpr T Clamp(T value, T min, T max) {
  return (value < min ? min : (value > max ? max : value));
}

template <typename T>
constexpr T Map(T value, T min1, T max1, T min2, T max2) {
  return min2 + (max2 - min2) * ((value - min1) / (max1 - min1));
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_FUNCTIONS_H_
