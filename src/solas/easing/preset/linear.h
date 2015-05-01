//
//  solas/easing/preset/linear.h
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
#ifndef SOLAS_EASING_PRESET_LINEAR_H_
#define SOLAS_EASING_PRESET_LINEAR_H_

#include "solas/easing/group.h"

namespace solas {
namespace easing {
namespace preset {

template <typename T>
struct Linear {
  T operator()(T parameter) {
    return parameter;
  }
};

template <typename T>
using LinearEasing = Group<T, Linear>;

}  // namespace preset

template <typename T>
using LinearEasing = preset::LinearEasing<T>;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_PRESET_LINEAR_H_
