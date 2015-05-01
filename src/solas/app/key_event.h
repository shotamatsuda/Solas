//
//  solas/app/key_event.h
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
#ifndef SOLAS_APP_KEY_EVENT_H_
#define SOLAS_APP_KEY_EVENT_H_

namespace solas {
namespace app {

class KeyEvent final {
 public:
  enum class Type {
    UNDEFINED,
    DOWN,
    UP
  };

 public:
  // Constructors
  KeyEvent();

  // Copy and move
  KeyEvent(const KeyEvent& other) = default;
  KeyEvent(KeyEvent&& other) = default;

  // Disallow assign
  KeyEvent& operator=(const KeyEvent& other) = delete;

  // Attributes
  bool empty() const { return type_ == Type::UNDEFINED; }

  // Properties
  Type type() const { return type_; }

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
};

#pragma mark -

inline KeyEvent::KeyEvent()
    : type_(Type::UNDEFINED) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_KEY_EVENT_H_
