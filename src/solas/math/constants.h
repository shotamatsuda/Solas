//
//  solas/math/constants.h
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
#ifndef SOLAS_MATH_CONSTANTS_H_
#define SOLAS_MATH_CONSTANTS_H_

#include <boost/math/constants/constants.hpp>

namespace solas {
namespace math {

template <typename T = double>
constexpr T pi = boost::math::constants::pi<T>();
template constexpr float pi<float>;
template constexpr double pi<double>;
template constexpr long double pi<long double>;

template <typename T = double>
constexpr T half_pi = boost::math::constants::half_pi<T>();
template constexpr float half_pi<float>;
template constexpr double half_pi<double>;
template constexpr long double half_pi<long double>;

template <typename T = double>
constexpr T third_pi = boost::math::constants::third_pi<T>();
template constexpr float third_pi<float>;
template constexpr double third_pi<double>;
template constexpr long double third_pi<long double>;

template <typename T = double>
constexpr T quarter_pi = boost::math::constants::half_pi<T>() / 2;
template constexpr float quarter_pi<float>;
template constexpr double quarter_pi<double>;
template constexpr long double quarter_pi<long double>;

template <typename T = double>
constexpr T two_pi = boost::math::constants::two_pi<T>();
template constexpr float two_pi<float>;
template constexpr double two_pi<double>;
template constexpr long double two_pi<long double>;

template <typename T = double>
constexpr T tau = boost::math::constants::two_pi<T>();
template constexpr float tau<float>;
template constexpr double tau<double>;
template constexpr long double tau<long double>;

template <typename T = double>
constexpr T e = boost::math::constants::e<T>();
template constexpr float e<float>;
template constexpr double e<double>;
template constexpr long double e<long double>;

template <typename T = double>
constexpr T degree = boost::math::constants::degree<T>();
template constexpr float degree<float>;
template constexpr double degree<double>;
template constexpr long double degree<long double>;

template <typename T = double>
constexpr T radian = boost::math::constants::radian<T>();
template constexpr float radian<float>;
template constexpr double radian<double>;
template constexpr long double radian<long double>;

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_CONSTANTS_H_
