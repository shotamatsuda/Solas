//
//  solas/tween/easing.h
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
#ifndef SOLAS_TWEEN_EASING_H_
#define SOLAS_TWEEN_EASING_H_

#include "solas/easing/preset.h"
#include "solas/easing/type.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

using Easing = easing::Easing<Unit>;
using BackEasing = easing::BackEasing<Unit>;
using BounceEasing = easing::BounceEasing<Unit>;
using CircularEasing = easing::CircularEasing<Unit>;
using CubicEasing = easing::CubicEasing<Unit>;
using ElasticEasing = easing::ElasticEasing<Unit>;
using ExponentialEasing = easing::ExponentialEasing<Unit>;
using LinearEasing = easing::LinearEasing<Unit>;
using QuadraticEasing = easing::QuadraticEasing<Unit>;
using QuarticEasing = easing::QuarticEasing<Unit>;
using QuinticEasing = easing::QuinticEasing<Unit>;
using SinusoidalEasing = easing::SinusoidalEasing<Unit>;

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_EASING_H_

