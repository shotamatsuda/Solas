//
//  solas/mouse_button.h
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
  _0 = LEFT,
  _1 = RIGHT,
  _2 = MIDDLE,
  _3 = 3,
  _4 = 4,
  _5 = 5,
  _6 = 6,
  _7 = 7,
  _8 = 8,
  _9 = 9
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
    case MouseButton::_3:
      os << "button3";
      break;
    case MouseButton::_4:
      os << "button4";
      break;
    case MouseButton::_5:
      os << "button5";
      break;
    case MouseButton::_6:
      os << "button6";
      break;
    case MouseButton::_7:
      os << "button7";
      break;
    case MouseButton::_8:
      os << "button8";
      break;
    case MouseButton::_9:
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
