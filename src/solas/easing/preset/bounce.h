//
//  solas/easing/preset/bounce.h
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
#ifndef SOLAS_EASING_PRESET_BOUNCE_H_
#define SOLAS_EASING_PRESET_BOUNCE_H_

#include "solas/easing/group.h"

namespace solas {
namespace easing {
namespace preset {

template <typename T>
struct Bounce {
  T operator()(T parameter) {
    const T v = 1.0 - parameter;
    T c;
    T d;
    if (v < (1.0 / 2.750)) {
      c = v;
      d = 0;
    } else if (v < (2.0 / 2.750)) {
      c = v - 1.50 / 2.750;
      d = 0.750;
    } else if (v < (2.5 / 2.750)) {
      c = v - 2.250 / 2.750;
      d = 0.93750;
    } else {
      c = v - 2.6250 / 2.750;
      d = 0.9843750;
    }
    return 1.0 - (7.56250 * c * c + d);
  }
};

template <typename T>
using BounceEasing = Group<T, Bounce>;

}  // namespace preset

template <typename T>
using BounceEasing = preset::BounceEasing<T>;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_PRESET_BOUNCE_H_
