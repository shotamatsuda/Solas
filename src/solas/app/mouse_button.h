//
//  solas/app/mouse_button.h
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
#ifndef SOLAS_APP_MOUSE_BUTTON_H_
#define SOLAS_APP_MOUSE_BUTTON_H_

namespace solas {
namespace app {

enum class MouseButton : int {
  UNDEFINED = -1,
  ZERO = 0,
  ONE = 1,
  TWO = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9,
  LEFT = ZERO,
  RIGHT = ONE,
  MIDDLE = TWO
};

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_MOUSE_BUTTON_H_
