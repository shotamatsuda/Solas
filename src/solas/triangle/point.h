//
//  solas/triangle/point.h
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
