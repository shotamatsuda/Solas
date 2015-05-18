//
//  solas/graphics/contour.cc
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//  Copyright (C) 2015 takram design engineering
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

#include "solas/graphics/contour.h"

#include <algorithm>
#include <iterator>
#include <limits>
#include <list>

#include "SkGeometry.h"
#include "SkPath.h"
#include "SkPoint.h"

#include "solas/graphics/segment.h"
#include "solas/math/rect.h"

namespace solas {
namespace graphics {

namespace {

static void AddConicAsQuads(const std::vector<SkPoint>& points,
                            float weight,
                            float tolerance,
                            Contour *contour) {
  assert(contour);
  if (!tolerance) {
    const int pow2 = 1;
    const int quad_count = 1 << pow2;
    const int point_count = 1 + 2 * quad_count;
    std::vector<SkPoint> quads(point_count);
    const SkConic conic(points.data(), weight);
    conic.chopIntoQuadsPOW2(quads.data(), pow2);
    for (auto itr = quads.begin() + 1; itr != quads.end(); itr += 2) {
      contour->quadraticTo(*itr, *(itr + 1));
    }
  } else {
    SkAutoConicToQuads converter;
    const auto quads = converter.computeQuads(points.data(), weight, tolerance);
    const auto end = quads + converter.countQuads() * 2 + 1;
    for (auto itr = quads + 1; itr != end; itr += 2) {
      contour->quadraticTo(*itr, *(itr + 1));
    }
  }
}

}  // namespace

#pragma mark Mutators

void Contour::set(const SkPath& path) {
  reset();
  SkPath::RawIter itr(path);
  SkPath::Verb verb;
  std::vector<SkPoint> points(4);
  while ((verb = itr.next(points.data())) != SkPath::kDone_Verb) {
    switch (verb) {
      case SkPath::Verb::kMove_Verb:
        moveTo(points[0]);
        break;
      case SkPath::Verb::kLine_Verb:
        lineTo(points[1]);
        break;
      case SkPath::Verb::kQuad_Verb:
        quadraticTo(points[1], points[2]);
        break;
      case SkPath::Verb::kConic_Verb:
        AddConicAsQuads(points, itr.conicWeight(), 0.0, this);
        break;
      case SkPath::Verb::kCubic_Verb:
        cubicTo(points[1], points[2], points[3]);
        break;
      case SkPath::Verb::kClose_Verb:
        close();
        break;
      default:
        assert(false);
        break;
    }
  }
}

#pragma mark Attributes

math::Rect<Contour::Real> Contour::bounds() const {
  Real min_x = std::numeric_limits<Real>::max();
  Real min_y = std::numeric_limits<Real>::max();
  Real max_x = std::numeric_limits<Real>::lowest();
  Real max_y = std::numeric_limits<Real>::lowest();
  for (const auto& segment : *this) {
    switch (segment.type()) {
      case Segment::Type::CUBIC:
        if (segment.control2().x < min_x) {
          min_x = segment.control2().x;
        }
        if (segment.control2().y < min_y) {
          min_y = segment.control2().y;
        }
        if (segment.control2().x > max_x) {
          max_x = segment.control2().x;
        }
        if (segment.control2().y > max_y) {
          max_y = segment.control2().y;
        }
        // Pass through
      case Segment::Type::QUADRATIC:
        if (segment.control1().x < min_x) {
          min_x = segment.control1().x;
        }
        if (segment.control1().y < min_y) {
          min_y = segment.control1().y;
        }
        if (segment.control1().x > max_x) {
          max_x = segment.control1().x;
        }
        if (segment.control1().y > max_y) {
          max_y = segment.control1().y;
        }
        // Pass through
      case Segment::Type::MOVE:
      case Segment::Type::LINE:
        if (segment.point().x < min_x) {
          min_x = segment.point().x;
        }
        if (segment.point().y < min_y) {
          min_y = segment.point().y;
        }
        if (segment.point().x > max_x) {
          max_x = segment.point().x;
        }
        if (segment.point().y > max_y) {
          max_y = segment.point().y;
        }
        break;
      default:
        break;
    }
  }
  if (min_x == std::numeric_limits<Real>::max()) {
    min_x = Real();
  }
  if (min_y == std::numeric_limits<Real>::max()) {
    min_y = Real();
  }
  if (max_x == std::numeric_limits<Real>::lowest()) {
    max_x = Real();
  }
  if (max_y == std::numeric_limits<Real>::lowest()) {
    max_y = Real();
  }
  return math::Rect<Real>(Point(min_x, min_y), Point(max_x, max_y));
}

#pragma mark Implicit conversion

Contour::operator SkPath() const {
  SkPath path;
  for (const auto& segment : *this) {
    switch (segment.type()) {
      case Segment::Type::MOVE:
        path.moveTo(segment.point());
        break;
      case Segment::Type::LINE:
        path.lineTo(segment.point());
        break;
      case Segment::Type::QUADRATIC:
        path.quadTo(segment.control(), segment.point());
        break;
      case Segment::Type::CUBIC:
        path.cubicTo(segment.control1(), segment.control2(), segment.point());
        break;
      case Segment::Type::CLOSE:
        path.close();
        break;
      default:
        assert(false);
        break;
    }
  }
  return std::move(path);
}

#pragma mark Direction

Contour::Direction Contour::direction() const {
  if (segments_.size() < 3) {
    return Direction::UNDEFINED;
  }
  Real sum{};
  auto first = segments_.begin();
  auto second = std::next(first);
  for (; second != segments_.end(); ++first, ++second) {
    switch (second->type()) {
      case Segment::Type::LINE:
      case Segment::Type::QUADRATIC:
      case Segment::Type::CUBIC:
        sum += first->point().cross(second->point());
        break;
      case Segment::Type::CLOSE:
        sum += second->point().cross(segments_.front().point());
        break;
      default:
        assert(false);
        break;
    }
  }
  return sum < 0.0 ? Direction::COUNTER_CLOCKWISE : Direction::CLOCKWISE;
}

Contour& Contour::reverse() {
  std::list<Point> points;
  for (auto& segment : segments_) {
    switch (segment.type()) {
      case Segment::Type::MOVE:
      case Segment::Type::LINE:
        points.emplace_back(segment.point());
        break;
      case Segment::Type::QUADRATIC:
        points.emplace_back(segment.control1());
        points.emplace_back(segment.point());
        break;
      case Segment::Type::CUBIC:
        points.emplace_back(segment.control1());
        points.emplace_back(segment.control2());
        points.emplace_back(segment.point());
        break;
      default:
        break;
    }
  }
  if (segments_.back().type() == Segment::Type::CLOSE) {
    std::reverse(std::next(segments_.begin()), std::prev(segments_.end()));
  } else {
    std::reverse(std::next(segments_.begin()), segments_.end());
  }
  std::reverse(points.begin(), points.end());
  auto itr = points.begin();
  for (auto& segment : segments_) {
    switch (segment.type()) {
      case Segment::Type::MOVE:
      case Segment::Type::LINE:
        segment.point() = *(itr++);
        break;
      case Segment::Type::QUADRATIC:
        segment.control1() = *(itr++);
        segment.point() = *(itr++);
        break;
      case Segment::Type::CUBIC:
        segment.control1() = *(itr++);
        segment.control2() = *(itr++);
        segment.point() = *(itr++);
        break;
      default:
        break;
    }
  }
  assert(itr == points.end());
  return *this;
}

}  // namespace graphics
}  // namespace solas
