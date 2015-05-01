//
//  solas/triangle/triangulator.h
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
#ifndef SOLAS_TRIANGLE_TRIANGULATOR_H_
#define SOLAS_TRIANGLE_TRIANGULATOR_H_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "solas/triangle/point.h"
#include "solas/triangle/result.h"
#include "solas/triangle/type.h"

struct triangulateio;

namespace solas {
namespace triangle {

class Triangulator {
 public:
  // Constructors
  Triangulator();
  virtual ~Triangulator() = 0;

  // Copy and assign
  Triangulator(const Triangulator& other) = default;
  Triangulator& operator=(const Triangulator& other) = default;

  // Triangulation
  template <typename Container>
  bool operator()(const Container& container);
  bool operator()(std::vector<Point>&& points);
  bool operator()(const std::vector<Point>& points);
  virtual bool operator()(const std::vector<Real>& coordinates) = 0;
  void clear();

  // Parameters
  Real min_angle() const;
  void set_min_angle(double value);
  Real max_area() const;
  void set_max_area(double value);
  int max_steiner_points() const;
  void set_max_steiner_points(int value);

  // Attributes
  bool empty() const { return !result_; }
  virtual std::size_t size() const = 0;

 protected:
  // Triangulation
  bool operator()(const std::string& options,
                  struct triangulateio *in,
                  struct triangulateio *out,
                  struct triangulateio *voronoi);

 protected:
  std::shared_ptr<Result> result_;

 private:
  // Parameters
  Real min_angle_;
  Real max_area_;
  int max_steiner_points_;
};

#pragma mark -

inline Triangulator::Triangulator()
    : min_angle_(std::numeric_limits<double>::quiet_NaN()),
      max_area_(std::numeric_limits<double>::quiet_NaN()),
      max_steiner_points_(-1) {}

inline Triangulator::~Triangulator() {}

#pragma mark Triangulation

template <typename Container>
inline bool Triangulator::operator()(const Container& container) {
  std::vector<Point> points(container.size());
  std::copy(container.begin(), container.end(), points.begin());
  return operator()(std::move(points));
}

inline bool Triangulator::operator()(std::vector<Point>&& points) {
  auto index = std::size_t();
  for (auto& point : points) {
    point.index = index++;
  }
  return operator()(points);
}

inline void Triangulator::clear() {
  result_.reset<Result>(nullptr);
}

#pragma mark Parameters

inline Real Triangulator::min_angle() const {
  return min_angle_;
}

inline void Triangulator::set_min_angle(Real value) {
  min_angle_ = value;
}

inline Real Triangulator::max_area() const {
  return max_area_;
}

inline void Triangulator::set_max_area(Real value) {
  max_area_ = value;
}

inline int Triangulator::max_steiner_points() const {
  return max_steiner_points_;
}

inline void Triangulator::set_max_steiner_points(int value) {
  max_steiner_points_ = value;
}

}  // namespace triangle

using triangle::Triangulator;

}  // namespace solas

#endif  // SOLAS_TRIANGLE_TRIANGULATOR_H_
