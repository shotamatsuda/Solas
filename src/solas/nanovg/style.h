//
//  solas/nanovg/style.h
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
#ifndef SOLAS_NANOVG_STYLE_H_
#define SOLAS_NANOVG_STYLE_H_

#include "nanovg.h"

#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

// Stroke
void StrokeColor(NVGcolor color);
void StrokePaint(NVGpaint paint);

// Fill
void FillColor(NVGcolor color);
void FillPaint(NVGpaint paint);

// Stroke settings
void MiterLimit(Real limit);
void StrokeWidth(Real size);
void LineCap(NVGlineCap cap);
void LineJoin(NVGlineCap join);

// Global settings
void GlobalAlpha(Real alpha);

#pragma mark -

inline void StrokeColor(NVGcolor color) {
  nvgStrokeColor(Context::Current(), color);
}

inline void StrokePaint(NVGpaint paint) {
  nvgStrokePaint(Context::Current(), paint);
}

inline void FillColor(NVGcolor color) {
  nvgFillColor(Context::Current(), color);
}

inline void FillPaint(NVGpaint paint) {
  nvgFillPaint(Context::Current(), paint);
}

inline void MiterLimit(Real limit) {
  nvgMiterLimit(Context::Current(), limit);
}

inline void StrokeWidth(Real size) {
  nvgStrokeWidth(Context::Current(), size);
}

inline void LineCap(NVGlineCap cap) {
  nvgLineCap(Context::Current(), cap);
}

inline void LineJoin(NVGlineCap join) {
  nvgLineJoin(Context::Current(), join);
}

inline void GlobalAlpha(Real alpha) {
  nvgGlobalAlpha(Context::Current(), alpha);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STYLE_H_
