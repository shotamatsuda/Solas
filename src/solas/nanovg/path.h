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

void BeginPath();
void MoveTo(Real x, Real y);
void MoveTo(const Vec2& point);
void LineTo(Real x, Real y);
void LineTo(const Vec2& point);
void QuadTo(Real cx, Real cy, Real x, Real y);
void QuadTo(const Vec2& control, const Vec2& point);
void CubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y);
void CubicTo(const Vec2& control1, const Vec2& control2, const Vec2& point);
void AppendPath(const graphics::Path& path);
void AppendSegment(const graphics::Segment& segment);
void ClosePath();
void PathWinding(int direction);
void Rect(const Vec2& point, const Size2& size);
void RoundedRect(const Vec2& point, const Size2& size, Real radius);
void Ellipse(const Vec2& point, const Size2& size);
void Circle(const Vec2& point, Real radius);
void Fill();
void Stroke();

#pragma mark -

inline void BeginPath() {
  nvgBeginPath(Context::Current());
}

inline void MoveTo(Real x, Real y) {
  nvgMoveTo(Context::Current(), x, y);
}

inline void MoveTo(const Vec2& point) {
  nvgMoveTo(Context::Current(), point.x, point.y);
}

inline void LineTo(Real x, Real y) {
  nvgLineTo(Context::Current(), x, y);
}

inline void LineTo(const Vec2& point) {
  nvgLineTo(Context::Current(), point.x, point.y);
}

inline void QuadTo(Real cx, Real cy, Real x, Real y) {
  nvgQuadTo(Context::Current(), cx, cy, x, y);
}

inline void QuadTo(const Vec2& control, const Vec2& point) {
  nvgQuadTo(Context::Current(), control.x, control.y, point.x, point.y);
}

inline void CubicTo(Real cx1, Real cy1, Real cx2, Real cy2, Real x, Real y) {
  nvgBezierTo(Context::Current(), cx1, cy1, cx2, cy2, x, y);
}

inline void CubicTo(const Vec2& control1,
                    const Vec2& control2,
                    const Vec2& point) {
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

inline void Rect(const Vec2& point, const Size2& size) {
  nvgRect(Context::Current(), point.x, point.y, size.w, size.h);
}

inline void RoundedRect(const Vec2& point, const Size2& size, Real radius) {
  nvgRoundedRect(Context::Current(), point.x, point.y, size.w, size.h, radius);
}

inline void Ellipse(const Vec2& point, const Size2& size) {
  nvgEllipse(Context::Current(), point.x, point.y, size.w, size.h);
}

inline void Circle(const Vec2& point, Real radius) {
  nvgCircle(Context::Current(), point.x, point.y, radius);
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
