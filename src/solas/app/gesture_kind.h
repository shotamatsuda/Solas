//
//  solas/app/gesture_kind.h
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
