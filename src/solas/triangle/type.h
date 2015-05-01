//
//  solas/triangle/type.h
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
#ifndef SOLAS_TRIANGLE_TYPE_H_
#define SOLAS_TRIANGLE_TYPE_H_

#include "solas/math/line2.h"
#include "solas/math/triangle2.h"
#include "solas/math/vector2.h"

namespace solas {
namespace triangle {

using Real = double;
using Vector = math::Vector2<Real>;
using Line = math::Line2<Real>;
using Triangle = math::Triangle2<Real>;

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_TYPE_H_
