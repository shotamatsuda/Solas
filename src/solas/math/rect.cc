//
//  solas/math/rect.cc
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

#include "solas/math/rect.h"

#include "solas/tween/easing.h"
#include "solas/tween/transform.h"
#include "solas/tween/type.h"

namespace solas {
namespace math {

//template class Rect<std::int8_t>;
//template class Rect<std::uint8_t>;
//template class Rect<std::int16_t>;
//template class Rect<std::uint16_t>;
//template class Rect<std::int32_t>;
//template class Rect<std::uint32_t>;
//template class Rect<float>;
//template class Rect<double>;
//template class Rect<long double>;

}  // namespace math

#pragma mark Tween support

namespace tween {

template <typename T>
T Transform(const Easing& easing, Unit unit, const T& from, const T& to) {
  return T(from.origin + (to.origin - from.origin) * easing(unit),
           from.size + (to.size - from.size) * easing(unit));
}

#define SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(T) \
    template math::Rect<T> Transform( \
        const Easing& easing, Unit unit, \
        const math::Rect<T>& from, \
        const math::Rect<T>& to);

SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::int8_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::uint8_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::int16_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::uint16_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::int32_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(std::uint32_t)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(float)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(double)
SOLAS_MATH_RECT_TWEEN_TRANSFORM_SPECIALIZE(long double)

}  // namespace tween

}  // namespace solas
