//
//  solas/swipe_direction.h
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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
#ifndef SOLAS_SWIPE_DIRECTION_H_
#define SOLAS_SWIPE_DIRECTION_H_

#include <cassert>
#include <ostream>

namespace solas {

enum class SwipeDirection {
  UNDEFINED,
  RIGHT,
  LEFT,
  RELEASED,
  PRESSED,
};

inline std::ostream& operator<<(std::ostream& os, SwipeDirection direction) {
  switch (direction) {
    case SwipeDirection::UNDEFINED:
      os << "undefined";
      break;
    case SwipeDirection::RIGHT:
      os << "right";
      break;
    case SwipeDirection::LEFT:
      os << "left";
      break;
    case SwipeDirection::RELEASED:
      os << "up";
      break;
    case SwipeDirection::PRESSED:
      os << "down";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace solas

#endif  // SOLAS_SWIPE_DIRECTION_H_
