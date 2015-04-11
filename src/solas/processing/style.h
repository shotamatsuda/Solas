//
//  solas/processing/style.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef SOLAS_PROCESSING_STYLE_H_
#define SOLAS_PROCESSING_STYLE_H_

#include <cstdint>
#include <limits>

#include "solas/processing/constants.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

class Style {
 public:
  // Constructors
  Style();

  // Copy and assign
  Style(const Style& other) = default;
  Style(Style&& other) = default;
  Style& operator=(const Style& other) = default;
  Style& operator=(Style&& other) = default;

  // Comparison
  bool operator==(const Style& other) const;
  bool operator!=(const Style& other) const;

  // Mutators
  void reset();

 public:
  static const constexpr Real default_stroke_weight = 1.0;
  static const constexpr Real default_text_size = 12.0;
  static const constexpr Real default_text_leading = 14.0;

 public:
  // Shape modes
  Constant image_mode;
  Constant rect_mode;
  Constant ellipse_mode;
  Constant shape_mode;

  // Blending mode
  Constant blend_mode;

  // Color mode
  Constant color_mode;
  Real color_mode_x;
  Real color_mode_y;
  Real color_mode_z;
  Real color_mode_a;

  // Color settings
  bool tint;
  Color tint_color;
  bool fill;
  Color fill_color;
  bool stroke;
  Color stroke_color;
  Real stroke_weight;
  Constant stroke_cap;
  Constant stroke_join;

  // Text settings
  Font text_font;
  Constant text_align;
  Constant text_align_y;
  Constant text_mode;
  Real text_size;
  Real text_leading;
};

#pragma mark -

inline Style::Style()
    : image_mode(CORNER),
      rect_mode(CORNER),
      ellipse_mode(CORNER),
      shape_mode(CORNER),
      blend_mode(BLEND),
      color_mode(RGB),
      color_mode_x(std::numeric_limits<std::uint8_t>::max()),
      color_mode_y(std::numeric_limits<std::uint8_t>::max()),
      color_mode_z(std::numeric_limits<std::uint8_t>::max()),
      color_mode_a(std::numeric_limits<std::uint8_t>::max()),
      tint(false),
      tint_color(Color::White()),
      fill(true),
      fill_color(Color::White()),
      stroke(true),
      stroke_color(Color::Black()),
      stroke_weight(default_stroke_weight),
      stroke_cap(SQUARE),
      stroke_join(MITER),
      text_font(),
      text_align(LEFT),
      text_align_y(BASELINE),
      text_mode(MODEL),
      text_size(default_text_size),
      text_leading(default_text_leading) {}

#pragma mark Mutators

inline void Style::reset() {
  image_mode = CORNER;
  rect_mode = CORNER;
  ellipse_mode = CORNER;
  shape_mode = CORNER;
  blend_mode = BLEND;
  color_mode = RGB;
  color_mode_x = std::numeric_limits<std::uint8_t>::max();
  color_mode_y = std::numeric_limits<std::uint8_t>::max();
  color_mode_z = std::numeric_limits<std::uint8_t>::max();
  color_mode_a = std::numeric_limits<std::uint8_t>::max();
  tint = false;
  tint_color = Color::White();
  fill = true;
  fill_color = Color::White();
  stroke = true;
  stroke_color = Color::Black();
  stroke_weight = default_stroke_weight;
  stroke_cap = SQUARE;
  stroke_join = MITER;
  text_font = Font();
  text_align = LEFT;
  text_align_y = BASELINE;
  text_mode = MODEL;
  text_size = default_text_size;
  text_leading = default_text_leading;
}

#pragma mark Comparison

inline bool Style::operator==(const Style& other) const {
  return (image_mode == other.image_mode &&
          rect_mode == other.rect_mode &&
          ellipse_mode == other.ellipse_mode &&
          shape_mode == other.shape_mode &&
          blend_mode == other.blend_mode &&
          color_mode == other.color_mode &&
          color_mode_x == other.color_mode_x &&
          color_mode_y == other.color_mode_y &&
          color_mode_z == other.color_mode_z &&
          color_mode_a == other.color_mode_a &&
          tint == other.tint &&
          tint_color == other.tint_color &&
          fill == other.fill &&
          fill_color == other.fill_color &&
          stroke == other.stroke &&
          stroke_color == other.stroke_color &&
          stroke_weight == other.stroke_weight &&
          stroke_cap == other.stroke_cap &&
          stroke_join == other.stroke_join &&
          text_font == other.text_font &&
          text_align == other.text_align &&
          text_align_y == other.text_align_y &&
          text_mode == other.text_mode &&
          text_size == other.text_size &&
          text_leading == other.text_leading);
}

inline bool Style::operator!=(const Style& other) const {
  return !operator==(other);
}

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_STYLE_H_
