//
//  solas/nanovg/text.h
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
#ifndef SOLAS_NANOVG_TEXT_H_
#define SOLAS_NANOVG_TEXT_H_

#include <string>
#include <tuple>
#include <utility>

#include "nanovg.h"

#include "solas/math/rect.h"
#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

namespace text {

struct Metrics {
  math::Rect<Real> bounds;
  Real advance;
};

}  // namespace text

int CreateFont(const std::string& name, const std::string& filename);
int FindFont(const std::string& name);
void FontSize(Real size);
void FontBlur(Real blur);
void TextLetterSpacing(Real spacing);
void TextLineHeight(Real height);
void TextAlign(NVGalign align);
void FontFace(int font);
void FontFace(const std::string& font);
Real Text(const std::string& text);
Real Text(Real x, Real y, const std::string& text);
Real Text(const Vec& point, const std::string& text);
void TextBox(Real width, const std::string& text);
void TextBox(Real x, Real y, Real width, const std::string& text);
void TextBox(const Vec& point, Real width, const std::string& text);
text::Metrics TextBounds(const std::string& text);
text::Metrics TextBounds(Real x, Real y, const std::string& text);
text::Metrics TextBounds(const Vec& point, const std::string& text);
math::Rect<Real> TextBoxBounds(Real width, const std::string& text);
math::Rect<Real> TextBoxBounds(Real x, Real y, Real width,
                               const std::string& text);
math::Rect<Real> TextBoxBounds(const Vec& point, Real width,
                               const std::string& text);

#pragma mark -

inline int CreateFont(const std::string& name, const std::string& filename) {
  return nvgCreateFont(Context::Current(), name.c_str(), filename.c_str());
}

inline int FindFont(const std::string& name) {
  return nvgFindFont(Context::Current(), name.c_str());
}

inline void FontSize(Real size) {
  nvgFontSize(Context::Current(), size);
}

inline void FontBlur(Real blur) {
  nvgFontSize(Context::Current(), blur);
}

inline void TextLetterSpacing(Real spacing) {
  nvgFontSize(Context::Current(), spacing);
}

inline void TextLineHeight(Real height) {
  nvgFontSize(Context::Current(), height);
}

inline void TextAlign(NVGalign align) {
  nvgFontSize(Context::Current(), align);
}

inline void FontFace(int font) {
  nvgFontSize(Context::Current(), font);
}

inline void FontFace(const std::string& font) {
  nvgFontFace(Context::Current(), font.c_str());
}

inline Real Text(const std::string& text) {
  return Text(Real(), Real(), text);
}

inline Real Text(Real x, Real y, const std::string& text) {
  return nvgText(Context::Current(), x, y, text.c_str(), nullptr);
}

inline Real Text(const Vec& point, const std::string& text) {
  return Text(point.x, point.y, text);
}

inline void TextBox(Real width, const std::string& text) {
  TextBox(Real(), Real(), width, text);
}

inline void TextBox(Real x, Real y, Real width, const std::string& text) {
  nvgTextBox(Context::Current(), x, y, width, text.c_str(), nullptr);
}

inline void TextBox(const Vec& point, Real width, const std::string& text) {
  TextBox(point.x, point.y, width, text);
}

inline text::Metrics TextBounds(const std::string& string) {
  return TextBounds(Real(), Real(), string);
}

inline text::Metrics TextBounds(Real x, Real y, const std::string& text) {
  text::Metrics metrics;
  struct { Real xmin; Real ymin; Real xmax; Real ymax; } bounds;
  metrics.advance = nvgTextBounds(
      Context::Current(), x, y,
      text.c_str(), nullptr, &bounds.xmin);
  metrics.bounds.set(Vec(bounds.xmin, bounds.ymin),
                     Vec(bounds.xmax, bounds.ymax));
  return std::move(metrics);
}

inline text::Metrics TextBounds(const Vec& point, const std::string& string) {
  return TextBounds(point.x, point.y, string);
}

inline math::Rect<Real> TextBoxBounds(Real width, const std::string& text) {
  return TextBoxBounds(Real(), Real(), width, text);
}

inline math::Rect<Real> TextBoxBounds(Real x, Real y, Real width,
                                      const std::string& text) {
  struct { Real xmin; Real ymin; Real xmax; Real ymax; } bounds;
  nvgTextBoxBounds(
      Context::Current(), x, y, width,
      text.c_str(), nullptr, &bounds.xmin);
  return math::Rect<Real>(Vec(bounds.xmin, bounds.ymin),
                          Vec(bounds.xmax, bounds.ymax));
}

inline math::Rect<Real> TextBoxBounds(const Vec& point, Real width,
                                      const std::string& text) {
  return TextBoxBounds(point.x, point.y, width, text);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STYLE_H_
