//
//  solas/key_modifier.h
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
#ifndef SOLAS_KEY_MODIFIER_H_
#define SOLAS_KEY_MODIFIER_H_

#include <cassert>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "solas/enum.h"

namespace solas {

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

inline std::ostream& operator<<(std::ostream& os, KeyModifier modifier) {
  if (modifier == KeyModifier::NONE) {
    os << "none";
  } else {
    std::vector<std::string> list;
    if ((modifier & KeyModifier::CAPS) != KeyModifier::NONE) {
      list.emplace_back("caps");
    }
    if ((modifier & KeyModifier::SHIFT) != KeyModifier::NONE) {
      list.emplace_back("shift");
    }
    if ((modifier & KeyModifier::CONTROL) != KeyModifier::NONE) {
      list.emplace_back("control");
    }
    if ((modifier & KeyModifier::ALTERNATE) != KeyModifier::NONE) {
      list.emplace_back("alternate");
    }
    if ((modifier & KeyModifier::COMMAND) != KeyModifier::NONE) {
      list.emplace_back("command");
    }
    if ((modifier & KeyModifier::FUNCTION) != KeyModifier::NONE) {
      list.emplace_back("function");
    }
    assert(!list.empty());
    os << boost::algorithm::join(list, " ");
  }
  return os;
}

}  // namespace solas

#endif  // SOLAS_KEY_MODIFIER_H_
