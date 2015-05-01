//
//  solas/utility/enum.h
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
#ifndef SOLAS_UTILITY_ENUM_H_
#define SOLAS_UTILITY_ENUM_H_

#include <type_traits>

#define SOLAS_ENUM_BITWISE_OPERATORS(T)                                        \
    constexpr std::underlying_type<T>::type operator%(T a, T b) {              \
      return static_cast<std::underlying_type<T>::type>(                       \
          static_cast<std::underlying_type<T>::type>(a) &                      \
          static_cast<std::underlying_type<T>::type>(b));                      \
    };                                                                         \
    constexpr T operator&(T a, T b) {                                          \
      return static_cast<T>(                                                   \
          static_cast<std::underlying_type<T>::type>(a) &                      \
          static_cast<std::underlying_type<T>::type>(b));                      \
    };                                                                         \
    constexpr T operator|(T a, T b) {                                          \
      return static_cast<T>(                                                   \
          static_cast<std::underlying_type<T>::type>(a) |                      \
          static_cast<std::underlying_type<T>::type>(b));                      \
    };                                                                         \
    constexpr T operator^(T a, T b) {                                          \
      return static_cast<T>(                                                   \
          static_cast<std::underlying_type<T>::type>(a) ^                      \
          static_cast<std::underlying_type<T>::type>(b));                      \
    };                                                                         \
    constexpr T operator~(T a) {                                               \
      return static_cast<T>(~static_cast<std::underlying_type<T>::type>(a));   \
    };                                                                         \
    constexpr T& operator&=(T& a, T b) {                                       \
      return a = a & b;                                                        \
    };                                                                         \
    constexpr T& operator|=(T& a, T b) {                                       \
      return a = a | b;                                                        \
    };                                                                         \
    constexpr T& operator^=(T& a, T b) {                                       \
      return a = a ^ b;                                                        \
    };

#endif  // SOLAS_UTILITY_ENUM_H_
