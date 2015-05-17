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

#include "nanovg.h"

#include "solas/nanovg/context.h"
#include "solas/nanovg/type.h"

namespace solas {
namespace nanovg {

// Font creation
int CreateFont(const std::string& name, const std::string& filename);
int FindFont(const std::string& name);

// Font settings
void FontSize(Real size);
void FontBlur(Real blur);
  
// Text settings
void TextLetterSpacing(Real spacing);
void TextLineHeight(Real height);
void TextAlign(NVGalign align);

// Font face
void FontFace(int font);
void FontFace(const std::string& font);

// Text
Real Text(const std::string& text);
Real Text(Real x, Real y, const std::string& text);
Real Text(const Vec& vec, const std::string& text);
  
// Text box
void TextBox(Real width, const std::string& text);
void TextBox(Real x, Real y, Real width, const std::string& text);
void TextBox(const Vec& vec, Real width, const std::string& text);

// Bounds
Real TextBounds(const std::string& text, Rec *bounds = nullptr);
Real TextBounds(Real x, Real y, const std::string& text, Rec *bounds = nullptr);
Real TextBounds(const Vec& vec, const std::string& text, Rec *bounds = nullptr);

// Box bounds
Rec TextBoxBounds(Real width, const std::string& text);
Rec TextBoxBounds(Real x, Real y, Real width, const std::string& text);
Rec TextBoxBounds(const Vec& vec, Real width, const std::string& text);

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
  nvgFontBlur(Context::Current(), blur);
}

inline void TextLetterSpacing(Real spacing) {
  nvgTextLetterSpacing(Context::Current(), spacing);
}

inline void TextLineHeight(Real height) {
  nvgTextLineHeight(Context::Current(), height);
}

inline void TextAlign(NVGalign align) {
  nvgTextAlign(Context::Current(), align);
}

inline void FontFace(int font) {
  nvgFontFaceId(Context::Current(), font);
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

inline Real Text(const Vec& vec, const std::string& text) {
  return Text(vec.x, vec.y, text);
}

inline void TextBox(Real width, const std::string& text) {
  TextBox(Real(), Real(), width, text);
}

inline void TextBox(Real x, Real y, Real width, const std::string& text) {
  nvgTextBox(Context::Current(), x, y, width, text.c_str(), nullptr);
}

inline void TextBox(const Vec& vec, Real width, const std::string& text) {
  TextBox(vec.x, vec.y, width, text);
}

inline Real TextBounds(const std::string& text, Rec *bounds) {
  return TextBounds(Real(), Real(), text, bounds);
}

inline Real TextBounds(Real x, Real y, const std::string& text, Rec *bounds) {
  struct { Real xmin; Real ymin; Real xmax; Real ymax; } values;
  const auto result = nvgTextBounds(
      Context::Current(), x, y,
      text.c_str(), nullptr, &values.xmin);
  if (bounds) {
    bounds->set(Vec(values.xmin, values.ymin), Vec(values.xmax, values.ymax));
  }
  return result;
}

inline Real TextBounds(const Vec& vec, const std::string& text, Rec *bounds) {
  return TextBounds(vec.x, vec.y, text, bounds);
}

inline Rec TextBoxBounds(Real width, const std::string& text) {
  return TextBoxBounds(Real(), Real(), width, text);
}

inline Rec TextBoxBounds(Real x, Real y, Real width, const std::string& text) {
  struct { Real xmin; Real ymin; Real xmax; Real ymax; } values;
  nvgTextBoxBounds(
      Context::Current(), x, y, width,
      text.c_str(), nullptr, &values.xmin);
  return Rec(Vec(values.xmin, values.ymin), Vec(values.xmax, values.ymax));
}

inline Rec TextBoxBounds(const Vec& vec, Real width, const std::string& text) {
  return TextBoxBounds(vec.x, vec.y, width, text);
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STYLE_H_
