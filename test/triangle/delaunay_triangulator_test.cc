//
//  triangle/delaunay_triangulator_test.cc
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

#include <iterator>
#include <vector>

#include "gtest/gtest.h"

#include "solas/triangle/delaunay_triangulator.h"

namespace {

struct TestPoint {
  double x;
  double y;
};

}  // namespace

namespace solas {
namespace triangle {

TEST(DelaunayTriangulatorTest, Size) {
  DelaunayTriangulator triangulator;
  std::vector<TestPoint> points;
  points.emplace_back(TestPoint{1, 1});
  points.emplace_back(TestPoint{1, 2});
  points.emplace_back(TestPoint{2, 2});
  triangulator(points);
  ASSERT_EQ(triangulator.size(), 1);
  ASSERT_EQ(std::distance(triangulator.begin(), triangulator.end()), 1);
}

}  // namespace triangle
}  // namespace solas
