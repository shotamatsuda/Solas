//
//  solas/tween/transform.cc
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

#include "solas/tween/transform.h"

#include "solas/tween/easing.h"
#include "solas/tween/type.h"

namespace solas {
namespace tween {

template <typename T>
T Transform(const Easing& easing, Unit unit, const T& from, const T& to) {
  return from + (to - from) * easing(unit);
}

#define SOLAS_TWEEN_TRANSFORM_SPECIALIZE(T) \
    template T Transform(const Easing&, Unit, const T&, const T&);

SOLAS_TWEEN_TRANSFORM_SPECIALIZE(bool)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(char)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(signed char)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(unsigned char)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(char16_t)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(char32_t)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(wchar_t)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(short)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(unsigned short)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(int)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(unsigned int)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(long)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(unsigned long)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(long long)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(unsigned long long)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(float)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(double)
SOLAS_TWEEN_TRANSFORM_SPECIALIZE(long double)

}  // namespace tween
}  // namespace solas
