//
//  solas/graphics/core_graphics_renderer.h
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

#pragma once
#ifndef SOLAS_GRAPHICS_CORE_GRAPHICS_RENDERER_H_
#define SOLAS_GRAPHICS_CORE_GRAPHICS_RENDERER_H_

#include "solas/graphics/color.h"
#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/renderer.h"
#include "solas/graphics/stroke.h"

struct CGContext;

namespace solas {
namespace graphics {

class CoreGraphicsRenderer : public Renderer<double> {
 public:
  // Drawing 2D primitives
  void drawPoint(const ContextHolder& holder,
                 const Fill& fill,
                 const Stroke& stroke,
                 Real x, Real y) override;
  void drawLine(const ContextHolder& holder,
                const Fill& fill,
                const Stroke& stroke,
                Real x1, Real y1, Real x2, Real y2) override;
  void drawTriangle(const ContextHolder& holder,
                    const Fill& fill,
                    const Stroke& stroke,
                    Real x1, Real y1,
                    Real x2, Real y2,
                    Real x3, Real y3) override;
  void drawQuad(const ContextHolder& holder,
                const Fill& fill,
                const Stroke& stroke,
                Real x1, Real y1, Real x2, Real y2,
                Real x3, Real y3, Real x4, Real y4) override;
  void drawRect(const ContextHolder& holder,
                const Fill& fill,
                const Stroke& stroke,
                Real x, Real y, Real width, Real height) override;
  void drawRoundedRect(const ContextHolder& holder,
                       const Fill& fill,
                       const Stroke& stroke,
                       Real x, Real y, Real width, Real height,
                       Real radius) override;
  void drawRoundedRect(const ContextHolder& holder,
                       const Fill& fill,
                       const Stroke& stroke,
                       Real x, Real y, Real width, Real height,
                       Real top_left, Real top_right,
                       Real bottom_right, Real bottom_left) override;
  void drawArc(const ContextHolder& holder,
               const Fill& fill,
               const Stroke& stroke,
               Real x, Real y, Real width, Real height,
               Real start_angle, Real stop_angle) override;
  void drawEllipse(const ContextHolder& holder,
                   const Fill& fill,
                   const Stroke& stroke,
                   Real x, Real y, Real width, Real height) override;

  // Clearing the buffer
  void clearBuffer(const ContextHolder& holder) override;
  void clearBuffer(const ContextHolder& holder, const Color4d& color) override;

  // Controlling antialias
  void enableAntialias(const ContextHolder& holder) override;
  void disableAntialias(const ContextHolder& holder) override;
};

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_CORE_GRAPHICS_RENDERER_H_
