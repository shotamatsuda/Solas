//
//  solas/processing/types.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef SOLAS_PROCESSING_TYPES_H_
#define SOLAS_PROCESSING_TYPES_H_

#include <tuple>

#include "solas/graphics/color.h"
#include "solas/math/size.h"
#include "solas/math/vector.h"

namespace solas {
namespace processing {

using Real = double;
using Real2 = std::tuple<Real, Real>;
using Real3 = std::tuple<Real, Real, Real>;
using Real4 = std::tuple<Real, Real, Real, Real>;
using Real5 = std::tuple<Real, Real, Real, Real, Real>;
using Real6 = std::tuple<Real, Real, Real, Real, Real, Real>;
using Real7 = std::tuple<Real, Real, Real, Real, Real, Real, Real>;
using Color = graphics::Color4<Real>;
template <int Dimensions>
using Vec = math::Vector<Real, Dimensions>;
using Vec2 = math::Vector2<Real>;
using Vec3 = math::Vector3<Real>;
using Vec4 = math::Vector4<Real>;
template <int Dimensions>
using Size = math::Size<Real, Dimensions>;
using Size2 = math::Size2<Real>;
using Size3 = math::Size3<Real>;

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_TYPES_H_
