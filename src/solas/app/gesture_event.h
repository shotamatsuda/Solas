//
//  solas/app/gesture_event.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
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
#ifndef SOLAS_APP_GESTURE_EVENT_H_
#define SOLAS_APP_GESTURE_EVENT_H_

#include <boost/any.hpp>

#include "solas/app/gesture_kind.h"
#include "solas/app/screen_edge.h"
#include "solas/app/swipe_direction.h"
#include "solas/math/vector.h"

namespace solas {
namespace app {

class GestureEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGIN,
    CHANGE,
    CANCEL,
    END
  };

  struct TapData {
    std::size_t taps;
  };

  struct PinchData {
    double scale;
    math::Vec2d velocity;
  };

  struct RotationData {
    double rotation;
    math::Vec2d velocity;
  };

  struct SwipeData {
    SwipeDirection direction;
  };

  struct PanData {
    math::Vec2d translation;
    math::Vec2d velocity;
  };

  struct ScreenEdgeData {
    ScreenEdge edges;
  };

  struct LongPressData {
    std::size_t taps;
  };

 public:
  // Constructors
  GestureEvent();
  GestureEvent(Type type,
               GestureKind kind,
               const std::vector<math::Vec2d>& touches);
  GestureEvent(Type type,
               GestureKind kind,
               const std::vector<math::Vec2d>& touches,
               SwipeDirection direction);

  // Copy and move
  GestureEvent(const GestureEvent& other) = default;
  GestureEvent(GestureEvent&& other) = default;

  // Disallow assign
  GestureEvent& operator=(const GestureEvent& other) = delete;

  // Attributes
  bool empty() const { return type == Type::UNDEFINED; }

  // Conversion
  operator bool() const { return !empty(); }

 public:
  Type type;
  GestureKind kind;
  std::vector<math::Vec2d> touches;
  boost::any data;
};

#pragma mark -

inline GestureEvent::GestureEvent()
    : type(Type::UNDEFINED),
      kind(GestureKind::UNDEFINED) {}

inline GestureEvent::GestureEvent(
    Type type,
    GestureKind kind,
    const std::vector<math::Vec2d>& touches)
    : type(type),
      kind(kind),
      touches(touches) {}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_GESTURE_EVENT_H_
