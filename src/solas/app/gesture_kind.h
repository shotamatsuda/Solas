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

#include <cassert>
#include <ostream>

namespace solas {
namespace app {

enum class GestureKind {
  UNDEFINED,
  TAP,
  PINCH,
  ROTATION,
  SWIPE,
  PAN,
  SCREEN_EDGE
};

inline std::ostream& operator<<(std::ostream& os, GestureKind kind) {
  switch (kind) {
    case GestureKind::UNDEFINED:
      os << "undefined";
      break;
    case GestureKind::TAP:
      os << "tap";
      break;
    case GestureKind::PINCH:
      os << "pinch";
      break;
    case GestureKind::ROTATION:
      os << "rotation";
      break;
    case GestureKind::SWIPE:
      os << "swipe";
      break;
    case GestureKind::PAN:
      os << "pan";
      break;
    case GestureKind::SCREEN_EDGE:
      os << "screen edge";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_GESTURE_KIND_H_
