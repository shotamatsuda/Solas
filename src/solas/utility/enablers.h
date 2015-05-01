//
//  solas/utility/enablers.h
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
#ifndef SOLAS_UTILITY_ENABLERS_H_
#define SOLAS_UTILITY_ENABLERS_H_

#include <type_traits>

namespace solas {
namespace utility {

template <typename T, typename U = void>
using EnableIfScalar = typename std::enable_if<
    std::is_scalar<T>::value, U>::type;
template <typename T, typename U = void>
using EnableIfIntegral = typename std::enable_if<
    std::is_integral<T>::value, U>::type;
template <typename T, typename U = void>
using EnableIfFloating = typename std::enable_if<
    std::is_floating_point<T>::value, U>::type;

}  // namespace utility

using utility::EnableIfScalar;
using utility::EnableIfIntegral;
using utility::EnableIfFloating;

}  // namespace solas

#endif  // SOLAS_UTILITY_ENABLERS_H_
