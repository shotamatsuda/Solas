//
//  solas/app/motion_event.h
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
#ifndef SOLAS_APP_MOTION_EVENT_H_
#define SOLAS_APP_MOTION_EVENT_H_

namespace solas {
namespace app {

class MotionEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGIN,
    CANCEL,
    END
  };

 public:
  // Constructors
  MotionEvent();

  // Copy and move
  MotionEvent(const MotionEvent& other) = default;
  MotionEvent(MotionEvent&& other) = default;

  // Disallow assign
  MotionEvent& operator=(const MotionEvent& other) = delete;

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

inline MotionEvent::MotionEvent()
    : type_(Type::UNDEFINED) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_MOTION_EVENT_H_
