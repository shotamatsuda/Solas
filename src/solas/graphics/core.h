//
//  solas/graphics/core.h
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
#ifndef SOLAS_GRAPHICS_CORE_H_
#define SOLAS_GRAPHICS_CORE_H_

#include <tuple>

#include "solas/graphics/color.h"
#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/path.h"
#include "solas/graphics/stroke.h"
#include "solas/math/line.h"
#include "solas/math/matrix.h"
#include "solas/math/rect.h"
#include "solas/math/vector.h"

namespace solas {
namespace graphics {
namespace core {

using Real = double;

// Drawing 2D primitives
void DrawPoint(const ContextHolder& holder,
               const Fill& fill,
               const Stroke& stroke,
               const math::Vec2<Real>& point);
void DrawLine(const ContextHolder& holder,
              const Fill& fill,
              const Stroke& stroke,
              const math::Line2<Real>& line);
void DrawRect(const ContextHolder& holder,
              const Fill& fill,
              const Stroke& stroke,
              const math::Rect<Real>& rect);
void DrawRoundedRect(const ContextHolder& holder,
                     const Fill& fill,
                     const Stroke& stroke,
                     const math::Rect<Real>& rect,
                     Real radius);
void DrawRoundedRect(const ContextHolder& holder,
                     const Fill& fill,
                     const Stroke& stroke,
                     const math::Rect<Real>& rect,
                     const std::tuple<Real, Real, Real, Real>& radii);
void DrawArc(const ContextHolder& holder,
             const Fill& fill,
             const Stroke& stroke,
             const math::Rect<Real>& rect,
             Real start_angle,
             Real stop_angle);
void DrawEllipse(const ContextHolder& holder,
                 const Fill& fill,
                 const Stroke& stroke,
                 const math::Rect<Real>& rect);
void DrawPath(const ContextHolder& holder,
              const Fill& fill,
              const Stroke& stroke,
              const Path& path);

// Clearing the buffer
void Clear(const ContextHolder& holder);
void Clear(const ContextHolder& holder, const Color4<Real>& color);

// Configuring antialias
void EnableAntialias(const ContextHolder& holder);
void DisableAntialias(const ContextHolder& holder);

// Transform
void SetMatrix(const ContextHolder& holder,
               const math::Matrix2<Real>& matrix);
void ConcatMatrix(const ContextHolder& holder,
                  const math::Matrix2<Real>& matrix);
void PushMatrix(const ContextHolder& holder);
void PopMatrix(const ContextHolder& holder);
void Translate(const ContextHolder& holder,
               const math::Vec2<Real>& vector);
void Scale(const ContextHolder& holder,
           const math::Vec2<Real>& vector);
void Rotate(const ContextHolder& holder, Real angle);

}  // namespace core
}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_CORE_H_
