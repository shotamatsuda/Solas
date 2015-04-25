//
//  solas/tween/type.h
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
#ifndef SOLAS_TWEEN_TYPE_H_
#define SOLAS_TWEEN_TYPE_H_

#include <cstdint>
#include <functional>

#ifndef SOLAS_TWEEN_UNIT_TYPE
#define SOLAS_TWEEN_UNIT_TYPE double
#endif

#ifndef SOLAS_TWEEN_TIME_VALUE_TYPE
#define SOLAS_TWEEN_TIME_VALUE_TYPE double
#endif

#ifndef SOLAS_TWEEN_FRAME_VALUE_TYPE
#define SOLAS_TWEEN_FRAME_VALUE_TYPE std::int64_t
#endif

namespace solas {
namespace tween {

using Unit = SOLAS_TWEEN_UNIT_TYPE;
using TimeValue = SOLAS_TWEEN_TIME_VALUE_TYPE;
using FrameValue = SOLAS_TWEEN_FRAME_VALUE_TYPE;
using Callback = std::function<void()>;

}  // namespace tween
}  // namespace solas

#endif  // SOLAS_TWEEN_TYPE_H_
