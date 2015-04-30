//
//  solas/app/swipe_direction.h
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
#ifndef SOLAS_APP_SWIPE_DIRECTION_H_
#define SOLAS_APP_SWIPE_DIRECTION_H_

#include <cassert>
#include <ostream>

namespace solas {
namespace app {

enum class SwipeDirection {
  UNDEFINED = -1,
  RIGHT,
  LEFT,
  UP,
  DOWN,
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
    case SwipeDirection::UP:
      os << "up";
      break;
    case SwipeDirection::DOWN:
      os << "down";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_SWIPE_DIRECTION_H_