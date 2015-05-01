//
//  solas/triangle/point.h
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
#ifndef SOLAS_TRIANGLE_POINT_H_
#define SOLAS_TRIANGLE_POINT_H_

#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

class Point final {
 public:
  // Constructors
  Point();

  // Implicit conversions
  template <typename T>
  Point(const T& other);
  template <typename T>
  Point& operator=(const T& other);

  // Copy and assign
  Point(const Point& other) = default;
  Point& operator=(const Point& other) = default;

  union {
    Vector vector;
    struct { Real x; Real y; };
  };
  int index;
};

#pragma mark -

inline Point::Point() : vector(), index() {}

#pragma mark Implicit conversions

template <typename T>
inline Point::Point(const T& other) : vector(other.x, other.y), index() {}

template <typename T>
inline Point& Point::operator=(const T& other) {
  vector.x = other.x;
  vector.y = other.y;
  return *this;
}

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_POINT_H_
