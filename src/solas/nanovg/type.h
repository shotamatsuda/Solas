//
//  solas/nanovg/type.h
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
#ifndef SOLAS_NANOVG_TYPE_H_
#define SOLAS_NANOVG_TYPE_H_

#include "solas/math/size.h"
#include "solas/math/vector.h"

namespace solas {
namespace nanovg {

using Real = float;
using Vec2 = math::Vec2<Real>;
using Size2 = math::Size2<Real>;

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_TYPE_H_
