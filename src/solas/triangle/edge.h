//
//  solas/triangle/edge.h
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
#ifndef SOLAS_TRIANGLE_EDGE_H_
#define SOLAS_TRIANGLE_EDGE_H_

#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

class Edge final {
 public:
  // Constructors
  Edge();

  // Copy and assign
  Edge(const Edge& other) = default;
  Edge& operator=(const Edge& other) = default;

 public:
  union {
    Line line;
    struct { Vector a; Vector b; };
    struct { Real x1; Real y1; Real x2; Real y2; };
  };
  bool finite;
};

#pragma mark -

inline Edge::Edge() : line(), finite(false) {}

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_EDGE_H_
