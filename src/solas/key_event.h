//
//  solas/key_event.h
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
#ifndef SOLAS_KEY_EVENT_H_
#define SOLAS_KEY_EVENT_H_

#include <cstdint>
#include <string>

#include "solas/key_modifier.h"

namespace solas {

class KeyEvent final {
 public:
  enum class Type {
    UNDEFINED,
    PRESSED,
    RELEASED
  };

 public:
  KeyEvent();
  KeyEvent(Type type,
           std::uint32_t code,
           const std::string& characters,
           KeyModifier modifiers);

  // Copy semantics excluding assignment
  KeyEvent(const KeyEvent&) = default;
  KeyEvent& operator=(const KeyEvent&) = delete;

  // Properties
  bool empty() const { return type_ == Type::UNDEFINED; }
  Type type() const { return type_; }
  std::uint32_t code() const { return code_; }
  const std::string& characters() const { return characters_; }
  KeyModifier modifiers() const { return modifiers_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  std::uint32_t code_;
  std::string characters_;
  KeyModifier modifiers_;
};

#pragma mark -

inline KeyEvent::KeyEvent()
    : type_(Type::UNDEFINED),
      code_(),
      modifiers_(KeyModifier::NONE) {}

inline KeyEvent::KeyEvent(Type type,
                          std::uint32_t code,
                          const std::string& characters,
                          KeyModifier modifiers)
    : type_(type),
      code_(code),
      characters_(characters),
      modifiers_(modifiers) {}

}  // namespace solas

#endif  // SOLAS_KEY_EVENT_H_
