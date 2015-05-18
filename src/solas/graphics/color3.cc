//
//  solas/graphics/color3.cc
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

#include "solas/graphics/color3.h"

#include <cstdint>

#include "nanovg.h"

namespace solas {
namespace graphics {

#pragma mark Mutators

template <typename T>
void Color3<T>::set(const NVGcolor& color) {
  r = ColorDepth<T>::Convert(color.r);
  g = ColorDepth<T>::Convert(color.g);
  b = ColorDepth<T>::Convert(color.b);
}

#pragma mark Implicit conversion

template <typename T>
inline Color3<T>::operator NVGcolor() const {
  return {{{
    ColorDepth<float>::Convert(red),
    ColorDepth<float>::Convert(green),
    ColorDepth<float>::Convert(blue),
    1.0
  }}};
}

template class Color<std::int8_t, 3>;
template class Color<std::uint8_t, 3>;
template class Color<std::int16_t, 3>;
template class Color<std::uint16_t, 3>;
template class Color<std::int32_t, 3>;
template class Color<std::uint32_t, 3>;
template class Color<float, 3>;
template class Color<double, 3>;
template class Color<long double, 3>;

}  // namespace graphics
}  // namespace solas
