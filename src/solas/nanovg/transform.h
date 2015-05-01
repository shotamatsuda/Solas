//
//  solas/nanovg/transform.h
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
  TranslateX(Context::Shared(), dx);
}

inline void TranslateY(float dy) {
  TranslateY(Context::Shared(), dy);
}

inline void Translate(float value) {
  Translate(Context::Shared(), value);
}

inline void Translate(float dx, float dy) {
  Translate(Context::Shared(), dx, dy);
}

inline void Translate(const math::Vec2f& value) {
  Translate(Context::Shared(), value);
}

inline void Rotate(float angle) {
  Rotate(Context::Shared(), angle);
}

inline void Rotate(float angle, const math::Vec2f& point) {
  Rotate(Context::Shared(), angle, point);
}

inline void ScaleX(float sx) {
  ScaleX(Context::Shared(), sx);
}

inline void ScaleY(float sy) {
  ScaleY(Context::Shared(), sy);
}

inline void Scale(float value) {
  Scale(Context::Shared(), value);
}

inline void Scale(float sx, float sy) {
  Scale(Context::Shared(), sx, sy);
}

inline void Scale(const math::Vec2f& value) {
  Scale(Context::Shared(), value);
}

inline void SkewX(float angle) {
  SkewX(Context::Shared(), angle);
}

inline void SkewY(float angle) {
  SkewY(Context::Shared(), angle);
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
