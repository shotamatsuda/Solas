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
constexpr T PI = boost::math::constants::pi<T>();
template constexpr float PI<float>;
template constexpr double PI<double>;
template constexpr long double PI<long double>;

template <typename T = double>
constexpr T HALF_PI = boost::math::constants::half_pi<T>();
template constexpr float HALF_PI<float>;
template constexpr double HALF_PI<double>;
template constexpr long double HALF_PI<long double>;

template <typename T = double>
constexpr T TWO_PI = boost::math::constants::two_pi<T>();
template constexpr float TWO_PI<float>;
template constexpr double TWO_PI<double>;
template constexpr long double TWO_PI<long double>;

template <typename T = double>
constexpr T TAU = boost::math::constants::two_pi<T>();
template constexpr float TAU<float>;
template constexpr double TAU<double>;
template constexpr long double TAU<long double>;

template <typename T = double>
constexpr T E = boost::math::constants::e<T>();
template constexpr float E<float>;
template constexpr double E<double>;
template constexpr long double E<long double>;

template <typename T = double>
constexpr T DEGREE = boost::math::constants::degree<T>();
template constexpr float DEGREE<float>;
template constexpr double DEGREE<double>;
template constexpr long double DEGREE<long double>;

template <typename T = double>
constexpr T RADIAN = boost::math::constants::radian<T>();
template constexpr float RADIAN<float>;
template constexpr double RADIAN<double>;
template constexpr long double RADIAN<long double>;

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_CONSTANTS_H_
