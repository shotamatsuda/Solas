//
//  solas/triangle/triangulator.cc
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

#include "solas/triangle/triangulator.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include "solas/triangle/lib.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

namespace {

using PointRef = std::reference_wrapper<const Point>;

inline bool IdentifyVector(const PointRef& a, const PointRef& b) {
  return a.get().vector == b.get().vector;
}

inline bool CompareVector(const PointRef& a, const PointRef& b) {
  return a.get().vector < b.get().vector;
}

inline bool CompareIndex(const PointRef& a, const PointRef& b) {
  return a.get().index < b.get().index;
}

}  // namespace

#pragma mark Triangulation

bool Triangulator::operator()(const std::vector<Point>& points) {
  // Sort and unique will remove lots of points we don't need
  std::vector<PointRef> refs(points.begin(), points.end());
  std::sort(refs.begin(), refs.end(), CompareVector);
  refs.erase(std::unique(refs.begin(), refs.end(), IdentifyVector), refs.end());

  // Sort again, now on their indexes
  std::sort(refs.begin(), refs.end(), CompareIndex);
  std::vector<Real> coordinates;
  for (const auto& ref : refs) {
    coordinates.emplace_back(ref.get().x);
    coordinates.emplace_back(ref.get().y);
  }
  return operator()(coordinates);
}

bool Triangulator::operator()(const std::string& options,
                              struct triangulateio *in,
                              struct triangulateio *out,
                              struct triangulateio *voronoi) {
  std::string parameters;
  if (!std::isnan(min_angle_)) {
    parameters += "q" + std::to_string(min_angle_);
  }
  if (!std::isnan(max_area_)) {
    parameters += "a" + std::to_string(max_area_);
  }
  if (max_steiner_points_ >= 0) {
    parameters += "S" + std::to_string(max_steiner_points_);
  }
  std::vector<char> switches(options.begin(), options.end());
  switches.insert(switches.end(), parameters.begin(), parameters.end());
  switches.emplace_back('\0');
  ::triangulate(switches.data(), in, out, voronoi);
  return true;
}

}  // namespace triangle
}  // namespace solas
