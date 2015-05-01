//
//  solas/math/constants.h
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
#ifndef SOLAS_MATH_CONSTANTS_H_
#define SOLAS_MATH_CONSTANTS_H_

#include <boost/math/constants/constants.hpp>

namespace solas {
namespace math {

template <typename T = double>
constexpr const T e = boost::math::constants::e<T>();
template constexpr const float e<float>;
template constexpr const double e<double>;
template constexpr const long double e<long double>;

template <typename T = double>
constexpr const T pi = boost::math::constants::pi<T>();
template constexpr const float pi<float>;
template constexpr const double pi<double>;
template constexpr const long double pi<long double>;

template <typename T = double>
constexpr const T half_pi = boost::math::constants::half_pi<T>();
template constexpr const float half_pi<float>;
template constexpr const double half_pi<double>;
template constexpr const long double half_pi<long double>;

template <typename T = double>
constexpr const T third_pi = boost::math::constants::third_pi<T>();
template constexpr const float third_pi<float>;
template constexpr const double third_pi<double>;
template constexpr const long double third_pi<long double>;

template <typename T = double>
constexpr const T quarter_pi = boost::math::constants::half_pi<T>() / 2;
template constexpr const float quarter_pi<float>;
template constexpr const double quarter_pi<double>;
template constexpr const long double quarter_pi<long double>;

template <typename T = double>
constexpr const T two_pi = boost::math::constants::two_pi<T>();
template constexpr const float two_pi<float>;
template constexpr const double two_pi<double>;
template constexpr const long double two_pi<long double>;

template <typename T = double>
constexpr const T tau = boost::math::constants::two_pi<T>();
template constexpr const float tau<float>;
template constexpr const double tau<double>;
template constexpr const long double tau<long double>;

template <typename T = double>
constexpr const T degree = boost::math::constants::degree<T>();
template constexpr const float degree<float>;
template constexpr const double degree<double>;
template constexpr const long double degree<long double>;

template <typename T = double>
constexpr const T radian = boost::math::constants::radian<T>();
template constexpr const float radian<float>;
template constexpr const double radian<double>;
template constexpr const long double radian<long double>;

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_CONSTANTS_H_
