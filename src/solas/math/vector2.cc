//
//  solas/math/vector2.cc
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

#include "solas/math/vector2.h"

#include <cstdint>

#include "SkPoint.h"

namespace solas {
namespace math {

#pragma mark Mutators

template <typename T>
void Vector2<T>::set(const SkPoint& point) {
  x = point.x();
  y = point.y();
}

#pragma mark Implicit conversion

template <typename T>
Vector2<T>::operator SkPoint() const {
  return SkPoint::Make(x, y);
}

template class Vector<std::int8_t, 2>;
template class Vector<std::uint8_t, 2>;
template class Vector<std::int16_t, 2>;
template class Vector<std::uint16_t, 2>;
template class Vector<std::int32_t, 2>;
template class Vector<std::uint32_t, 2>;
template class Vector<float, 2>;
template class Vector<double, 2>;
template class Vector<long double, 2>;

}  // namespace math
}  // namespace solas
