//
//  solas/processing/graphics.h
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
#ifndef SOLAS_PROCESSING_GRAPHICS_H_
#define SOLAS_PROCESSING_GRAPHICS_H_

#include <cassert>
#include <memory>
#include <list>

#include "solas/graphics/context_holder.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/stroke.h"
#include "solas/processing/constants.h"
#include "solas/processing/style.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

class Graphics {
 public:
  // Constructors
  Graphics() = default;
  virtual ~Graphics() = 0;

  // Disallow copy and assign
  Graphics(const Graphics& other) = delete;
  Graphics& operator=(const Graphics& other) = delete;

  // Move
  Graphics(Graphics&& other) = default;

  // Structure
  void pushStyle();
  void popStyle();

  // Point and lines
  void point(Real x, Real y) const;
  void point(const Vec2& p) const;
  void line(Real x1, Real y1, Real x2, Real y2) const;
  void line(const Vec2& a, const Vec2& b) const;
  void triangle(Real x1, Real y1, Real x2, Real y2, Real x3, Real y3) const;
  void triangle(const Vec2& a, const Vec2& b, const Vec2& c) const;
  void quad(Real x1, Real y1, Real x2, Real y2,
            Real x3, Real y3, Real x4, Real y4) const;
  void quad(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d) const;

  // Rect
  void rect(Real a, Real b, Real c, Real d) const;
  void rect(Real a, Real b, Real c, Real d, Constant mode) const;
  void rect(const Vec2& a, const Vec2& b) const;
  void rect(const Vec2& a, const Vec2& b, Constant mode) const;
  void rect(const Vec2& a, const Size2& b) const;
  void rect(const Vec2& a, const Size2& b, Constant mode) const;

  // Rounded rect
  void rect(Real a, Real b, Real c, Real d, Real radius) const;
  void rect(Real a, Real b, Real c, Real d, Real radius, Constant mode) const;
  void rect(const Vec2& a, const Vec2& b, Real radius) const;
  void rect(const Vec2& a, const Vec2& b, Real radius, Constant mode) const;
  void rect(const Vec2& a, const Size2& b, Real radius) const;
  void rect(const Vec2& a, const Size2& b, Real radius, Constant mode) const;

  // Rounded rect with separated radii
  void rect(Real a, Real b, Real c, Real d,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(Real a, Real b, Real c, Real d,
            Real tl, Real tr, Real br, Real bl, Constant mode) const;
  void rect(const Vec2& a, const Vec2& b,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(const Vec2& a, const Vec2& b,
            Real tl, Real tr, Real br, Real bl, Constant mode) const;
  void rect(const Vec2& a, const Size2& b,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(const Vec2& a, const Size2& b,
            Real tl, Real tr, Real br, Real bl, Constant mode) const;

  // Arc
  void arc(Real a, Real b, Real c, Real d, Real start, Real stop) const;
  void arc(Real a, Real b, Real c, Real d, Real start, Real stop,
           Constant mode) const;
  void arc(const Vec2& a, const Vec2& b, Real start, Real stop) const;
  void arc(const Vec2& a, const Vec2& b, Real start, Real stop,
           Constant mode) const;
  void arc(const Vec2& a, const Size2& b, Real start, Real stop) const;
  void arc(const Vec2& a, const Size2& b, Real start, Real stop,
           Constant mode) const;

  // Ellipse
  void ellipse(Real a, Real b, Real c, Real d) const;
  void ellipse(Real a, Real b, Real c, Real d, Constant mode) const;
  void ellipse(const Vec2& a, const Vec2& b) const;
  void ellipse(const Vec2& a, const Vec2& b, Constant mode) const;
  void ellipse(const Vec2& a, const Size2& b) const;
  void ellipse(const Vec2& a, const Size2& b, Constant mode) const;

  // Shape attributes
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
  void translate(Real x, Real y);
  void translate(Real x, Real y, Real z);
  void translate(const Vec2& vector);
  void translate(const Vec3& vector);
  void scale(Real scalar);
  void scale(Real x, Real y);
  void scale(Real x, Real y, Real z);
  void scale(const Vec2& vector);
  void scale(const Vec3& vector);
  void rotate(Real angle);
  void rotate(Real angle, Real x, Real y);
  void rotate(Real angle, Real x, Real y, Real z);
  void rotate(Real angle, const Vec2& center);
  void rotate(Real angle, const Vec3& center);
  void rotateX(Real angle);
  void rotateY(Real angle);
  void rotateZ(Real angle);
  void shearX(Real angle);
  void shearY(Real angle);

  // Vertex
  void beginShape();
  void beginShape(Constant kind);
  void endShape(Constant mode);
  void beginContour();
  void endContour();
  void vertex(Real x, Real y);
  void vertex(const Vec2& vector);
  void curveVertex(Real x, Real y);
  void curveVertex(const Vec2& vector);
  void bezierVertex(Real x, Real y);
  void bezierVertex(const Vec2& vector);
  void quadraticVertex(Real x, Real y);
  void quadraticVertex(const Vec2& vector);

  // Color settings
  void colorMode(Constant mode);
  void colorMode(Constant mode, Real max);
  void colorMode(Constant mode, Real max1, Real max2, Real max3);
  void colorMode(Constant mode, Real max1, Real max2, Real max3, Real max4);
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

  // Color creation and reading
  Color color(Real value) const;
  Color color(Real value, Real alpha) const;
  Color color(Real v1, Real v2, Real v3) const;
  Color color(Real v1, Real v2, Real v3, Real alpha) const;
  Color color(const Color& color) const;
  Color color(const Color& color, Real alpha) const;
  Real red(const Color& color);
  Real green(const Color& color);
  Real blue(const Color& color);
  Real alpha(const Color& color);
  Real hue(const Color& color);
  Real saturation(const Color& color);
  Real brightness(const Color& color);

 protected:
  // Context
  virtual const graphics::ContextHolder& context() const = 0;

 private:
  // Creating fill and stroke
  graphics::Fill fill() const;
  graphics::Stroke stroke() const;

 private:
  Style style_;
  std::list<Style> style_stack_;
};

#pragma mark -

inline Graphics::~Graphics() {}

#pragma mark Structure

inline void Graphics::pushStyle() {
  style_stack_.emplace_back(style_);
}

inline void Graphics::popStyle() {
  assert(!style_stack_.empty());
  style_ = style_stack_.back();
  style_stack_.pop_back();
}

#pragma mark Point and lines

inline void Graphics::point(const Vec2& p) const {
  point(p.x, p.y);
}

inline void Graphics::line(const Vec2& a, const Vec2& b) const {
  line(a.x, a.y, b.x, b.y);
}

inline void Graphics::triangle(const Vec2& a,
                               const Vec2& b,
                               const Vec2& c) const {
  triangle(a.x, a.y, b.x, b.y, c.x, c.y);
}

inline void Graphics::quad(const Vec2& a, const Vec2& b,
                           const Vec2& c, const Vec2& d) const {
  quad(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
}

#pragma mark Rect

inline void Graphics::rect(Real a, Real b, Real c, Real d) const {
  rect(a, b, c, d, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b) const {
  rect(a.x, a.y, b.x, b.y, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b,
                           Constant mode) const {
  rect(a.x, a.y, b.x, b.y, mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b) const {
  rect(a.x, a.y, b.w, b.h, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b,
                           Constant mode) const {
  rect(a.x, a.y, b.w, b.h, mode);
}

#pragma mark Rounded rect

inline void Graphics::rect(Real a, Real b, Real c, Real d, Real radius) const {
  rect(a, b, c, d, radius, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b, Real radius) const {
  rect(a.x, a.y, b.x, b.y, radius, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b, Real radius,
                           Constant mode) const {
  rect(a.x, a.y, b.x, b.y, radius, mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b, Real radius) const {
  rect(a.x, a.y, b.w, b.h, radius, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b, Real radius,
                           Constant mode) const {
  rect(a.x, a.y, b.w, b.h, radius, mode);
}

#pragma mark Rounded rect with separated radii

inline void Graphics::rect(Real a, Real b, Real c, Real d,
                           Real tl, Real tr, Real br, Real bl) const {
  rect(a, b, c, d, tl, tr, br, bl, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b,
                           Real tl, Real tr, Real br, Real bl) const {
  rect(a.x, a.y, b.x, b.y, tl, tr, br, bl, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Vec2& b,
                           Real tl, Real tr, Real br, Real bl,
                           Constant mode) const {
  rect(a.x, a.y, b.x, b.y, tl, tr, br, bl, mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b,
                           Real tl, Real tr, Real br, Real bl) const {
  rect(a.x, a.y, b.w, b.h, tl, tr, br, bl, style_.rect_mode);
}

inline void Graphics::rect(const Vec2& a, const Size2& b,
                           Real tl, Real tr, Real br, Real bl,
                           Constant mode) const {
  rect(a.x, a.y, b.w, b.h, tl, tr, br, bl, mode);
}

#pragma mark Arc

inline void Graphics::arc(Real a, Real b, Real c, Real d,
                          Real start, Real stop) const {
  arc(a, b, c, d, start, stop, style_.ellipse_mode);
}

inline void Graphics::arc(const Vec2& a, const Vec2& b,
                          Real start, Real stop) const {
  arc(a.x, a.y, b.x, b.y, start, stop, style_.ellipse_mode);
}

inline void Graphics::arc(const Vec2& a, const Vec2& b,
                          Real start, Real stop, Constant mode) const {
  arc(a.x, a.y, b.x, b.y, start, stop, mode);
}

inline void Graphics::arc(const Vec2& a, const Size2& b,
                          Real start, Real stop) const {
  arc(a.x, a.y, b.w, b.h, start, stop, style_.ellipse_mode);
}

inline void Graphics::arc(const Vec2& a, const Size2& b,
                          Real start, Real stop, Constant mode) const {
  arc(a.x, a.y, b.w, b.h, start, stop, mode);
}

#pragma mark Ellipse

inline void Graphics::ellipse(Real a, Real b, Real c, Real d) const {
  ellipse(a, b, c, d, style_.ellipse_mode);
}

inline void Graphics::ellipse(const Vec2& a, const Vec2& b) const {
  ellipse(a.x, a.y, b.x, b.y, style_.ellipse_mode);
}

inline void Graphics::ellipse(const Vec2& a, const Vec2& b,
                              Constant mode) const {
  ellipse(a.x, a.y, b.x, b.y, mode);
}

inline void Graphics::ellipse(const Vec2& a, const Size2& b) const {
  ellipse(a.x, a.y, b.w, b.h, style_.ellipse_mode);
}

inline void Graphics::ellipse(const Vec2& a, const Size2& b,
                              Constant mode) const {
  ellipse(a.x, a.y, b.w, b.h, mode);
}

#pragma mark Shape attributes

inline Constant Graphics::ellipseMode() const {
  return style_.ellipse_mode;
}

inline void Graphics::ellipseMode(Constant mode) {
  style_.ellipse_mode = mode;
}

inline Constant Graphics::rectMode() const {
  return style_.rect_mode;
}

inline void Graphics::rectMode(Constant mode) {
  style_.rect_mode = mode;
}

inline Constant Graphics::strokeCap() const {
  return style_.stroke_cap;
}

inline void Graphics::strokeCap(Constant cap) {
  style_.stroke_cap = cap;
}

inline Constant Graphics::strokeJoin() const {
  return style_.stroke_join;
}

inline void Graphics::strokeJoin(Constant join) {
  style_.stroke_join = join;
}

inline Real Graphics::strokeWeight() const {
  return style_.stroke_weight;
}

inline void Graphics::strokeWeight(Real weight) {
  style_.stroke_weight = weight;
}

#pragma mark Transform

inline void Graphics::applyMatrix(Real n00, Real n01, Real n02,
                                  Real n10, Real n11, Real n12) {
  // TODO(sgss):
}

inline void Graphics::applyMatrix(Real n00, Real n01, Real n02, Real n03,
                                  Real n10, Real n11, Real n12, Real n13,
                                  Real n20, Real n21, Real n22, Real n23,
                                  Real n30, Real n31, Real n32, Real n33) {
  // TODO(sgss):
}

inline void Graphics::applyMatrix(const Vec3& n0, const Vec3& n1) {
  // TODO(sgss):
}

inline void Graphics::applyMatrix(const Vec4& n0, const Vec4& n1,
                                  const Vec4& n2, const Vec4& n3) {
  // TODO(sgss):
}

inline void Graphics::resetMatrix() {
  // TODO(sgss):
}

inline void Graphics::translate(Real x, Real y) {
  translate(x, y, 0.0);
}

inline void Graphics::translate(const Vec2& vector) {
  translate(vector.x, vector.y, 0.0);
}

inline void Graphics::translate(const Vec3& vector) {
  translate(vector.x, vector.y, vector.z);
}

inline void Graphics::scale(Real scalar) {
  scale(scalar, scalar, scalar);
}

inline void Graphics::scale(Real x, Real y) {
  scale(x, y, 1.0);
}

inline void Graphics::scale(const Vec2& vector) {
  scale(vector.x, vector.y, 1.0);
}

inline void Graphics::scale(const Vec3& vector) {
  scale(vector.x, vector.y, vector.z);
}

inline void Graphics::rotate(Real angle, Real x, Real y) {
  // TODO(sgss):
}

inline void Graphics::rotate(Real angle, Real x, Real y, Real z) {
  // TODO(sgss):
}

inline void Graphics::rotate(Real angle, const Vec2& center) {
  // TODO(sgss):
}

inline void Graphics::rotate(Real angle, const Vec3& center) {
  // TODO(sgss):
}

inline void Graphics::rotateX(Real angle) {
  // TODO(sgss):
}

inline void Graphics::rotateY(Real angle) {
  // TODO(sgss):
}

inline void Graphics::rotateZ(Real angle) {
  // TODO(sgss):
}

inline void Graphics::shearX(Real angle) {
  // TODO(sgss):
}

inline void Graphics::shearY(Real angle) {
  // TODO(sgss):
}

#pragma mark Color settings

inline void Graphics::colorMode(Constant mode) {
  style_.color_mode = mode;
}

inline void Graphics::colorMode(Constant mode, Real max) {
  style_.color_mode = mode;
  style_.color_mode_x = max;
  style_.color_mode_y = max;
  style_.color_mode_z = max;
  style_.color_mode_a = max;
}

inline void Graphics::colorMode(Constant mode,
                                Real max1, Real max2, Real max3) {
  style_.color_mode = mode;
  style_.color_mode_x = max1;
  style_.color_mode_y = max2;
  style_.color_mode_z = max3;
}

inline void Graphics::colorMode(Constant mode,
                                Real max1, Real max2, Real max3, Real max4) {
  style_.color_mode = mode;
  style_.color_mode_x = max1;
  style_.color_mode_y = max2;
  style_.color_mode_z = max3;
  style_.color_mode_a = max4;
}

inline void Graphics::fill(Real gray) {
  style_.fill = true;
  style_.fill_color = color(gray);
}

inline void Graphics::fill(Real gray, Real alpha) {
  style_.fill = true;
  style_.fill_color = color(gray, alpha);
}

inline void Graphics::fill(Real v1, Real v2, Real v3) {
  style_.fill = true;
  style_.fill_color = color(v1, v2, v3);
}

inline void Graphics::fill(Real v1, Real v2, Real v3, Real alpha) {
  style_.fill = true;
  style_.fill_color = color(v1, v2, v3, alpha);
}

inline void Graphics::fill(const Color& color) {
  style_.fill = true;
  style_.fill_color = this->color(color);
}

inline void Graphics::fill(const Color& color, Real alpha) {
  style_.fill = true;
  style_.fill_color = this->color(color, alpha);
}

inline void Graphics::noFill() {
  style_.fill = false;
}

inline void Graphics::stroke(Real gray) {
  style_.stroke = true;
  style_.stroke_color = color(gray);
}

inline void Graphics::stroke(Real gray, Real alpha) {
  style_.stroke = true;
  style_.stroke_color = color(gray, alpha);
}

inline void Graphics::stroke(Real v1, Real v2, Real v3) {
  style_.stroke = true;
  style_.stroke_color = color(v1, v2, v3);
}

inline void Graphics::stroke(Real v1, Real v2, Real v3, Real alpha) {
  style_.stroke = true;
  style_.stroke_color = color(v1, v2, v3, alpha);
}

inline void Graphics::stroke(const Color& color) {
  style_.stroke = true;
  style_.stroke_color = this->color(color);
}

inline void Graphics::stroke(const Color& color, Real alpha) {
  style_.stroke = true;
  style_.stroke_color = this->color(color, alpha);
}

inline void Graphics::noStroke() {
  style_.stroke = false;
}

inline void Graphics::background(Real gray) const {
  background(color(gray));
}

inline void Graphics::background(Real gray, Real alpha) const {
  background(color(gray, alpha));
}

inline void Graphics::background(Real v1, Real v2, Real v3) const {
  background(color(v1, v2, v3));
}

inline void Graphics::background(Real v1, Real v2, Real v3, Real alpha) const {
  background(color(v1, v2, v3, alpha));
}

inline void Graphics::background(const Color& color, Real alpha) const {
  background(this->color(color, alpha));
}

#pragma mark Color creation and reading

inline Color Graphics::color(Real value) const {
  if (value > style_.color_mode_x) {
    return Color::Hex(value);
  }
  return Color(math::Clamp(value / style_.color_mode_x, 0.0, 1.0));
}

inline Color Graphics::color(Real value, Real alpha) const {
  const Real a = math::Clamp(alpha / style_.color_mode_a, 0.0, 1.0);
  if (value > style_.color_mode_x) {
    return Color::Hex(value, a);
  }
  return Color(math::Clamp(value / style_.color_mode_x, 0.0, 1.0), a);
}

inline Color Graphics::color(Real v1, Real v2, Real v3) const {
  return Color(math::Clamp<Real>(v1 / style_.color_mode_x, 0.0, 1.0),
               math::Clamp<Real>(v2 / style_.color_mode_y, 0.0, 1.0),
               math::Clamp<Real>(v3 / style_.color_mode_z, 0.0, 1.0));
}

inline Color Graphics::color(Real v1, Real v2, Real v3, Real alpha) const {
  return Color(math::Clamp<Real>(v1 / style_.color_mode_x, 0.0, 1.0),
               math::Clamp<Real>(v2 / style_.color_mode_y, 0.0, 1.0),
               math::Clamp<Real>(v3 / style_.color_mode_z, 0.0, 1.0),
               math::Clamp<Real>(alpha / style_.color_mode_a, 0.0, 1.0));
}

inline Color Graphics::color(const Color& color) const {
  return this->color(color.r, color.g, color.b);
}

inline Color Graphics::color(const Color& color, Real alpha) const {
  return this->color(color.r, color.g, color.b, alpha);
}

inline Real Graphics::red(const Color& color) {
  return color.r * style_.color_mode_x;
}

inline Real Graphics::green(const Color& color) {
  return color.g * style_.color_mode_y;
}

inline Real Graphics::blue(const Color& color) {
  return color.b * style_.color_mode_z;
}

inline Real Graphics::alpha(const Color& color) {
  return color.a * style_.color_mode_a;
}

inline Real Graphics::hue(const Color& color) {
  // TODO(sgss):
  return 0;
}

inline Real Graphics::saturation(const Color& color) {
  // TODO(sgss):
  return 0;
}

inline Real Graphics::brightness(const Color& color) {
  // TODO(sgss):
  return 0;
}

#pragma mark Creating fill and stroke

inline graphics::Fill Graphics::fill() const {
  return graphics::Fill(style_.fill_color);
}

inline graphics::Stroke Graphics::stroke() const {
  auto stroke_cap = graphics::Stroke::Cap::SQUARE;
  auto stroke_join = graphics::Stroke::Join::MITER;
  switch (style_.stroke_cap) {
    case SQUARE:
      stroke_cap = graphics::Stroke::Cap::SQUARE;
      break;
    case PROJECT:
      stroke_cap = graphics::Stroke::Cap::PROJECT;
      break;
    case ROUND:
      stroke_cap = graphics::Stroke::Cap::ROUND;
      break;
    default:
      assert(false);
      break;
  }
  switch (style_.stroke_join) {
    case MITER:
      stroke_join = graphics::Stroke::Join::MITER;
      break;
    case BEVEL:
      stroke_join = graphics::Stroke::Join::BEVEL;
      break;
    case ROUND:
      stroke_join = graphics::Stroke::Join::ROUND;
      break;
    default:
      assert(false);
      break;
  }
  return graphics::Stroke(
      style_.stroke_color, style_.stroke_weight,
      stroke_cap, stroke_join);
}

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_GRAPHICS_H_
