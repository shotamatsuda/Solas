//
//  solas/mouse_button.h
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
#ifndef SOLAS_MOUSE_BUTTON_H_
#define SOLAS_MOUSE_BUTTON_H_

#include <cassert>
#include <ostream>

namespace solas {

enum class MouseButton : int {
  UNDEFINED = -1,
  LEFT = 0,
  RIGHT = 1,
  MIDDLE = 2,
  ZERO = LEFT,
  ONE = RIGHT,
  TWO = MIDDLE,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9
};

inline std::ostream& operator<<(std::ostream& os, MouseButton button) {
  switch (button) {
    case MouseButton::UNDEFINED:
      os << "undefined";
      break;
    case MouseButton::LEFT:
      os << "left";
      break;
    case MouseButton::RIGHT:
      os << "right";
      break;
    case MouseButton::MIDDLE:
      os << "middle";
      break;
    case MouseButton::THREE:
      os << "button3";
      break;
    case MouseButton::FOUR:
      os << "button4";
      break;
    case MouseButton::FIVE:
      os << "button5";
      break;
    case MouseButton::SIX:
      os << "button6";
      break;
    case MouseButton::SEVEN:
      os << "button7";
      break;
    case MouseButton::EIGHT:
      os << "button8";
      break;
    case MouseButton::NINE:
      os << "button9";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace solas

#endif  // SOLAS_MOUSE_BUTTON_H_
