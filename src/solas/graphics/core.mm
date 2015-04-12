//
//  solas/graphics/core.mm
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

#include <cassert>
#include <tuple>

#include "solas/graphics/color.h"
#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/stroke.h"
#include "solas/math/line.h"
#include "solas/math/matrix.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSGraphicsContext.h"

namespace solas {
namespace graphics {
namespace core {

namespace {

inline CGLineCap ConvertStrokeCap(Stroke::Cap cap) {
  switch (cap) {
    case Stroke::Cap::SQUARE:
      return kCGLineCapButt;
    case Stroke::Cap::PROJECT:
      return kCGLineCapSquare;
    case Stroke::Cap::ROUND:
      return kCGLineCapRound;
      break;
    default:
      assert(false);
      break;
  }
  return kCGLineCapButt;
}

inline CGLineJoin ConvertStrokeJoin(Stroke::Join join) {
  switch (join) {
    case Stroke::Join::MITER:
      return kCGLineJoinMiter;
    case Stroke::Join::BEVEL:
      return kCGLineJoinBevel;
    case Stroke::Join::ROUND:
      return kCGLineJoinRound;
      break;
    default:
      assert(false);
      break;
  }
  return kCGLineJoinMiter;
}

}  // namespace

#pragma mark Drawing 2D primitives

void DrawPoint(const ContextHolder& holder,
               const Fill& fill,
               const Stroke& stroke,
               const math::Vector2<Real>& point) {
  auto context = holder.get<CGContextRef>();
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillEllipseInRect(context, CGRectMake(point.x, point.y, 1.0, 1.0));
  }
}

void DrawLine(const ContextHolder& holder,
              const Fill& fill,
              const Stroke& stroke,
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
    CGContextSetLineWidth(context, stroke.weight);
    CGContextSetLineCap(context, ConvertStrokeCap(stroke.cap));
    CGContextSetLineJoin(context, ConvertStrokeJoin(stroke.join));
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, line.x1, line.y1);
    CGContextAddLineToPoint(context, line.x2, line.y2);
    CGContextStrokePath(context);
  }
}

void DrawRect(const ContextHolder& holder,
              const Fill& fill,
              const Stroke& stroke,
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
    CGContextSetLineWidth(context, stroke.weight);
    CGContextSetLineCap(context, ConvertStrokeCap(stroke.cap));
    CGContextSetLineJoin(context, ConvertStrokeJoin(stroke.join));
    CGContextStrokeRect(context,
        CGRectMake(rect.x, rect.y, rect.width, rect.height));
  }
}

void DrawRoundedRect(const ContextHolder& holder,
                     const Fill& fill,
                     const Stroke& stroke,
                     const math::Rect<Real>& rect,
                     Real radius) {
}

void DrawRoundedRect(const ContextHolder& holder,
                     const Fill& fill,
                     const Stroke& stroke,
                     const math::Rect<Real>& rect,
                     const std::tuple<Real, Real, Real, Real>& radii) {
}

void DrawArc(const ContextHolder& holder,
             const Fill& fill,
             const Stroke& stroke,
             const math::Rect<Real>& rect,
             Real start_angle,
             Real stop_angle) {
}

void DrawEllipse(const ContextHolder& holder,
                 const Fill& fill,
                 const Stroke& stroke,
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
    CGContextSetLineWidth(context, stroke.weight);
    CGContextSetLineCap(context, ConvertStrokeCap(stroke.cap));
    CGContextSetLineJoin(context, ConvertStrokeJoin(stroke.join));
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

#pragma mark Transform

void SetMatrix(const ContextHolder& holder,
               const math::Matrix2<Real>& matrix) {
}

void ConcatMatrix(const ContextHolder& holder,
                  const math::Matrix2<Real>& matrix) {
  auto context = holder.get<CGContextRef>();
  CGContextConcatCTM(context, CGAffineTransformMake(
      matrix.m00, matrix.m01,
      matrix.m10, matrix.m11,
      matrix.m20, matrix.m21));
}

void PushMatrix(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextSaveGState(context);
}

void PopMatrix(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextRestoreGState(context);
}

void Translate(const ContextHolder& holder,
               const math::Vector2<Real>& vector) {
  auto context = holder.get<CGContextRef>();
  CGContextTranslateCTM(context, vector.x, vector.y);
}

void Scale(const ContextHolder& holder,
           const math::Vector2<Real>& vector) {
  auto context = holder.get<CGContextRef>();
  CGContextScaleCTM(context, vector.x, vector.y);
}

void Rotate(const ContextHolder& holder, Real angle) {
  auto context = holder.get<CGContextRef>();
  CGContextRotateCTM(context, angle);
}

}  // namespace core
}  // namespace graphics
}  // namespace solas
