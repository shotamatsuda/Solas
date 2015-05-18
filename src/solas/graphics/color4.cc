//
//  solas/graphics/color4.cc
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

#include "solas/graphics/color4.h"

#include <cstdint>

#include "nanovg.h"

namespace solas {
namespace graphics {

#pragma mark Mutators

template <typename T>
void Color4<T>::set(const NVGcolor& color) {
  r = ColorDepth<T>::Convert(color.r);
  g = ColorDepth<T>::Convert(color.g);
  b = ColorDepth<T>::Convert(color.b);
  a = ColorDepth<T>::Convert(color.a);
}

#pragma mark Implicit conversion

template <typename T>
inline Color4<T>::operator NVGcolor() const {
  return {{{
    ColorDepth<float>::Convert(red),
    ColorDepth<float>::Convert(green),
    ColorDepth<float>::Convert(blue),
    ColorDepth<float>::Convert(alpha)
  }}};
}

template class Color<std::int8_t, 4>;
template class Color<std::uint8_t, 4>;
template class Color<std::int16_t, 4>;
template class Color<std::uint16_t, 4>;
template class Color<std::int32_t, 4>;
template class Color<std::uint32_t, 4>;
template class Color<float, 4>;
template class Color<double, 4>;
template class Color<long double, 4>;

}  // namespace graphics
}  // namespace solas
