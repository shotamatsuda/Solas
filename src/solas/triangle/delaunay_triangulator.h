//
//  solas/triangle/delaunay_triangulator.h
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
#ifndef SOLAS_TRIANGLE_DELAUNAY_TRIANGULATOR_H_
#define SOLAS_TRIANGLE_DELAUNAY_TRIANGULATOR_H_

#include <cstddef>
#include <vector>

#include "solas/triangle/triangle_iterator.h"
#include "solas/triangle/triangulator.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

class DelaunayTriangulator : public Triangulator {
 public:
  enum class Type {
    DEFAULT = 0,
    CONSTRAINED,
    CONFORMING,
    CONSTRAINED_CONFORMING
  };

 public:
  // Constructors
  DelaunayTriangulator();
  explicit DelaunayTriangulator(Type type);

  // Copy and assign
  DelaunayTriangulator(const DelaunayTriangulator& other) = default;
  DelaunayTriangulator& operator=(const DelaunayTriangulator& other) = default;

  // Triangulation
  using Triangulator::operator();
  bool operator()(const std::vector<Real>& coordinates) override;

  // Attributes
  std::size_t size() const override;

  // Iterator
  TriangleIterator begin() const;
  TriangleIterator end() const;

 private:
  // Parameters
  Type type;
};

#pragma mark -

inline DelaunayTriangulator::DelaunayTriangulator() : type(Type::DEFAULT) {}

inline DelaunayTriangulator::DelaunayTriangulator(Type type) : type(type) {}

}  // namespace triangle
  
using triangle::DelaunayTriangulator;
  
}  // namespace solas

#endif  // SOLAS_TRIANGLE_DELAUNAY_TRIANGULATOR_H_
