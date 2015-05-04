//
//  solas/graphics/path.cc
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

#include "solas/graphics/path.h"

#include <cassert>
#include <functional>
#include <utility>
#include <vector>

#include "SkGeometry.h"
#include "SkPath.h"
#include "SkPoint.h"

#include "solas/graphics/segment.h"

namespace solas {
namespace graphics {

namespace {

static void AddConicAsQuads(const std::vector<SkPoint>& points,
                            float weight,
                            Path *path) {
  assert(path);
  const int pow2 = 1;
  const int quad_count = 1 << pow2;
  const int point_count = 1 + 2 * quad_count;
  std::vector<SkPoint> quads(point_count);
  const SkConic conic(points.data(), weight);
  conic.chopIntoQuadsPOW2(quads.data(), pow2);
  for (auto itr = quads.begin() + 1; itr != quads.end(); itr += 2) {
    path->quadraticTo(*itr, *(itr + 1));
  }
}

static void AddConicAsQuads(const std::vector<SkPoint>& points,
                            float weight,
                            float tolerance,
                            Path *path) {
  assert(path);
  SkAutoConicToQuads converter;
  const auto quads = converter.computeQuads(points.data(), weight, tolerance);
  const auto end = quads + converter.countQuads() * 2 + 1;
  for (auto itr = quads + 1; itr != end; itr += 2) {
    path->quadraticTo(*itr, *(itr + 1));
  }
}

}  // namespace

#pragma mark Mutators

void Path::set(const SkPath& path) {
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
        AddConicAsQuads(points, itr.conicWeight(), this);
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

#pragma mark Reversing

Path& Path::reverse() {
  return *this;
}

#pragma mark Implicit conversion

Path::operator SkPath() const {
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

}  // namespace graphics
}  // namespace solas
