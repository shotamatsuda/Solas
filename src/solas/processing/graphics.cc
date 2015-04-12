//
//  solas/processing/graphics.cc
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

#include "solas/processing/graphics.h"

#include <algorithm>
#include <cassert>
#include <tuple>

#include "solas/graphics/core.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"
#include "solas/processing/constants.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

namespace {

inline Real4 CanonicalizeArgs(Real a, Real b, Real c, Real d, Constant mode) {
  switch (mode) {
    case CENTER:
      return std::make_tuple(a - c / 2, b - d / 2, c, d);
    case RADIUS:
      return std::make_tuple(a - c, b - d, c * 2, d * 2);
    case CORNER:
      return std::make_tuple(a, b, c, d);
    case CORNERS: {
      const auto x = std::min(a, c);
      const auto y = std::min(b, d);
      return std::make_tuple(x, y, std::max(a, c) - x, std::max(b, d) - y);
    }
    default:
      assert(false);
      break;
  }
  return std::make_tuple(a, b, c, d);
}

}  // namespace

#pragma mark Point and lines

void Graphics::point(Real x, Real y) const {
  const Vec2 point(x, y);
  graphics::core::DrawPoint(context(), fill(), stroke(), point);
}

void Graphics::line(Real x1, Real y1, Real x2, Real y2) const {
  const math::Line2<Real> line(x1, y1, x2, y2);
  graphics::core::DrawLine(context(), fill(), stroke(), line);
}

void Graphics::triangle(Real x1, Real y1,
                        Real x2, Real y2,
                        Real x3, Real y3) const {
}

void Graphics::quad(Real x1, Real y1, Real x2, Real y2,
                    Real x3, Real y3, Real x4, Real y4) const {
}

#pragma mark Rect

void Graphics::rect(Real a, Real b, Real c, Real d, Constant mode) const {
  math::Rect<Real> rect;
  std::tie(rect.x, rect.y, rect.w, rect.h) = CanonicalizeArgs(a, b, c, d, mode);
  graphics::core::DrawRect(context(), fill(), stroke(), rect);
}

#pragma mark Rounded rect

void Graphics::rect(Real a, Real b, Real c, Real d, Real radius,
                    Constant mode) const {
  math::Rect<Real> rect;
  std::tie(rect.x, rect.y, rect.w, rect.h) = CanonicalizeArgs(a, b, c, d, mode);
  graphics::core::DrawRoundedRect(context(), fill(), stroke(), rect, radius);
}

#pragma mark Rounded rect with separated radii

void Graphics::rect(Real a, Real b, Real c, Real d,
                    Real tl, Real tr, Real br, Real bl,
                    Constant mode) const {
  math::Rect<Real> rect;
  std::tie(rect.x, rect.y, rect.w, rect.h) = CanonicalizeArgs(a, b, c, d, mode);
  const auto radii = std::make_tuple(tl, tr, br, bl);
  graphics::core::DrawRoundedRect(context(), fill(), stroke(), rect, radii);
}

#pragma mark Arc

void Graphics::arc(Real a, Real b, Real c, Real d,
                   Real start, Real stop, Constant mode) const {
  math::Rect<Real> rect;
  std::tie(rect.x, rect.y, rect.w, rect.h) = CanonicalizeArgs(a, b, c, d, mode);
  graphics::core::DrawArc(context(), fill(), stroke(), rect, start, stop);
}

#pragma mark Ellipse

void Graphics::ellipse(Real a, Real b, Real c, Real d, Constant mode) const {
  math::Rect<Real> rect;
  std::tie(rect.x, rect.y, rect.w, rect.h) = CanonicalizeArgs(a, b, c, d, mode);
  graphics::core::DrawEllipse(context(), fill(), stroke(), rect);
}

#pragma mark Shape attributes

void Graphics::smooth() {
  graphics::core::EnableAntialias(context());
}

void Graphics::noSmooth() {
  graphics::core::DisableAntialias(context());
}

#pragma mark Transform

void Graphics::pushMatrix() {
  graphics::core::PushMatrix(context());
}

void Graphics::popMatrix() {
  graphics::core::PopMatrix(context());
}

void Graphics::translate(Real x, Real y, Real z) {
  graphics::core::Translate(context(), Vec2(x, y));
}

void Graphics::scale(Real x, Real y, Real z) {
  graphics::core::Scale(context(), Vec2(x, y));
}

void Graphics::rotate(Real angle) {
  graphics::core::Rotate(context(), angle);
}

#pragma mark Color settings

void Graphics::background(const Color& color) const {
  graphics::core::Clear(context(), color);
}

void Graphics::clear() const {
  graphics::core::Clear(context());
}

}  // namespace processing
}  // namespace solas
