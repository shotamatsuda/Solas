//
//  solas/app/gesture_kind.h
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
#ifndef SOLAS_APP_GESTURE_KIND_H_
#define SOLAS_APP_GESTURE_KIND_H_

namespace solas {
namespace app {

enum class GestureKind {
  UNDEFINED,
  TAP,
  DOUBLE_TAP,
  TRIPLE_TAP,
  PINCH,
  ROTATION,
  SWIPE,
  TWO_FINGERS_SWIPE,
  THREE_FINGERS_SWIPE,
  FOUR_FINGERS_SWIPE,
  PAN,
  TWO_FINGERS_PAN,
  THREE_FINGERS_PAN,
  FOUR_FINGERS_PAN,
  SCREEN_EDGE_TOP,
  SCREEN_EDGE_LEFT,
  SCREEN_EDGE_BOTTOM,
  SCREEN_EDGE_RIGHT
};

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_GESTURE_KIND_H_
