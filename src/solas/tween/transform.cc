//
//  solas/tween/transform.cc
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
