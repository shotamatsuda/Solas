//
//  solas/tween/transform.h
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
#ifndef SOLAS_TWEEN_TRANFORM_H_
#define SOLAS_TWEEN_TRANFORM_H_

#include "solas/tween/easing.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename T>
T Transform(const Easing& easing, Unit unit, const T& from, const T& to);

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TRANFORM_H_
