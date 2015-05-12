//
//  solas/app/app_event.h
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
#ifndef SOLAS_APP_APP_EVENT_H_
#define SOLAS_APP_APP_EVENT_H_

#include "solas/app/context_holder.h"
#include "solas/math/size.h"

namespace solas {
namespace app {

class AppEvent final {
 public:
  enum class Type {
    UNDEFINED,
    SETUP,
    UPDATE,
    PRE,
    DRAW,
    POST,
    EXIT
  };

 public:
  // Constructors
  AppEvent() {}
  template <typename Context>
  AppEvent(const Context& context, const math::Size2d& size, double scale);

  // Copy and move
  AppEvent(const AppEvent& other) = default;
  AppEvent(AppEvent&& other) = default;

  // Disallow assign
  AppEvent& operator=(const AppEvent& other) = delete;

  // Properties
  const ContextHolder& context() const { return context_; }
  const math::Size2d& size() const { return size_; }
  double scale() const { return scale_; }

 private:
  ContextHolder context_;
  math::Size2d size_;
  double scale_;
};

#pragma mark -

template <typename Context>
inline AppEvent::AppEvent(const Context& context,
                          const math::Size2d& size,
                          double scale)
    : context_(context),
      size_(size),
      scale_(scale) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_APP_EVENT_H_
