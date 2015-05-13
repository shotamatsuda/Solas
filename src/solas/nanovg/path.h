//
//  solas/nanovg/path.h
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
#ifndef SOLAS_NANOVG_PATH_H_
#define SOLAS_NANOVG_PATH_H_

#include "nanovg.h"

#include "solas/graphics/path.h"
#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

// Low-level path operations
void BeginPath();
void MoveTo(Real x, Real y);
void MoveTo(const Vec& point);
void LineTo(Real x, Real y);
void LineTo(const Vec& point);
void QuadTo(Real cx, Real cy, Real x, Real y);
void QuadTo(const Vec& control, const Vec& point);
void CubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y);
void CubicTo(const Vec& control1, const Vec& control2, const Vec& point);
void Path(const graphics::Path& path);
void Contour(const graphics::Contour& contour);
void ClosePath();
void PathWinding(int direction);

// Rect
void Rect(Real width, Real height);
void Rect(const Size& size);
void Rect(Real x, Real y, Real width, Real height);
void Rect(const Vec& vec, const Size& size);
void Rect(const Rec& rect);

// Rounded rect
void RoundedRect(Real x, Real y, Real width, Real height, Real radius);
void RoundedRect(const Vec& vec, const Size& size, Real radius);
void RoundedRect(const Rec& rect, Real radius);

// Ellipse
void Ellipse(Real x, Real y, Real width, Real height);
void Ellipse(const Vec& vec, const Size& size);
void Ellipse(const Rec& rect);

// Circle
void Circle(Real x, Real y, Real radius);
void Circle(const Vec& vec, Real radius);

// Drawing
void Fill();
void Stroke();

#pragma mark -

inline void BeginPath() {
  nvgBeginPath(Context::Current());
}

inline void MoveTo(Real x, Real y) {
  nvgMoveTo(Context::Current(), x, y);
}

inline void MoveTo(const Vec& point) {
  nvgMoveTo(Context::Current(), point.x, point.y);
}

inline void LineTo(Real x, Real y) {
  nvgLineTo(Context::Current(), x, y);
}

inline void LineTo(const Vec& point) {
  nvgLineTo(Context::Current(), point.x, point.y);
}

inline void QuadTo(Real cx, Real cy, Real x, Real y) {
  nvgQuadTo(Context::Current(), cx, cy, x, y);
}

inline void QuadTo(const Vec& control, const Vec& point) {
  nvgQuadTo(Context::Current(), control.x, control.y, point.x, point.y);
}

inline void CubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y) {
  nvgBezierTo(Context::Current(), cx1, cy1, cx2, cy2, x, y);
}

inline void CubicTo(const Vec& control1,
                    const Vec& control2,
                    const Vec& point) {
  nvgBezierTo(Context::Current(),
              control1.x, control1.y,
              control2.x, control2.y,
              point.x, point.y);
}

inline void ClosePath() {
  nvgClosePath(Context::Current());
}

inline void PathWinding(int direction) {
  nvgPathWinding(Context::Current(), direction);
}

inline void Rect(Real width, Real height) {
  nvgRect(Context::Current(), Real(), Real(), width, height);
}

inline void Rect(const Size& size) {
  nvgRect(Context::Current(), Real(), Real(), size.w, size.h);
}

inline void Rect(float x, float y, float width, float height) {
  nvgRect(Context::Current(), x, y, width, height);
}

inline void Rect(const Vec& vec, const Size& size) {
  nvgRect(Context::Current(), vec.x, vec.y, size.w, size.h);
}

inline void Rect(const Rec& rect) {
  nvgRect(Context::Current(), rect.x, rect.y, rect.w, rect.h);
}

inline void RoundedRect(Real x, Real y, Real width, Real height, Real radius) {
  nvgRoundedRect(Context::Current(), x, y, width, height, radius);
}

inline void RoundedRect(const Vec& vec, const Size& size, Real radius) {
  nvgRoundedRect(Context::Current(), vec.x, vec.y, size.w, size.h, radius);
}

inline void RoundedRect(const Rec& rect, Real radius) {
  nvgRoundedRect(Context::Current(), rect.x, rect.y, rect.w, rect.h, radius);
}

inline void Ellipse(Real x, Real y, Real width, Real height) {
  nvgEllipse(Context::Current(), x, y, width, height);
}

inline void Ellipse(const Vec& vec, const Size& size) {
  nvgEllipse(Context::Current(), vec.x, vec.y, size.w, size.h);
}

inline void Ellipse(const Rec& rect) {
  nvgEllipse(Context::Current(), rect.x, rect.y, rect.w, rect.h);
}

inline void Circle(Real x, Real y, Real radius) {
  nvgCircle(Context::Current(), x, y, radius);
}

inline void Circle(const Vec& vec, Real radius) {
  nvgCircle(Context::Current(), vec.x, vec.y, radius);
}

inline void Fill() {
  nvgFill(Context::Current());
}

inline void Stroke() {
  nvgStroke(Context::Current());
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_PATH_H_
