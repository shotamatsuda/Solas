//
//  solas/easing/preset/elastic.h
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
#ifndef SOLAS_EASING_PRESET_ELASTIC_H_
#define SOLAS_EASING_PRESET_ELASTIC_H_

#include <cmath>

#include "solas/easing/group.h"
#include "solas/math/constants.h"

namespace solas {
namespace easing {
namespace preset {

template <typename T>
struct Elastic {
  T operator()(T parameter) {
    const T v = parameter - 1.0;
    const T p = 0.3;
    return -std::pow(2.0, 10.0 * v) *
        std::sin((v - p / 4.0) * math::tau<T> / p);
  }
};

template <typename T>
using ElasticEasing = Group<T, Elastic>;

}  // namespace preset

template <typename T>
using ElasticEasing = preset::ElasticEasing<T>;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_PRESET_ELASTIC_H_
