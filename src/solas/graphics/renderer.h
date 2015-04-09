//
//  solas/graphics/renderer.h
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
#ifndef SOLAS_GRAPHICS_RENDERER_H_
#define SOLAS_GRAPHICS_RENDERER_H_

#include "solas/graphics/color.h"
#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/stroke.h"

namespace solas {
namespace graphics {

template <typename T = double>
class Renderer {
 public:
  using Real = T;
  using Fill = Fill<Real>;
  using Stroke = Stroke<Real>;

 public:
  // Constructors
  virtual ~Renderer() = 0;

  // Drawing 2D primitives
  virtual void drawPoint(const ContextHolder& holder,
                         const Fill& fill,
                         const Stroke& stroke,
                         Real x, Real y) {}
  virtual void drawLine(const ContextHolder& holder,
                        const Fill& fill,
                        const Stroke& stroke,
                        Real x1, Real y1, Real x2, Real y2) {}
  virtual void drawTriangle(const ContextHolder& holder,
                            const Fill& fill,
                            const Stroke& stroke,
                            Real x1, Real y1,
                            Real x2, Real y2,
                            Real x3, Real y3) {}
  virtual void drawQuad(const ContextHolder& holder,
                        const Fill& fill,
                        const Stroke& stroke,
                        Real x1, Real y1, Real x2, Real y2,
                        Real x3, Real y3, Real x4, Real y4) {}
  virtual void drawRect(const ContextHolder& holder,
                        const Fill& fill,
                        const Stroke& stroke,
                        Real x, Real y, Real width, Real height) {}
  virtual void drawRoundedRect(const ContextHolder& holder,
                               const Fill& fill,
                               const Stroke& stroke,
                               Real x, Real y, Real width, Real height,
                               Real radius) {}
  virtual void drawRoundedRect(const ContextHolder& holder,
                               const Fill& fill,
                               const Stroke& stroke,
                               Real x, Real y, Real width, Real height,
                               Real top_left, Real top_right,
                               Real bottom_right, Real bottom_left) {}
  virtual void drawArc(const ContextHolder& holder,
                       const Fill& fill,
                       const Stroke& stroke,
                       Real x, Real y, Real width, Real height,
                       Real start_angle, Real stop_angle) {}
  virtual void drawEllipse(const ContextHolder& holder,
                           const Fill& fill,
                           const Stroke& stroke,
                           Real x, Real y, Real width, Real height) {}

  // Clearing the buffer
  virtual void clearBuffer(const ContextHolder& holder) {}
  virtual void clearBuffer(const ContextHolder& holder,
                           const Color4<Real>& color) {}

  // Controlling antialias
  virtual void enableAntialias(const ContextHolder& holder) {}
  virtual void disableAntialias(const ContextHolder& holder) {}
};

#pragma mark -

template <typename T>
inline Renderer<T>::~Renderer() {}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_RENDERER_H_
