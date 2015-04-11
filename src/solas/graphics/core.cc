//
//  solas/graphics/core.cc
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

#include "solas/graphics/core.h"

#include <CoreGraphics/CoreGraphics.h>

#include <tuple>

#include "solas/graphics/color.h"
#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/stroke.h"
#include "solas/math/line.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

namespace solas {
namespace graphics {
namespace core {

#pragma mark Drawing 2D primitives

void DrawPoint(const ContextHolder& holder,
               const Fill<Real>& fill,
               const Stroke<Real>& stroke,
               const math::Vec2<Real>& point) {
  auto context = holder.get<CGContextRef>();
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillEllipseInRect(context, CGRectMake(point.x, point.y, 1.0, 1.0));
  }
}

void DrawLine(const ContextHolder& holder,
              const Fill<Real>& fill,
              const Stroke<Real>& stroke,
              const math::Line2<Real>& line) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, line.x1, line.y1);
    CGContextAddLineToPoint(context, line.x2, line.y2);
    CGContextFillPath(context);
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, line.x1, line.y1);
    CGContextAddLineToPoint(context, line.x2, line.y2);
    CGContextStrokePath(context);
  }
}

void DrawRect(const ContextHolder& holder,
              const Fill<Real>& fill,
              const Stroke<Real>& stroke,
              const math::Rect<Real>& rect) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillRect(context,
        CGRectMake(rect.x, rect.y, rect.width, rect.height));
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextStrokeRect(context,
        CGRectMake(rect.x, rect.y, rect.width, rect.height));
  }
}

void DrawRoundedRect(const ContextHolder& holder,
                     const Fill<Real>& fill,
                     const Stroke<Real>& stroke,
                     const math::Rect<Real>& rect,
                     Real radius) {
}

void DrawRoundedRect(const ContextHolder& holder,
                     const Fill<Real>& fill,
                     const Stroke<Real>& stroke,
                     const math::Rect<Real>& rect,
                     const std::tuple<Real, Real, Real, Real>& radii) {
}

void DrawArc(const ContextHolder& holder,
             const Fill<Real>& fill,
             const Stroke<Real>& stroke,
             const math::Rect<Real>& rect,
             Real start_angle,
             Real stop_angle) {
}

void DrawEllipse(const ContextHolder& holder,
                 const Fill<Real>& fill,
                 const Stroke<Real>& stroke,
                 const math::Rect<Real>& rect) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillEllipseInRect(context,
        CGRectMake(rect.x, rect.y, rect.width, rect.height));
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextStrokeEllipseInRect(context,
        CGRectMake(rect.x, rect.y, rect.width, rect.height));
  }
}

#pragma mark Clearing the buffer

void Clear(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextClearRect(context, CGRectInfinite);
}

void Clear(const ContextHolder& holder, const Color4<Real>& color) {
  auto context = holder.get<CGContextRef>();
  CGContextClearRect(context, CGRectInfinite);
  CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
  CGContextFillRect(context, CGRectInfinite);
}

#pragma mark Configuring antialias

void EnableAntialias(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextSetShouldAntialias(context, true);
}

void DisableAntialias(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextSetShouldAntialias(context, false);
}

}  // namespace core
}  // namespace graphics
}  // namespace solas
