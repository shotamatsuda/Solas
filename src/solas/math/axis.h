//
//  solas/math/axis.h
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

#pragma once
#ifndef SOLAS_MATH_AXIS_H_
#define SOLAS_MATH_AXIS_H_

#include <cassert>
#include <ostream>

namespace solas {
namespace math {

enum class Axis : int {
  X = 0,
  Y = 1,
  Z = 2,
  W = 3
};

inline std::ostream& operator<<(std::ostream& os, Axis axis) {
  switch (axis) {
    case Axis::X:
      os << "x";
      break;
    case Axis::Y:
      os << "y";
      break;
    case Axis::Z:
      os << "z";
      break;
    case Axis::W:
      os << "w";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_AXIS_H_
