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

void TranslateX(float dx);
void TranslateY(float dy);
void Translate(float value);
void Translate(float dx, float dy);
void Translate(const math::Vec2f& value);
void Rotate(float angle);
void Rotate(float angle, const math::Vec2f& point);
void ScaleX(float sx);
void ScaleY(float sy);
void Scale(float value);
void Scale(float sx, float sy);
void Scale(const math::Vec2f& value);
void SkewX(float angle);
void SkewY(float angle);

void TranslateX(NVGcontext *context, float dx);
void TranslateY(NVGcontext *context, float dy);
void Translate(NVGcontext *context, float value);
void Translate(NVGcontext *context, float dx, float dy);
void Translate(NVGcontext *context, const math::Vec2f& value);
void Rotate(NVGcontext *context, float angle);
void Rotate(NVGcontext *context, float angle, const math::Vec2f& point);
void ScaleX(NVGcontext *context, float sx);
void ScaleY(NVGcontext *context, float sy);
void Scale(NVGcontext *context, float value);
void Scale(NVGcontext *context, float sx, float sy);
void Scale(NVGcontext *context, const math::Vec2f& value);
void SkewX(NVGcontext *context, float angle);
void SkewY(NVGcontext *context, float angle);

#pragma mark -

inline void TranslateX(float dx) {
  TranslateX(Context::shared(), dx);
}

inline void TranslateY(float dy) {
  TranslateY(Context::shared(), dy);
}

inline void Translate(float value) {
  Translate(Context::shared(), value);
}

inline void Translate(float dx, float dy) {
  Translate(Context::shared(), dx, dy);
}

inline void Translate(const math::Vec2f& value) {
  Translate(Context::shared(), value);
}

inline void Rotate(float angle) {
  Rotate(Context::shared(), angle);
}

inline void Rotate(float angle, const math::Vec2f& point) {
  Rotate(Context::shared(), angle, point);
}

inline void ScaleX(float sx) {
  ScaleX(Context::shared(), sx);
}

inline void ScaleY(float sy) {
  ScaleY(Context::shared(), sy);
}

inline void Scale(float value) {
  Scale(Context::shared(), value);
}

inline void Scale(float sx, float sy) {
  Scale(Context::shared(), sx, sy);
}

inline void Scale(const math::Vec2f& value) {
  Scale(Context::shared(), value);
}

inline void SkewX(float angle) {
  SkewX(Context::shared(), angle);
}

inline void SkewY(float angle) {
  SkewY(Context::shared(), angle);
}

inline void TranslateX(NVGcontext *context, float dx) {
  nvgTranslate(context, dx, 0.0);
}

inline void TranslateY(NVGcontext *context, float dy) {
  nvgTranslate(context, 0.0, dy);
}

inline void Translate(NVGcontext *context, float value) {
  nvgTranslate(context, value, value);
}

inline void Translate(NVGcontext *context, float dx, float dy) {
  nvgTranslate(context, dx, dy);
}

inline void Translate(NVGcontext *context, const math::Vec2f& value) {
  nvgTranslate(context, value.x, value.y);
}

inline void Rotate(NVGcontext *context, float angle) {
  nvgRotate(context, angle);
}

inline void Rotate(NVGcontext *context, float angle, const math::Vec2f& point) {
  nvgTranslate(context, point.x, point.y);
  nvgRotate(context, angle);
  nvgTranslate(context, -point.x, -point.y);
}

inline void ScaleX(NVGcontext *context, float sx) {
  nvgScale(context, sx, 1.0);
}

inline void ScaleY(NVGcontext *context, float sy) {
  nvgScale(context, 1.0, sy);
}

inline void Scale(NVGcontext *context, float value) {
  nvgScale(context, value, value);
}

inline void Scale(NVGcontext *context, float sx, float sy) {
  nvgScale(context, sx, sy);
}

inline void Scale(NVGcontext *context, const math::Vec2f& value) {
  nvgScale(context, value.x, value.y);
}

inline void SkewX(NVGcontext *context, float angle) {
  nvgSkewX(context, angle);
}

inline void SkewY(NVGcontext *context, float angle) {
  nvgSkewY(context, angle);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_TRANSFORM_H_
