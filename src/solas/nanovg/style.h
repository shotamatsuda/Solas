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

#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

void StrokeColor(NVGcolor color);
void StrokePaint(NVGpaint paint);
void FillColor(NVGcolor color);
void FillPaint(NVGpaint paint);
void MiterLimit(Real limit);
void StrokeWidth(Real size);
void LineCap(int cap);
void LineJoin(int join);
void GlobalAlpha(Real alpha);

#pragma mark -

inline void StrokeColor(NVGcolor color) {
  nvgStrokeColor(Context::Shared(), color);
}

inline void StrokePaint(NVGpaint paint) {
  nvgStrokePaint(Context::Shared(), paint);
}

inline void FillColor(NVGcolor color) {
  nvgFillColor(Context::Shared(), color);
}

inline void FillPaint(NVGpaint paint) {
  nvgFillPaint(Context::Shared(), paint);
}

inline void MiterLimit(Real limit) {
  nvgMiterLimit(Context::Shared(), limit);
}

inline void StrokeWidth(Real size) {
  nvgStrokeWidth(Context::Shared(), size);
}

inline void LineCap(int cap) {
  nvgLineCap(Context::Shared(), cap);
}

inline void LineJoin(int join) {
  nvgLineJoin(Context::Shared(), join);
}

inline void GlobalAlpha(Real alpha) {
  nvgGlobalAlpha(Context::Shared(), alpha);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STYLE_H_
