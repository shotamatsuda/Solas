//
//  solas/processing/layer.h
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
#ifndef SOLAS_PROCESSING_LAYER_H_
#define SOLAS_PROCESSING_LAYER_H_

#include <chrono>

#include "solas/processing/constants.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

class Layer {
 public:
  // Structure
  void pushStyle();
  void popStyle();

  // Shape > 2D primitive
  void point(Real x, Real y) const;
  void point(const Vec2& p) const;
  void line(Real x1, Real y1, Real x2, Real y2) const;
  void line(const Vec2& a, const Vec2& b) const;
  void triangle(Real x1, Real y1, Real x2, Real y2, Real x3, Real y3) const;
  void triangle(const Vec2& a, const Vec2& b, const Vec2& c) const;
  void quad(Real x1, Real y1, Real x2, Real y2,
            Real x3, Real y3, Real x4, Real y4) const;
  void quad(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d) const;
  void rect(Real a, Real b, Real c, Real d) const;
  void rect(Real a, Real b, Real c, Real d, Real r) const;
  void rect(Real a, Real b, Real c, Real d,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(Real a, Real b, Real c, Real d, Constant mode) const;
  void rect(Real a, Real b, Real c, Real d, Real r, Constant mode) const;
  void rect(Real a, Real b, Real c, Real d,
            Real tl, Real tr, Real br, Real bl, Constant mode) const;
  void rect(const Vec2& a, const Vec2& b) const;
  void rect(const Vec2& a, const Vec2& b, Real r) const;
  void rect(const Vec2& a, const Vec2& b,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(const Vec2& a, const Size2& b) const;
  void rect(const Vec2& a, const Size2& b, Real r) const;
  void rect(const Vec2& a, const Size2& b,
            Real tl, Real tr, Real br, Real bl) const;
  void arc(Real a, Real b, Real c, Real d, Real start, Real stop) const;
  void arc(Real a, Real b, Real c, Real d,
           Real start, Real stop, Constant mode) const;
  void arc(const Vec2& a, const Vec2& b, Real start, Real stop) const;
  void arc(const Vec2& a, const Vec2& b,
           Real start, Real stop, Constant mode) const;
  void arc(const Vec2& a, const Size2& b, Real start, Real stop) const;
  void arc(const Vec2& a, const Size2& b,
           Real start, Real stop, Constant mode) const;
  void ellipse(Real a, Real b, Real c, Real d) const;
  void ellipse(Real a, Real b, Real c, Real d, Constant mode) const;
  void ellipse(const Vec2& a, const Vec2& b) const;
  void ellipse(const Vec2& a, const Size2& b) const;

  // Shape > Attributes
  void smooth();
  void noSmooth();
  Real strokeWeight() const;
  void strokeWeight(Real weight);
  Constant strokeCap() const;
  void strokeCap(Constant cap);
  Constant strokeJoin() const;
  void strokeJoin(Constant join);
  Constant rectMode() const;
  void rectMode(Constant mode);
  Constant ellipseMode() const;
  void ellipseMode(Constant mode);

  // Transform
  void applyMatrix(Real n00, Real n01, Real n02,
                   Real n10, Real n11, Real n12);
  void applyMatrix(Real n00, Real n01, Real n02, Real n03,
                   Real n10, Real n11, Real n12, Real n13,
                   Real n20, Real n21, Real n22, Real n23,
                   Real n30, Real n31, Real n32, Real n33);
  void applyMatrix(const Vec3& n0, const Vec3& n1);
  void applyMatrix(const Vec4& n0, const Vec4& n1,
                   const Vec4& n2, const Vec4& n3);
  void popMatrix();
  void pushMatrix();
  void resetMatrix();
  void scale(Real s);
  void scale(Real x, Real y);
  void scale(Real x, Real y, Real z);
  void scale(const Vec2& p);
  void scale(const Vec3& p);
  void translate(Real x, Real y);
  void translate(Real x, Real y, Real z);
  void translate(const Vec2& p);
  void translate(const Vec3& p);
  void rotate(Real radians);
  void rotate(Real radians, Real x, Real y);
  void rotate(Real radians, Real x, Real y, Real z);
  void rotate(Real radians, const Vec2& p);
  void rotate(Real radians, const Vec3& p);
  void rotateX(Real radians);
  void rotateY(Real radians);
  void shearX(Real radians);
  void shearY(Real radians);

  // Input > Time & Date
  std::chrono::milliseconds::rep millis() const;

  // Color > Setting
  void colorMode(Constant mode);
  void colorMode(Constant mode, Real max);
  void colorMode(Constant mode, Real max1, Real max2, Real max3);
  void colorMode(Constant mode, Real max1, Real max2, Real max3, Real max_a);
  void fill(Real value);
  void fill(Real value, Real alpha);
  void fill(Real v1, Real v2, Real v3);
  void fill(Real v1, Real v2, Real v3, Real alpha);
  void fill(const Color& color);
  void fill(const Color& color, Real alpha);
  void noFill();
  void stroke(Real value);
  void stroke(Real value, Real alpha);
  void stroke(Real v1, Real v2, Real v3);
  void stroke(Real v1, Real v2, Real v3, Real alpha);
  void stroke(const Color& color);
  void stroke(const Color& color, Real alpha);
  void noStroke();
  void background(Real value) const;
  void background(Real value, Real alpha) const;
  void background(Real v1, Real v2, Real v3) const;
  void background(Real v1, Real v2, Real v3, Real alpha) const;
  void background(const Color& color) const;
  void background(const Color& color, Real alpha) const;
  void clear() const;

  // Color > Creating & Reading
  Color color(Real value) const;
  Color color(Real value, Real alpha) const;
  Color color(Real v1, Real v2, Real v3) const;
  Color color(Real v1, Real v2, Real v3, Real alpha) const;
  Color color(const Color& color) const;
  Color color(const Color& color, Real alpha) const;
};

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_LAYER_H_
