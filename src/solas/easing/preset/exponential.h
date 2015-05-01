//
//  solas/easing/preset/exponential.h
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
#ifndef SOLAS_EASING_PRESET_EXPONENTIAL_H_
#define SOLAS_EASING_PRESET_EXPONENTIAL_H_

#include <cmath>

#include "solas/easing/group.h"

namespace solas {
namespace easing {
namespace preset {

template <typename T>
struct Exponential {
  T operator()(T parameter) {
    if (parameter == 0.0) {
      return 0.0;
    }
    return std::pow(2.0, 10.0 * (parameter - 1.0));
  }
};

template <typename T>
using ExponentialEasing = Group<T, Exponential>;

}  // namespace preset

template <typename T>
using ExponentialEasing = preset::ExponentialEasing<T>;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_PRESET_EXPONENTIAL_H_
