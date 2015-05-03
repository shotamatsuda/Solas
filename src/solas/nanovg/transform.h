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

#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

void TranslateX(Real dx);
void TranslateY(Real dy);
void Translate(Real value);
void Translate(Real dx, Real dy);
void Translate(const Vec2& value);
void Rotate(Real angle);
void Rotate(Real angle, const Vec2& point);
void ScaleX(Real sx);
void ScaleY(Real sy);
void Scale(Real value);
void Scale(Real sx, Real sy);
void Scale(const Vec2& value);
void SkewX(Real angle);
void SkewY(Real angle);

#pragma mark -

inline void TranslateX(Real dx) {
  nvgTranslate(Context::Shared(), dx, 0.0);
}

inline void TranslateY(Real dy) {
  nvgTranslate(Context::Shared(), 0.0, dy);
}

inline void Translate(Real value) {
  nvgTranslate(Context::Shared(), value, value);
}

inline void Translate(Real dx, Real dy) {
  nvgTranslate(Context::Shared(), dx, dy);
}

inline void Translate(const Vec2& value) {
  nvgTranslate(Context::Shared(), value.x, value.y);
}

inline void Rotate(Real angle) {
  nvgRotate(Context::Shared(), angle);
}

inline void Rotate(Real angle, const Vec2& point) {
  nvgTranslate(Context::Shared(), point.x, point.y);
  nvgRotate(Context::Shared(), angle);
  nvgTranslate(Context::Shared(), -point.x, -point.y);
}

inline void ScaleX(Real sx) {
  nvgScale(Context::Shared(), sx, 1.0);
}

inline void ScaleY(Real sy) {
  nvgScale(Context::Shared(), 1.0, sy);
}

inline void Scale(Real value) {
  nvgScale(Context::Shared(), value, value);
}

inline void Scale(Real sx, Real sy) {
  nvgScale(Context::Shared(), sx, sy);
}

inline void Scale(const Vec2& value) {
  nvgScale(Context::Shared(), value.x, value.y);
}

inline void SkewX(Real angle) {
  nvgSkewX(Context::Shared(), angle);
}

inline void SkewY(Real angle) {
  nvgSkewY(Context::Shared(), angle);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_TRANSFORM_H_
