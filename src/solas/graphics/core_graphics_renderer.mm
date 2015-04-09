//
//  solas/graphics/core_graphics_renderer.mm
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

#include "solas/graphics/core_graphics_renderer.h"

#include <CoreGraphics/CoreGraphics.h>

#include "solas/graphics/context_holder.h"

namespace solas {
namespace graphics {

#pragma mark Drawing 2D primitives

void CoreGraphicsRenderer::drawPoint(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y) {
  auto context = holder.get<CGContextRef>();
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillEllipseInRect(context, CGRectMake(x, y, 1.0, 1.0));
  }
}

void CoreGraphicsRenderer::drawLine(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x1, Real y1, Real x2, Real y2) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextFillPath(context);
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextStrokePath(context);
  }
}

void CoreGraphicsRenderer::drawTriangle(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x1, Real y1, Real x2, Real y2, Real x3, Real y3) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextAddLineToPoint(context, x3, y3);
    CGContextClosePath(context);
    CGContextFillPath(context);
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextAddLineToPoint(context, x3, y3);
    CGContextClosePath(context);
    CGContextStrokePath(context);
  }
}

void CoreGraphicsRenderer::drawQuad(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x1, Real y1, Real x2, Real y2, Real x3, Real y3, Real x4, Real y4) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextAddLineToPoint(context, x3, y3);
    CGContextAddLineToPoint(context, x4, y4);
    CGContextClosePath(context);
    CGContextFillPath(context);
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, x1, y1);
    CGContextAddLineToPoint(context, x2, y2);
    CGContextAddLineToPoint(context, x3, y3);
    CGContextAddLineToPoint(context, x4, y4);
    CGContextClosePath(context);
    CGContextStrokePath(context);
  }
}

void CoreGraphicsRenderer::drawRect(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y, Real width, Real height) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillRect(context, CGRectMake(x, y, width, height));
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextStrokeRect(context, CGRectMake(x, y, width, height));
  }
}

void CoreGraphicsRenderer::drawRoundedRect(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y, Real width, Real height, Real radius) {
}

void CoreGraphicsRenderer::drawRoundedRect(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y, Real width, Real height,
    Real top_left, Real top_right, Real bottom_right, Real bottom_left) {
}

void CoreGraphicsRenderer::drawArc(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y, Real width, Real height,
    Real start_angle, Real stop_angle) {
}

void CoreGraphicsRenderer::drawEllipse(
    const ContextHolder& holder,
    const Fill& fill,
    const Stroke& stroke,
    Real x, Real y, Real width, Real height) {
  auto context = holder.get<CGContextRef>();
  if (fill) {
    const auto& color = fill.color;
    CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
    CGContextFillEllipseInRect(context, CGRectMake(x, y, width, height));
  }
  if (stroke) {
    const auto& color = stroke.color;
    CGContextSetRGBStrokeColor(context, color.r, color.g, color.b, color.a);
    CGContextStrokeEllipseInRect(context, CGRectMake(x, y, width, height));
  }
}

#pragma mark Clearing the buffer

void CoreGraphicsRenderer::clearBuffer(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextClearRect(context, CGRectInfinite);
}

void CoreGraphicsRenderer::clearBuffer(const ContextHolder& holder,
                                       const Color4<Real>& color) {
  auto context = holder.get<CGContextRef>();
  CGContextClearRect(context, CGRectInfinite);
  CGContextSetRGBFillColor(context, color.r, color.g, color.b, color.a);
  CGContextFillRect(context, CGRectInfinite);
}

#pragma mark Controlling antialias

void CoreGraphicsRenderer::enableAntialias(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextSetShouldAntialias(context, true);
}

void CoreGraphicsRenderer::disableAntialias(const ContextHolder& holder) {
  auto context = holder.get<CGContextRef>();
  CGContextSetShouldAntialias(context, false);
}

}  // namespace graphics
}  // namespace solas
