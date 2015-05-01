//
//  solas/app/backend.h
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
#ifndef SOLAS_APP_BACKEND_H_
#define SOLAS_APP_BACKEND_H_

#include "solas/utility/enum.h"

namespace solas {
namespace app {

enum class Backend : int {
  UNDEFINED = 0,
  OPENGL2 = 1 << 0,
  OPENGL3 = 1 << 1,
  OPENGL4 = 1 << 2,
  OPENGLES1 = 1 << 3,
  OPENGLES2 = 1 << 4,
  OPENGLES3 = 1 << 5,
  QUARTZ = 1 << 6
};

SOLAS_ENUM_BITWISE_OPERATORS(Backend);

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_BACKEND_H_
