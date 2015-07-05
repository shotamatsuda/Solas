//
//  solas/app/backend.h
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

#pragma once
#ifndef SOLAS_APP_BACKEND_H_
#define SOLAS_APP_BACKEND_H_

#include "solas/utility/enum.h"

namespace solas {
namespace app {

enum class Backend : int {
  UNDEFINED = 0,
  QUARTZ = 1 << 0,
  OPENGL2 = 1 << 1,
  OPENGL3 = 1 << 2,
  OPENGL4 = 1 << 3,
  OPENGLES1 = 1 << 4,
  OPENGLES2 = 1 << 5,
  OPENGLES3 = 1 << 6
};

SOLAS_ENUM_BITWISE_OPERATORS(Backend);

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_BACKEND_H_
