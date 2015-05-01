//
//  solas/triangle/voronoi_triangulator.cc
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

#include "solas/triangle/voronoi_triangulator.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "solas/triangle/edge_iterator.h"
#include "solas/triangle/lib.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

#pragma mark Triangulation

bool VoronoiTriangulator::operator()(const std::vector<Real>& points) {
  const auto size = points.size();
  using Size = decltype(triangulateio::numberofpoints);
  if (size > std::numeric_limits<Size>::max()) {
    // The number of points exceeds the limit of the triangle library.
    return false;
  } else if (size < 3) {
    // The provided parameter must have at least 3 points.
    return false;
  }
  // Prepare data
  result_ = std::make_shared<Result>();
  Result out;
  struct triangulateio in;
  std::memset(&in, 0, sizeof(in));
  std::vector<Real> mutable_points(points);
  in.pointlist = mutable_points.data();
  in.numberofpoints = size / 2;

  // Triangulation
  return Triangulator::operator()("vzQ", &in, &*out, &**result_);
}

#pragma mark Attributes

std::size_t VoronoiTriangulator::size() const {
  assert(result_);
  return (*result_)->numberofedges;
}

#pragma mark Iterators

EdgeIterator VoronoiTriangulator::begin() const {
  assert(result_);
  return EdgeIterator(result_);
}

EdgeIterator VoronoiTriangulator::end() const {
  assert(result_);
  const auto end = (*result_)->edgelist + (*result_)->numberofedges;
  return EdgeIterator(result_, end);
}

}  // namespace triangle
}  // namespace solas
