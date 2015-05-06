//
//  solas/nanovg/path.cc
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

#include "solas/nanovg/path.h"

#include "solas/graphics/path.h"

namespace solas {
namespace nanovg {

void Path(const graphics::Path& path) {
  for (const auto& segment : path) {
    switch (segment.type()) {
      case solas::gfx::Segment::Type::MOVE:
        MoveTo(segment.point());
        break;
      case solas::gfx::Segment::Type::LINE:
        LineTo(segment.point());
        break;
      case solas::gfx::Segment::Type::QUADRATIC:
        QuadTo(segment.control(), segment.point());
        break;
      case solas::gfx::Segment::Type::CUBIC:
        CubicTo(segment.control1(), segment.control2(), segment.point());
        break;
      case solas::gfx::Segment::Type::CLOSE:
        ClosePath();
        break;
    }
  }
}

}  // namespace nanovg
}  // namespace solas
