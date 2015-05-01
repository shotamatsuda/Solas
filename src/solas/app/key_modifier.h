//
//  solas/app/key_modifier.h
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
#ifndef SOLAS_APP_KEY_MODIFIER_H_
#define SOLAS_APP_KEY_MODIFIER_H_

#include <cstdint>

#include "solas/utility/enum.h"

namespace solas {
namespace app {

enum class KeyModifier : std::uint32_t {
  NONE = 0,
  CAPS = 1 << 0,
  SHIFT = 1 << 1,
  CONTROL = 1 << 2,
  ALTERNATE = 1 << 3,
  COMMAND = 1 << 4,
  FUNCTION = 1 << 5
};

SOLAS_ENUM_BITWISE_OPERATORS(KeyModifier)

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_KEY_MODIFIER_H_
