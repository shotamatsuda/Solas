//
//  solas/app/swipe_direction.h
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
#ifndef SOLAS_APP_SWIPE_DIRECTION_H_
#define SOLAS_APP_SWIPE_DIRECTION_H_

#include <cassert>
#include <ostream>

namespace solas {
namespace app {

enum class SwipeDirection {
  UNDEFINED,
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
