//
//  solas/tween/type.h
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

