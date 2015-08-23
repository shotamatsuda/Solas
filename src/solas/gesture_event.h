//
//  solas/gesture_event.h
//
//  The MIT License
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
#ifndef SOLAS_GESTURE_EVENT_H_
#define SOLAS_GESTURE_EVENT_H_

#include <cassert>
#include <cstddef>
#include <ostream>
#include <vector>

#include <boost/any.hpp>

#include "solas/gesture_kind.h"
#include "solas/screen_edge.h"
#include "solas/swipe_direction.h"
#include "solas/math.h"

namespace solas {

class GestureEvent final {
 public:
  enum class Type {
    UNDEFINED,
    BEGAN,
    CHANGED,
    CANCELLED,
    ENDED
  };

  struct TapData {
    std::size_t taps;
    std::size_t touches;
  };

  struct PinchData {
    double scale;
    double velocity;
  };

  struct RotationData {
    double rotation;
    double velocity;
  };

  struct SwipeData {
    SwipeDirection direction;
    std::size_t touches;
  };

  struct PanData {
    Vec2d translation;
    Vec2d velocity;
    std::size_t touches;
  };

  struct ScreenEdgeData {
    ScreenEdge edge;
  };

 public:
  GestureEvent();
  template <class Data>
  GestureEvent(Type type,
               GestureKind kind,
               const std::vector<Vec2d>& touches,
               const Data& data);
  GestureEvent(Type type,
               GestureKind kind,
               const std::vector<Vec2d>& touches,
               const boost::any& data);

  // Copy semantics excluding assignment
  GestureEvent(const GestureEvent&) = default;
  GestureEvent& operator=(const GestureEvent&) = delete;

  // Properties
  bool empty() const { return type_ == Type::UNDEFINED; }
  Type type() const { return type_; }
  GestureKind kind() const { return kind_; }
  const std::vector<Vec2d>& touches() const { return touches_; }

  // Gesture data
  const TapData& tap() const;
  const PinchData& pinch() const;
  const RotationData& rotation() const;
  const SwipeData& swipe() const;
  const PanData& pan() const;
  const ScreenEdgeData& screen_edge() const;

  // Conversion
  operator bool() const { return !empty(); }

 private:
  Type type_;
  GestureKind kind_;
  std::vector<Vec2d> touches_;
  boost::any data_;
};

#pragma mark -

inline GestureEvent::GestureEvent()
    : type_(Type::UNDEFINED),
      kind_(GestureKind::UNDEFINED) {}

template <class Data>
inline GestureEvent::GestureEvent(Type type,
                                  GestureKind kind,
                                  const std::vector<Vec2d>& touches,
                                  const Data& data)
    : type_(type),
      kind_(kind),
      touches_(touches),
      data_(data) {}

inline GestureEvent::GestureEvent(Type type,
                                  GestureKind kind,
                                  const std::vector<Vec2d>& touches,
                                  const boost::any& data)
    : type_(type),
      kind_(kind),
      touches_(touches),
      data_(data) {}

#pragma mark Gesture data

inline const GestureEvent::TapData& GestureEvent::tap() const {
  assert(kind_ == GestureKind::TAP);
  return *boost::any_cast<TapData>(&data_);
}

inline const GestureEvent::PinchData& GestureEvent::pinch() const {
  assert(kind_ == GestureKind::PINCH);
  return *boost::any_cast<PinchData>(&data_);
}

inline const GestureEvent::RotationData& GestureEvent::rotation() const {
  assert(kind_ == GestureKind::ROTATION);
  return *boost::any_cast<RotationData>(&data_);
}

inline const GestureEvent::SwipeData& GestureEvent::swipe() const {
  assert(kind_ == GestureKind::SWIPE);
  return *boost::any_cast<SwipeData>(&data_);
}

inline const GestureEvent::PanData& GestureEvent::pan() const {
  assert(kind_ == GestureKind::PAN);
  return *boost::any_cast<PanData>(&data_);
}

inline const GestureEvent::ScreenEdgeData& GestureEvent::screen_edge() const {
  assert(kind_ == GestureKind::SCREEN_EDGE);
  return *boost::any_cast<ScreenEdgeData>(&data_);
}

#pragma mark Stream

inline std::ostream& operator<<(std::ostream& os, GestureEvent::Type type) {
  switch (type) {
    case GestureEvent::Type::UNDEFINED:
      os << "undefined";
      break;
    case GestureEvent::Type::BEGAN:
      os << "begin";
      break;
    case GestureEvent::Type::CHANGED:
      os << "change";
      break;
    case GestureEvent::Type::CANCELLED:
      os << "cancel";
      break;
    case GestureEvent::Type::ENDED:
      os << "end";
      break;
    default:
      assert(false);
      break;
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const GestureEvent& event) {
  os << "( type = " << event.type() << ", kind = " << event.kind();
  switch (event.kind()) {
    case GestureKind::UNDEFINED:
      break;
    case GestureKind::TAP:
      os << ", taps = " << event.tap().taps;
      os << ", touches = " << event.tap().touches;
      break;
    case GestureKind::PINCH:
      os << ", scale = " << event.pinch().scale;
      os << ", velocity = " << event.pinch().velocity;
      break;
    case GestureKind::ROTATION:
      break;
    case GestureKind::SWIPE:
      os << ", direction = " << event.swipe().direction;
      os << ", touches = " << event.swipe().touches;
      break;
    case GestureKind::PAN:
      os << ", translation = " << event.pan().translation;
      os << ", velocity = " << event.pan().velocity;
      os << ", touches = " << event.pan().touches;
      break;
    case GestureKind::SCREEN_EDGE:
      os << ", edge = " << event.screen_edge().edge;
      break;
    default:
      assert(false);
      break;
  }
  return os << " )";
}

}  // namespace solas

#endif  // SOLAS_GESTURE_EVENT_H_
