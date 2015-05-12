//
//  solas/nanovg/scissor.h
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
#ifndef SOLAS_NANOVG_SCISSOR_H_
#define SOLAS_NANOVG_SCISSOR_H_

#include "nanovg.h"

#include "solas/math/rect.h"
#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

void Scissor(Real width, Real height);
void Scissor(const Size2& size);
void Scissor(Real x, Real y, Real width, Real height);
void Scissor(const Vec2& point, const Size2& size);
void Scissor(const math::Rect<Real>& rect);
void IntersectScissor(Real width, Real height);
void IntersectScissor(const Size2& size);
void IntersectScissor(Real x, Real y, Real width, Real height);
void IntersectScissor(const Vec2& point, const Size2& size);
void IntersectScissor(const math::Rect<Real>& rect);
void ResetScissor();

#pragma mark -

inline void Scissor(Real width, Real height) {
  nvgScissor(Context::Current(), Real(), Real(), width, height);
}

inline void Scissor(const Size2& size) {
  nvgScissor(Context::Current(), Real(), Real(), size.w, size.h);
}

inline void Scissor(Real x, Real y, Real width, Real height) {
  nvgScissor(Context::Current(), x, y, width, height);
}

inline void Scissor(const Vec2& point, const Size2& size) {
  nvgScissor(Context::Current(), point.x, point.y, size.w, size.h);
}

inline void Scissor(const math::Rect<Real>& rect) {
  nvgScissor(Context::Current(), rect.x, rect.y, rect.w, rect.h);
}

inline void IntersectScissor(Real width, Real height) {
  nvgIntersectScissor(Context::Current(), Real(), Real(), width, height);
}

inline void IntersectScissor(const Size2& size) {
  nvgIntersectScissor(Context::Current(), Real(), Real(), size.w, size.h);
}

inline void IntersectScissor(Real x, Real y, Real width, Real height) {
  nvgIntersectScissor(Context::Current(), x, y, width, height);
}

inline void IntersectScissor(const Vec2& point, const Size2& size) {
  nvgIntersectScissor(Context::Current(), point.x, point.y, size.w, size.h);
}

inline void IntersectScissor(const math::Rect<Real>& rect) {
  nvgIntersectScissor(Context::Current(), rect.x, rect.y, rect.w, rect.h);
}

inline void ResetScissor() {
  nvgResetScissor(Context::Current());
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_SCISSOR_H_
