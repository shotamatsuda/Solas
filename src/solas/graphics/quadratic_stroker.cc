//
//  solas/graphics/quadratic_stroker.cc
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

#include "solas/graphics/quadratic_stroker.h"

#include <cassert>

#include "SkPaint.h"
#include "SkPath.h"
#include "SkPathOps.h"

#include "solas/graphics/path.h"
#include "solas/graphics/stroke.h"

namespace solas {
namespace graphics {

namespace {

inline SkPaint::Cap PaintCap(Stroke::Cap cap) {
  switch (cap) {
    case Stroke::Cap::BUTT:
      return SkPaint::Cap::kButt_Cap;
    case Stroke::Cap::ROUND:
      return SkPaint::Cap::kRound_Cap;
    case Stroke::Cap::PROJECT:
      return SkPaint::Cap::kSquare_Cap;
    default:
      assert(false);
      break;
  }
  return SkPaint::Cap::kDefault_Cap;
}

inline SkPaint::Join PaintJoin(Stroke::Join join) {
  switch (join) {
    case Stroke::Join::MITER:
      return SkPaint::Join::kMiter_Join;
    case Stroke::Join::ROUND:
      return SkPaint::Join::kRound_Join;
    case Stroke::Join::BEVEL:
      return SkPaint::Join::kBevel_Join;
    default:
      assert(false);
      break;
  }
  return SkPaint::Join::kDefault_Join;
}

static void FixDirection(SkPath *stroke) {
  using Direction = Contour::Direction;
  assert(stroke);
  Path path(*stroke);
  if (path.size() == 1) {
    return;  // Nothing to fix
  }
  stroke->rewind();
  math::Rect<Path::Real> max_bounds;
  auto& contours = path.contours();
  auto max_itr = contours.begin();
  for (auto itr = contours.begin(); itr != contours.end(); ++itr) {
    const auto& bounds = itr->bounds();
    if (bounds.area() > max_bounds.area()) {
      max_bounds = bounds;
      max_itr = itr;
    }
  }
  for (auto itr = contours.begin(); itr != contours.end(); ++itr) {
    if (itr != max_itr && itr->direction() != Direction::COUNTER_CLOCKWISE) {
      itr->reverse();
    }
  }
  *stroke = path;
}

}  // namespace

Path QuadraticStroker::operator()(const Path& path) const {
  SkPaint paint;
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(width_);
  paint.setStrokeMiter(miter_);
  paint.setStrokeCap(PaintCap(cap_));
  paint.setStrokeJoin(PaintJoin(join_));
  SkPath result;
  SkPath stroke;
  for (const auto& contour : path.contours()) {
    stroke.rewind();
    paint.getFillPath(contour, &stroke, nullptr, tolerance_);
    Simplify(stroke, &stroke);
    FixDirection(&stroke);
    result.addPath(stroke);
  }
  return result;
}

}  // namespace graphics
}  // namespace solas
