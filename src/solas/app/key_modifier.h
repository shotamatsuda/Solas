//
//  solas/app/key_modifier.h
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
#ifndef SOLAS_APP_KEY_MODIFIER_H_
#define SOLAS_APP_KEY_MODIFIER_H_

#include <cstdint>

#include "solas/utility/enum.h"

namespace solas {
namespace app {

enum class KeyModifier : std::uint32_t {
  NONE = 0,
  CAPS = 1 << 0,
  SHIFT = 1 << 1,
  CONTROL = 1 << 2,
  ALTERNATE = 1 << 3,
  COMMAND = 1 << 4,
  FUNCTION = 1 << 5
};

SOLAS_ENUM_BITWISE_OPERATORS(KeyModifier, std::uint32_t)

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_KEY_MODIFIER_H_
