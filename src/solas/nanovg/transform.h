//
//  solas/nanovg/transform.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
#ifndef SOLAS_NANOVG_TRANSFORM_H_
#define SOLAS_NANOVG_TRANSFORM_H_

#include "nanovg.h"

#include "solas/math/vector.h"
#include "solas/nanovg/context.h"

namespace solas {
namespace nanovg {

void translateX(float dx);
void translateY(float dy);
void translate(float value);
void translate(float dx, float dy);
void translate(const math::Vec2f& value);
void rotate(float angle);
void rotate(float angle, const math::Vec2f& point);
void scaleX(float sx);
void scaleY(float sy);
void scale(float value);
void scale(float sx, float sy);
void scale(const math::Vec2f& value);
void skewX(float angle);
void skewY(float angle);

void translateX(NVGcontext *context, float dx);
void translateY(NVGcontext *context, float dy);
void translate(NVGcontext *context, float value);
void translate(NVGcontext *context, float dx, float dy);
void translate(NVGcontext *context, const math::Vec2f& value);
void rotate(NVGcontext *context, float angle);
void rotate(NVGcontext *context, float angle, const math::Vec2f& point);
void scaleX(NVGcontext *context, float sx);
void scaleY(NVGcontext *context, float sy);
void scale(NVGcontext *context, float value);
void scale(NVGcontext *context, float sx, float sy);
void scale(NVGcontext *context, const math::Vec2f& value);
void skewX(NVGcontext *context, float angle);
void skewY(NVGcontext *context, float angle);

#pragma mark -

inline void translateX(float dx) {
  translateX(Context::shared(), dx);
}

inline void translateY(float dy) {
  translateY(Context::shared(), dy);
}

inline void translate(float value) {
  translate(Context::shared(), value);
}

inline void translate(float dx, float dy) {
  translate(Context::shared(), dx, dy);
}

inline void translate(const math::Vec2f& value) {
  translate(Context::shared(), value);
}

inline void rotate(float angle) {
  rotate(Context::shared(), angle);
}

inline void rotate(float angle, const math::Vec2f& point) {
  rotate(Context::shared(), angle, point);
}

inline void scaleX(float sx) {
  scaleX(Context::shared(), sx);
}

inline void scaleY(float sy) {
  scaleY(Context::shared(), sy);
}

inline void scale(float value) {
  scale(Context::shared(), value);
}

inline void scale(float sx, float sy) {
  scale(Context::shared(), sx, sy);
}

inline void scale(const math::Vec2f& value) {
  scale(Context::shared(), value);
}

inline void skewX(float angle) {
  skewX(Context::shared(), angle);
}

inline void skewY(float angle) {
  skewY(Context::shared(), angle);
}

inline void translateX(NVGcontext *context, float dx) {
  nvgTranslate(context, dx, 0.0);
}

inline void translateY(NVGcontext *context, float dy) {
  nvgTranslate(context, 0.0, dy);
}

inline void translate(NVGcontext *context, float value) {
  nvgTranslate(context, value, value);
}

inline void translate(NVGcontext *context, float dx, float dy) {
  nvgTranslate(context, dx, dy);
}

inline void translate(NVGcontext *context, const math::Vec2f& value) {
  nvgTranslate(context, value.x, value.y);
}

inline void rotate(NVGcontext *context, float angle) {
  nvgRotate(context, angle);
}

inline void rotate(NVGcontext *context, float angle, const math::Vec2f& point) {
  nvgTranslate(context, point.x, point.y);
  nvgRotate(context, angle);
  nvgTranslate(context, -point.x, -point.y);
}

inline void scaleX(NVGcontext *context, float sx) {
  nvgScale(context, sx, 1.0);
}

inline void scaleY(NVGcontext *context, float sy) {
  nvgScale(context, 1.0, sy);
}

inline void scale(NVGcontext *context, float value) {
  nvgScale(context, value, value);
}

inline void scale(NVGcontext *context, float sx, float sy) {
  nvgScale(context, sx, sy);
}

inline void scale(NVGcontext *context, const math::Vec2f& value) {
  nvgScale(context, value.x, value.y);
}

inline void skewX(NVGcontext *context, float angle) {
  nvgSkewX(context, angle);
}

inline void skewY(NVGcontext *context, float angle) {
  nvgSkewY(context, angle);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_TRANSFORM_H_
