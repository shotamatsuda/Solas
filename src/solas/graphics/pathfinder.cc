//
//  solas/graphics/pathfinder.cc
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

#define SK_RELEASE

#include "solas/graphics/pathfinder.h"

#include "SkPath.h"
#include "SkPathOps.h"

namespace solas {
namespace graphics {

Path Simplify(const Path& path) {
  SkPath result;
  Simplify(path, &result);
  SkPath difference = result;
  difference.setFillType(SkPath::FillType::kWinding_FillType);
  Op(difference, result, SkPathOp::kDifference_SkPathOp, &difference);
  Path result_path = result;
  Path difference_path = difference;
  for (auto& result_contour : result_path.contours()) {
    for (auto& difference_contour : difference_path.contours()) {
      if (result_contour.bounds() == difference_contour.bounds()) {
        difference_contour.reverse();
      }
    }
  }
  return result_path;
}

}  // namespace graphics
}  // namespace solas
