//
//  solas/nanovg/paint.h
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
#ifndef SOLAS_NANOVG_PAINT_H_
#define SOLAS_NANOVG_PAINT_H_

#include "nanovg.h"

#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

// Linear gradient
NVGpaint LinearGradient(Real start_x, Real start_y, Real stop_x, Real stop_y,
                        NVGcolor start_color, NVGcolor stop_color);
NVGpaint LinearGradient(const Vec& start, const Vec& stop,
                        NVGcolor start_color, NVGcolor stop_color);

// Box gradient
NVGpaint BoxGradient(Real x, Real y, Real width, Real height,
                     Real radius, Real feather,
                     NVGcolor start_color, NVGcolor stop_color);
NVGpaint BoxGradient(const Vec& vec, const Size& size,
                     Real radius, Real feather,
                     NVGcolor start_color, NVGcolor stop_color);
NVGpaint BoxGradient(const Rec& rect, Real radius, Real feather,
                     NVGcolor start_color, NVGcolor stop_color);

// Radial gradient
NVGpaint RadialGradient(Real x, Real y, Real
                        start_radius, Real stop_radius,
                        NVGcolor start_color, NVGcolor stop_color);
NVGpaint RadialGradient(const Vec& vec, Real
                        start_radius, Real stop_radius,
                        NVGcolor start_color, NVGcolor stop_color);

// Image pattern
NVGpaint ImagePattern(Real x, Real y, Real width, Real height,
                      Real angle, int image, Real alpha);
NVGpaint ImagePattern(const Vec& vec, const Size& size,
                      Real angle, int image, Real alpha);
NVGpaint ImagePattern(const Rec& rect,
                      Real angle, int image, Real alpha);

#pragma mark -

inline NVGpaint LinearGradient(Real start_x, Real start_y,
                               Real stop_x, Real stop_y,
                               NVGcolor start_color, NVGcolor stop_color) {
  return nvgLinearGradient(Context::Current(), start_x, start_y,
                           stop_x, stop_y, start_color, stop_color);
}

inline NVGpaint LinearGradient(const Vec& start, const Vec& stop,
                        NVGcolor start_color, NVGcolor stop_color) {
  return LinearGradient(start.x, start.y, stop.x, stop.y,
                        start_color, stop_color);
}

inline NVGpaint BoxGradient(Real x, Real y, Real width, Real height,
                            Real radius, Real feather,
                            NVGcolor start_color, NVGcolor stop_color) {
  return nvgBoxGradient(Context::Current(), x, y, width, height,
                        radius, feather, start_color, stop_color);
}

inline NVGpaint BoxGradient(const Vec& vec, const Size& size,
                            Real radius, Real feather,
                            NVGcolor start_color, NVGcolor stop_color) {
  return BoxGradient(vec.x, vec.y, size.w, size.h,
                     radius, feather, start_color, stop_color);
}

inline NVGpaint BoxGradient(const Rec& rect, Real radius, Real feather,
                            NVGcolor start_color, NVGcolor stop_color) {
  return BoxGradient(rect.x, rect.y, rect.w, rect.h,
                     radius, feather, start_color, stop_color);
}

inline NVGpaint RadialGradient(Real x, Real y,
                               Real start_radius, Real stop_radius,
                               NVGcolor start_color, NVGcolor stop_color) {
  return nvgRadialGradient(Context::Current(), x, y,
                           start_radius, stop_radius, start_color, stop_color);
}

inline NVGpaint RadialGradient(const Vec& vec,
                               Real start_radius, Real stop_radius,
                               NVGcolor start_color, NVGcolor stop_color) {
  return RadialGradient(vec.x, vec.y, start_radius, stop_radius,
                        start_color, stop_color);
}

inline NVGpaint ImagePattern(Real x, Real y, Real width, Real height,
                             Real angle, int image, Real alpha) {
  return nvgImagePattern(Context::Current(), x, y, width, height,
                         angle, image, alpha);
}

inline NVGpaint ImagePattern(const Vec& vec, const Size& size,
                             Real angle, int image, Real alpha) {
  return ImagePattern(vec.x, vec.y, size.w, size.h, angle, image, alpha);
}

inline NVGpaint ImagePattern(const Rec& rect, Real angle,
                             int image, Real alpha) {
  return ImagePattern(rect.x, rect.y, rect.w, rect.h, angle, image, alpha);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_PAINT_H_
