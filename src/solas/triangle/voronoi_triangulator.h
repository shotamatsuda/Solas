//
//  solas/triangle/voronoi_triangulator.h
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
#ifndef SOLAS_TRIANGLE_VORONOI_TRIANGULATOR_H_
#define SOLAS_TRIANGLE_VORONOI_TRIANGULATOR_H_

#include <cstddef>
#include <vector>

#include "solas/triangle/edge_iterator.h"
#include "solas/triangle/triangulator.h"

namespace solas {
namespace triangle {

class VoronoiTriangulator : public Triangulator {
 public:
  // Constructors
  VoronoiTriangulator() = default;

  // Copy and assign
  VoronoiTriangulator(const VoronoiTriangulator& other) = default;
  VoronoiTriangulator& operator=(const VoronoiTriangulator& other) = default;

  // Triangulation
  using Triangulator::operator();
  bool operator()(const std::vector<double>& coordinates) override;

  // Attributes
  std::size_t size() const override;

  // Iterator
  EdgeIterator begin() const;
  EdgeIterator end() const;
};

}  // namespace triangle
  
using triangle::VoronoiTriangulator;
  
}  // namespace solas

#endif  // SOLAS_TRIANGLE_VORONOI_TRIANGULATOR_H_
