//
//  solas/processing/constant.h
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
#ifndef SOLAS_PROCESSING_CONSTANTS_H_
#define SOLAS_PROCESSING_CONSTANTS_H_

#include <limits>

#include "solas/math/constants.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

constexpr Real EPSILON = std::numeric_limits<Real>::epsilon();
constexpr Real MAX_REAL = std::numeric_limits<Real>::max();
constexpr Real MIN_REAL = std::numeric_limits<Real>::min();
constexpr Real MAX_INT = std::numeric_limits<int>::min();
constexpr Real MIN_INT = std::numeric_limits<int>::min();
constexpr Real PI = math::pi<Real>;
constexpr Real HALF_PI = math::half_pi<Real>;
constexpr Real THIRD_PI = math::third_pi<Real>;
constexpr Real QUARTER_PI = math::quarter_pi<Real>;
constexpr Real TWO_PI = math::two_pi<Real>;
constexpr Real TAU = math::two_pi<Real>;
constexpr Real E = math::e<Real>;
constexpr Real DEG_TO_RAD = math::degree<Real>;
constexpr Real RAD_TO_DEG = math::radian<Real>;

enum Constant {
  // General
  NONE,

  // Shapes
  VERTEX,
  BEZIER_VERTEX,
  QUADRATIC_VERTEX,
  CURVE_VERTEX,
  BREAK,

  // Angle modes
  RADIANS,
  DEGREES,

  // Colors and images
  RGB,
  ARGB,
  HSB,
  ALPHA,
  CMYK,

  // Image file types
  TIFF,
  PNG,
  JPEG,
  GIF,

  // Filter/convert types
  BLUR,
  GRAY,
  INVERT,
  OPAQUE,
  POSTERIZE,
  THRESHOLD,
  ERODE,
  DILATE,

  // Blend mode keyword definitions
  REPLACE,
  BLEND,
  ADD,
  SUBTRACT,
  LIGHTEST,
  DARKEST,
  DIFFERENCE,
  EXCLUSION,
  MULTIPLY,
  SCREEN,
  OVERLAY,
  HARD_LIGHT,
  SOFT_LIGHT,
  DODGE,
  BURN,

  // Types of transformation matrices
  PROJECTION,
  MODELVIEW,

  // Types of projection matrices
  CUSTOM,
  ORTHOGRAPHIC,
  PERSPECTIVE,

  // Shapes
  GROUP,
  POINT,
  POINTS,
  LINE,
  LINES,
  LINE_STRIP,
  LINE_LOOP,
  TRIANGLE,
  TRIANGLES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
  QUAD,
  QUADS,
  QUAD_STRIP,
  POLYGON,
  PATH,
  RECT,
  ELLIPSE,
  ARC,
  SPHERE,
  BOX,

  // Shape closing modes
  OPEN,
  CLOSE,

  // Shape drawing modes
  CORNER,
  CORNERS,
  RADIUS,
  CENTER,
  DIAMETER,

  // Arc drawing modes
  CHORD,
  PIE,

  // Vertically alignment modes for text
  BASELINE,
  TOP,
  BOTTOM,

  // UV texture orientation modes
  NORMAL,
  IMAGE,

  // Texture wrapping modes
  CLAMP,
  REPEAT,

  // Text placement modes
  MODEL,
  SHAPE,

  // Stroke modes
  SQUARE,
  ROUND,
  PROJECT,
  MITER,
  BEVEL,

  // Lighting
  AMBIENT,
  DIRECTIONAL,
  SPOT,

  // Mouse constants
  MIDDLE,
  OTHER,

  // Key constants
  BACKSPACE,
  TAB,
  ENTER,
  RETURN,
  ESC,
  DELETE,
  CODED,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ALT,
  CONTROL,
  SHIFT,

  // Orientations
  PORTRAIT,
  LANDSCAPE,

  // Cursor types
  ARROW,
  CROSS,
  HAND,
  MOVE,
  TEXT,
  WAIT
};

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_CONSTANTS_H_
