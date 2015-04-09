//
//  solas/app/processing.h
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
#ifndef SOLAS_APP_PROCESSING_H_
#define SOLAS_APP_PROCESSING_H_

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <ctime>
#include <functional>
#include <initializer_list>
#include <list>
#include <memory>
#include <tuple>
#include <vector>

#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"
#include "solas/graphics/color.h"
#include "solas/graphics/fill.h"
#include "solas/graphics/renderer.h"
#include "solas/graphics/stroke.h"
#include "solas/math/constants.h"
#include "solas/math/functions.h"
#include "solas/math/size.h"
#include "solas/math/vector.h"
#include "solas/utility/enablers.h"

namespace solas {
namespace app {

class Processing : public app::Runnable {
 public:
  using Real = double;
  using Color = graphics::Color4<Real>;
  template <int D>
  using Vec = math::Vector<Real, D>;
  using Vec2 = math::Vector2<Real>;
  using Vec3 = math::Vector3<Real>;
  using Vec4 = math::Vector4<Real>;
  template <int D>
  using Size = math::Size<Real, D>;
  using Size2 = math::Size2<Real>;
  using Size3 = math::Size3<Real>;

 private:
  using Real2 = std::tuple<Real, Real>;
  using Real3 = std::tuple<Real, Real, Real>;
  using Real4 = std::tuple<Real, Real, Real, Real>;
  using Real5 = std::tuple<Real, Real, Real, Real, Real>;
  using Real6 = std::tuple<Real, Real, Real, Real, Real, Real>;
  using Real7 = std::tuple<Real, Real, Real, Real, Real, Real, Real>;

 public:
  enum Constant {
    CENTER,
    RADIUS,
    CORNER,
    CORNERS,
    SQUARE,
    PROJECT,
    ROUND,
    MITER,
    BEVEL,
    RGB,
    HSB
  };

 protected:
  struct Style {
    graphics::Fill<Real> fill;
    graphics::Stroke<Real> stroke;
    Constant rect_mode;
    Constant ellipse_mode;
    Constant color_mode;
    Vec4 color_max;
  };

 public:
  // Constructors
  Processing();
  explicit Processing(std::unique_ptr<graphics::Renderer>&& renderer);

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
  static int year();
  static int month();
  static int day();
  static int hour();
  static int minute();
  static int second();
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
  static Real red(const Color& color);
  static Real green(const Color& color);
  static Real blue(const Color& color);
  static Real alpha(const Color& color);
  static Real hue(const Color& color);
  static Real saturation(const Color& color);
  static Real brightness(const Color& color);
  static Color lerpColor(const Color& c1, const Color& c2, Real amount);

  // Math > Calculation
  static Real sq(Real n);
  static Real sqrt(Real n);
  static Real pow(Real n, Real e);
  static Real exp(Real n);
  static Real log(Real n);
  static Real abs(Real n);
  static Real floor(Real n);
  static Real ceil(Real n);
  static Real round(Real n);
  static Real lerp(Real start, Real stop, Real amount);
  static Real norm(Real amount, Real start, Real stop);
  static Real constrain(Real value, Real min, Real max);
  static Real map(Real value, Real min1, Real max1, Real min2, Real max2);
  static Real mag(Real a, Real b);
  static Real mag(Real a, Real b, Real c);
  static Real mag(Real a, Real b, Real c, Real d);
  template <std::size_t D>
  static Real mag(const Vec<D>& v);
  static Real dist(Real x1, Real y1, Real x2, Real y2);
  static Real dist(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2);
  static Real dist(Real x1, Real y1, Real z1, Real w1,
                   Real x2, Real y2, Real z2, Real w2);
  template <std::size_t D>
  static Real dist(const Vec<D>& a, const Vec<D>& b);
  static Real min(std::initializer_list<Real> list);
  static Real min(Real a, Real b);
  static Real min(Real a, Real b, Real c);
  static Real max(std::initializer_list<Real> list);
  static Real max(Real a, Real b);
  static Real max(Real a, Real b, Real c);

  // Math > Trigonometry
  static Real sin(Real value);
  static Real cos(Real value);
  static Real tan(Real value);
  static Real asin(Real value);
  static Real acos(Real value);
  static Real atan(Real value);
  static Real atan2(Real x, Real y);
  static Real degrees(Real radians);
  static Real radians(Real degrees);

 protected:
  // Events
  virtual void mousePressed(const MouseEvent& event);
  virtual void mouseDragged(const MouseEvent& event);
  virtual void mouseReleased(const MouseEvent& event);
  virtual void mouseMoved(const MouseEvent& event);
  virtual void mouseEntered(const MouseEvent& event);
  virtual void mouseExited(const MouseEvent& event);
  virtual void mouseWheel(const MouseEvent& event);
  virtual void keyPressed(const KeyEvent& event);
  virtual void keyReleased(const KeyEvent& event);
  virtual void touchesBegan(const TouchEvent& event);
  virtual void touchesMoved(const TouchEvent& event);
  virtual void touchesCancelled(const TouchEvent& event);
  virtual void touchesEnded(const TouchEvent& event);
  virtual void motionBegan(const MotionEvent& event);
  virtual void motionCancelled(const MotionEvent& event);
  virtual void motionEnded(const MotionEvent& event);

  // Event handlers
  void handleMouseEvent(const MouseEvent& event);
  void handleTouchEvent(const TouchEvent& event);

  // Events intended to override
  virtual void mousePressed() {}
  virtual void mouseDragged() {}
  virtual void mouseReleased() {}
  virtual void mouseMoved() {}
  virtual void mouseEntered() {}
  virtual void mouseExited() {}
  virtual void mouseWheel() {}
  virtual void keyPressed() {}
  virtual void keyReleased() {}
  virtual void touchesBegan() {}
  virtual void touchesMoved() {}
  virtual void touchesCancelled() {}
  virtual void touchesEnded() {}
  virtual void motionBegan() {}
  virtual void motionCancelled() {}
  virtual void motionEnded() {}

 private:
  // Lifecycle overridden from Runnable
  void setup(const AppEvent& event) override;
  void update(const AppEvent& event) override;
  void draw(const AppEvent& event) override;
  void post(const AppEvent& event) override;
  void exit(const AppEvent& event) override;

  // Events overridden from Runnable
  void mouseDown(const MouseEvent& event) override;
  void mouseDrag(const MouseEvent& event) override;
  void mouseUp(const MouseEvent& event) override;
  void mouseMove(const MouseEvent& event) override;
  void mouseEnter(const MouseEvent& event) override;
  void mouseExit(const MouseEvent& event) override;
  void scrollWheel(const MouseEvent& event) override;
  void keyDown(const KeyEvent& event) override;
  void keyUp(const KeyEvent& event) override;
  void touchesBegin(const TouchEvent& event) override;
  void touchesMove(const TouchEvent& event) override;
  void touchesCancel(const TouchEvent& event) override;
  void touchesEnd(const TouchEvent& event) override;
  void motionBegin(const MotionEvent& event) override;
  void motionCancel(const MotionEvent& event) override;
  void motionEnd(const MotionEvent& event) override;

  // Argument conversions
  static Real4 canonicalizeRectArgs(Real a, Real b, Real c, Real d,
                                    Constant mode);

 public:
  // Constants
  static constexpr Real PI = math::pi<Real>;
  static constexpr Real HALF_PI = math::half_pi<Real>;
  static constexpr Real TWO_PI = math::two_pi<Real>;
  static constexpr Real TAU = math::tau<Real>;
  static constexpr Real E = math::e<Real>;

  // Input > Mouse
  union {
    Vec2 mouse;
    struct {
      Real mouse_x;
      Real mouse_y;
    };
  };
  union {
    Vec2 pmouse;
    struct {
      Real pmouse_x;
      Real pmouse_y;
    };
  };
  Constant mouse_button;
  bool mouse_pressed;

  // Input > Keyboard
  char key;
  std::uint32_t key_code;
  bool key_pressed;

 private:
  std::unique_ptr<graphics::Renderer> renderer_;

  // Styles
  Style style_;
  std::list<Style> styles_;

  // Events
  Vec2 dmouse_;
  Vec2 emouse_;
  std::vector<std::function<void()>> event_queue_;

  // Time
  std::chrono::system_clock::time_point started_time_;
};

using P5 = Processing;

#pragma mark -

inline Processing::Processing()
    : Processing(std::unique_ptr<graphics::Renderer>()) {}

#pragma mark Structure

inline void Processing::pushStyle() {
  styles_.emplace_back(style_);
}

inline void Processing::popStyle() {
  style_ = styles_.back();
  styles_.pop_back();
}

#pragma mark Shape > 2D primitive

inline void Processing::point(Real x, Real y) const {
  assert(renderer_);
  renderer_->drawPoint(graphics_context(),
                       style_.fill, style_.stroke,
                       x, y);
}

inline void Processing::point(const Vec2& p) const {
  point(p.x, p.y);
}

inline void Processing::line(Real x1, Real y1, Real x2, Real y2) const {
  assert(renderer_);
  renderer_->drawLine(graphics_context(),
                      style_.fill, style_.stroke,
                      x1, y1, x2, y2);
}

inline void Processing::line(const Vec2& a, const Vec2& b) const {
  line(a.x, a.y, b.x, b.y);
}

inline void Processing::triangle(Real x1, Real y1,
                                 Real x2, Real y2,
                                 Real x3, Real y3) const {
  assert(renderer_);
  renderer_->drawTriangle(graphics_context(),
                          style_.fill, style_.stroke,
                          x1, y1, x2, y2, x3, y3);
}

inline void Processing::triangle(const Vec2& a,
                                 const Vec2& b,
                                 const Vec2& c) const {
  triangle(a.x, a.y, b.x, b.y, c.x, c.y);
}

inline void Processing::quad(Real x1, Real y1, Real x2, Real y2,
                             Real x3, Real y3, Real x4, Real y4) const {
  assert(renderer_);
  renderer_->drawQuad(graphics_context(),
                      style_.fill, style_.stroke,
                      x1, y1, x2, y2, x3, y3, x4, y4);
}

inline void Processing::quad(const Vec2& a, const Vec2& b,
                             const Vec2& c, const Vec2& d) const {
  quad(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
}

inline void Processing::rect(Real a, Real b, Real c, Real d) const {
  rect(a, b, c, d, style_.rect_mode);
}

inline void Processing::rect(Real a, Real b, Real c, Real d, Real r) const {
  rect(a, b, c, d, r, style_.rect_mode);
}

inline void Processing::rect(Real a, Real b, Real c, Real d,
                             Real tl, Real tr, Real br, Real bl) const {
  rect(a, b, c, d, tl, tr, br, bl, style_.rect_mode);
}

inline void Processing::rect(Real a, Real b, Real c, Real d,
                             Constant mode) const {
  assert(renderer_);
  Real x, y, width, height;
  std::tie(x, y, width, height) = canonicalizeRectArgs(a, b, c, d, mode);
  renderer_->drawRect(graphics_context(),
                      style_.fill, style_.stroke,
                      x, y, width, height);
}

inline void Processing::rect(Real a, Real b, Real c, Real d, Real r,
                             Constant mode) const {
  assert(renderer_);
  Real x, y, width, height;
  std::tie(x, y, width, height) = canonicalizeRectArgs(a, b, c, d, mode);
  renderer_->drawRoundedRect(graphics_context(),
                             style_.fill, style_.stroke,
                             x, y, width, height, r);
}

inline void Processing::rect(Real a, Real b, Real c, Real d,
                             Real tl, Real tr, Real br, Real bl,
                             Constant mode) const {
  assert(renderer_);
  Real x, y, width, height;
  std::tie(x, y, width, height) = canonicalizeRectArgs(a, b, c, d, mode);
  renderer_->drawRoundedRect(graphics_context(),
                             style_.fill, style_.stroke,
                             x, y, width, height, tl, tr, br, bl);
}

inline void Processing::rect(const Vec2& a, const Vec2& b) const {
  rect(a.x, a.y, b.x, b.y, style_.rect_mode);
}

inline void Processing::rect(const Vec2& a, const Vec2& b, Real r) const {
  rect(a.x, a.y, b.x, b.y, r, style_.rect_mode);
}

inline void Processing::rect(const Vec2& a, const Vec2& b,
                             Real tl, Real tr, Real br, Real bl) const {
  rect(a.x, a.y, b.x, b.y, tl, tr, br, bl, style_.rect_mode);
}

inline void Processing::rect(const Vec2& a, const Size2& b) const {
  rect(a.x, a.y, b.width, b.height, style_.rect_mode);
}

inline void Processing::rect(const Vec2& a, const Size2& b, Real r) const {
  rect(a.x, a.y, b.width, b.height, r, style_.rect_mode);
}

inline void Processing::rect(const Vec2& a, const Size2& b,
                             Real tl, Real tr, Real br, Real bl) const {
  rect(a.x, a.y, b.width, b.height, tl, tr, br, bl, style_.rect_mode);
}

inline void Processing::arc(Real a, Real b, Real c, Real d,
                            Real start, Real stop) const {
  arc(a, b, c, d, start, stop, style_.ellipse_mode);
}

inline void Processing::arc(Real a, Real b, Real c, Real d,
                            Real start, Real stop, Constant mode) const {
  assert(renderer_);
  Real x, y, width, height;
  std::tie(x, y, width, height) = canonicalizeRectArgs(a, b, c, d, mode);
  renderer_->drawArc(graphics_context(),
                     style_.fill, style_.stroke,
                     x, y, width, height, start, stop);
}

inline void Processing::arc(const Vec2& a, const Vec2& b,
                            Real start, Real stop) const {
  arc(a.x, a.y, b.x, b.y, start, stop, style_.ellipse_mode);
}

inline void Processing::arc(const Vec2& a, const Vec2& b,
                            Real start, Real stop, Constant mode) const {
  arc(a.x, a.y, b.x, b.y, start, stop, mode);
}

inline void Processing::arc(const Vec2& a, const Size2& b,
                            Real start, Real stop) const {
  arc(a.x, a.y, b.width, b.height, start, stop, style_.ellipse_mode);
}

inline void Processing::arc(const Vec2& a, const Size2& b,
                            Real start, Real stop, Constant mode) const {
  arc(a.x, a.y, b.width, b.height, start, stop, mode);
}

inline void Processing::ellipse(Real a, Real b, Real c, Real d) const {
  ellipse(a, b, c, d, style_.ellipse_mode);
}

inline void Processing::ellipse(Real a, Real b, Real c, Real d,
                                Constant mode) const {
  assert(renderer_);
  Real x, y, width, height;
  std::tie(x, y, width, height) = canonicalizeRectArgs(a, b, c, d, mode);
  renderer_->drawEllipse(graphics_context(),
                         style_.fill, style_.stroke,
                         x, y, width, height);
}

inline void Processing::ellipse(const Vec2& a, const Vec2& b) const {
  ellipse(a.x, a.y, b.x, b.y, style_.ellipse_mode);
}

inline void Processing::ellipse(const Vec2& a, const Size2& b) const {
  ellipse(a.x, a.y, b.width, b.height, style_.ellipse_mode);
}

#pragma mark Shape > Attributes

inline void Processing::smooth() {
  assert(renderer_);
  renderer_->enableAntialias(graphics_context());
}

inline void Processing::noSmooth() {
  assert(renderer_);
  renderer_->disableAntialias(graphics_context());
}

inline P5::Constant Processing::ellipseMode() const {
  return style_.ellipse_mode;
}

inline void Processing::ellipseMode(Constant mode) {
  style_.ellipse_mode = mode;
}

inline P5::Constant Processing::rectMode() const {
  return style_.rect_mode;
}

inline void Processing::rectMode(Constant mode) {
  style_.rect_mode = mode;
}

inline P5::Constant Processing::strokeCap() const {
  switch (style_.stroke.cap) {
    case graphics::StrokeCap::SQUARE:
      return SQUARE;
    case graphics::StrokeCap::PROJECT:
      return PROJECT;
    case graphics::StrokeCap::ROUND:
      return ROUND;
    default:
      assert(false);
      break;
  }
  return SQUARE;
}

inline void Processing::strokeCap(Constant cap) {
  switch (cap) {
    case SQUARE:
      style_.stroke.cap = graphics::StrokeCap::SQUARE;
    case PROJECT:
      style_.stroke.cap = graphics::StrokeCap::PROJECT;
    case ROUND:
      style_.stroke.cap = graphics::StrokeCap::ROUND;
    default:
      assert(false);
      break;
  }
}

inline P5::Constant Processing::strokeJoin() const {
  switch (style_.stroke.join) {
    case graphics::StrokeJoin::MITER:
      return MITER;
    case graphics::StrokeJoin::BEVEL:
      return BEVEL;
    case graphics::StrokeJoin::ROUND:
      return ROUND;
    default:
      assert(false);
      break;
  }
  return MITER;
}

inline void Processing::strokeJoin(Constant join) {
  switch (join) {
    case MITER:
      style_.stroke.join = graphics::StrokeJoin::MITER;
    case BEVEL:
      style_.stroke.join = graphics::StrokeJoin::BEVEL;
    case ROUND:
      style_.stroke.join = graphics::StrokeJoin::ROUND;
    default:
      assert(false);
      break;
  }
}

inline P5::Real Processing::strokeWeight() const {
  return style_.stroke.weight;
}

inline void Processing::strokeWeight(Real weight) {
  style_.stroke.weight = weight;
}

#pragma mark -

#pragma mark Input > Time & Date

inline int Processing::year() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_year;
}

inline int Processing::month() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_mon + 1;
}

inline int Processing::day() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_mday;
}

inline int Processing::hour() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_hour;
}

inline int Processing::minute() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_min;
}

inline int Processing::second() {
  using clock = std::chrono::system_clock;
  const auto now = clock::to_time_t(clock::now());
  return std::localtime(&now)->tm_sec;
}

inline std::chrono::milliseconds::rep Processing::millis() const {
  using clock = std::chrono::system_clock;
  using unit = std::chrono::milliseconds;
  return std::chrono::duration_cast<unit>(clock::now() - started_time_).count();
}

#pragma mark -

#pragma mark Color > Setting

inline void Processing::colorMode(Constant mode) {
  style_.color_mode = mode;
}

inline void Processing::colorMode(Constant mode, Real max) {
  style_.color_mode = mode;
  style_.color_max[0] = max;
  style_.color_max[1] = max;
  style_.color_max[2] = max;
  style_.color_max[3] = max;
}

inline void Processing::colorMode(Constant mode,
                                  Real max1, Real max2, Real max3) {
  style_.color_mode = mode;
  style_.color_max[0] = max1;
  style_.color_max[1] = max2;
  style_.color_max[2] = max3;
}

inline void Processing::colorMode(Constant mode,
                                  Real max1, Real max2, Real max3, Real max_a) {
  style_.color_mode = mode;
  style_.color_max[0] = max1;
  style_.color_max[1] = max2;
  style_.color_max[2] = max3;
  style_.color_max[3] = max_a;
}

inline void Processing::fill(Real gray) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = color(gray);
}

inline void Processing::fill(Real gray, Real alpha) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = color(gray, alpha);
}

inline void Processing::fill(Real v1, Real v2, Real v3) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = color(v1, v2, v3);
}

inline void Processing::fill(Real v1, Real v2, Real v3, Real alpha) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = color(v1, v2, v3, alpha);
}

inline void Processing::fill(const Color& color) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = this->color(color);
}

inline void Processing::fill(const Color& color, Real alpha) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = this->color(color, alpha);
}

inline void Processing::noFill() {
  style_.fill.type = graphics::FillType::NONE;
}

inline void Processing::stroke(Real gray) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = color(gray);
}

inline void Processing::stroke(Real gray, Real alpha) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = color(gray, alpha);
}

inline void Processing::stroke(Real v1, Real v2, Real v3) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = color(v1, v2, v3);
}

inline void Processing::stroke(Real v1, Real v2, Real v3, Real alpha) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = color(v1, v2, v3, alpha);
}

inline void Processing::stroke(const Color& color) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = this->color(color);
}

inline void Processing::stroke(const Color& color, Real alpha) {
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = this->color(color, alpha);
}

inline void Processing::noStroke() {
  style_.stroke.type = graphics::StrokeType::NONE;
}

inline void Processing::background(Real gray) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), color(gray));
}

inline void Processing::background(Real gray, Real alpha) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), color(gray, alpha));
}

inline void Processing::background(Real v1, Real v2, Real v3) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), color(v1, v2, v3));
}

inline void Processing::background(Real v1, Real v2, Real v3,
                                   Real alpha) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), color(v1, v2, v3, alpha));
}

inline void Processing::background(const Color& color) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), this->color(color));
}

inline void Processing::background(const Color& color, Real alpha) const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context(), this->color(color, alpha));
}

inline void Processing::clear() const {
  assert(renderer_);
  renderer_->clearBuffer(graphics_context());
}

#pragma mark Color > Creating & Reading

inline P5::Color Processing::color(Real value) const {
  if (value > style_.color_max.front()) {
    return Color::Hex(value);
  }
  const Real v = math::Clamp<Real>(value / style_.color_max.front(), 0, 1);
  return Color(v, v, v);
}

inline P5::Color Processing::color(Real value, Real alpha) const {
  const Real a = math::Clamp<Real>(alpha / style_.color_max.back(), 0, 1);
  if (value > style_.color_max.front()) {
    return Color::Hex(value, a);
  }
  const Real v = math::Clamp<Real>(value / style_.color_max.front(), 0, 1);
  return Color(v, v, v, a);
}

inline P5::Color Processing::color(Real v1, Real v2, Real v3) const {
  auto itr = style_.color_max.begin();
  const Real r = math::Clamp<Real>(v1 / *itr, 0, 1);
  const Real g = math::Clamp<Real>(v2 / *++itr, 0, 1);
  const Real b = math::Clamp<Real>(v3 / *++itr, 0, 1);
  return Color(r, g, b);
}

inline P5::Color Processing::color(Real v1, Real v2, Real v3,
                                   Real alpha) const {
  auto itr = style_.color_max.begin();
  const Real r = math::Clamp<Real>(v1 / *itr, 0, 1);
  const Real g = math::Clamp<Real>(v2 / *++itr, 0, 1);
  const Real b = math::Clamp<Real>(v3 / *++itr, 0, 1);
  const Real a = math::Clamp<Real>(alpha / *++itr, 0, 1);
  return Color(r, g, b, a);
}

inline P5::Color Processing::color(const Color& color) const {
  return this->color(color.r, color.g, color.b);
}

inline P5::Color Processing::color(const Color& color, Real alpha) const {
  return this->color(color.r, color.g, color.b, alpha);
}

inline P5::Real Processing::red(const Color& color) {
  return color.red;
}

inline P5::Real Processing::green(const Color& color) {
  return color.green;
}

inline P5::Real Processing::blue(const Color& color) {
  return color.blue;
}

inline P5::Real Processing::alpha(const Color& color) {
  return color.alpha;
}

inline P5::Real Processing::hue(const Color& color) {
  // TODO:
  return 0;
}

inline P5::Real Processing::saturation(const Color& color) {
  // TODO:
  return 0;
}

inline P5::Real Processing::brightness(const Color& color) {
  // TODO:
  return 0;
}

inline P5::Color Processing::lerpColor(const Color& c1, const Color& c2,
                                       Real amount) {
  // TODO:
  return Color();
}

#pragma mark -

#pragma mark Math > Calculation

inline P5::Real Processing::sq(Real n) {
  return n * n;
}

inline P5::Real Processing::sqrt(Real n) {
  return std::sqrt(n);
}

inline P5::Real Processing::pow(Real n, Real e) {
  return std::pow(n, e);
}

inline P5::Real Processing::exp(Real n) {
  return std::exp(n);
}

inline P5::Real Processing::log(Real n) {
  return std::log(n);
}

inline P5::Real Processing::abs(Real n) {
  return std::abs(n);
}

inline P5::Real Processing::floor(Real n) {
  return std::floor(n);
}

inline P5::Real Processing::ceil(Real n) {
  return std::ceil(n);
}

inline P5::Real Processing::round(Real n) {
  return std::round(n);
}

inline P5::Real Processing::lerp(Real start, Real stop, Real amount) {
  // TODO:
  return 0;
}

inline P5::Real Processing::norm(Real amount, Real start, Real stop) {
  return math::Norm(amount, start, stop);
}

inline P5::Real Processing::constrain(Real value, Real min, Real max) {
  return math::Clamp(value, min, max);
}

inline P5::Real Processing::map(Real value,
                                Real min1, Real max1,
                                Real min2, Real max2) {
  // TODO:
  return 0;
}

inline P5::Real Processing::mag(Real a, Real b) {
  return std::sqrt(a * a + b * b);
}

inline P5::Real Processing::mag(Real a, Real b, Real c) {
  return std::sqrt(a * a + b * b + c * c);
}

inline P5::Real Processing::mag(Real a, Real b, Real c, Real d) {
  return std::sqrt(a * a + b * b + c * c + d * d);
}

template <std::size_t D>
inline P5::Real Processing::mag(const Vec<D>& v) {
  return v.magnitude();
}

inline P5::Real Processing::dist(Real x1, Real y1, Real x2, Real y2) {
  return mag(x1 - x2, y1 - y2);
}

inline P5::Real Processing::dist(Real x1, Real y1, Real z1,
                                 Real x2, Real y2, Real z2) {
  return mag(x1 - x2, y1 - y2, z1 - z2);
}

inline P5::Real Processing::dist(Real x1, Real y1, Real z1, Real w1,
                                 Real x2, Real y2, Real z2, Real w2) {
  return mag(x1 - x2, y1 - y2, z1 - z2, w1 - w2);
}

template <std::size_t D>
inline P5::Real Processing::dist(const Vec<D>& a, const Vec<D>& b) {
  return a.distance(b);
}

inline P5::Real Processing::min(std::initializer_list<Real> list) {
  return std::min(list);
}

inline P5::Real Processing::min(Real a, Real b) {
  return std::min(a, b);
}

inline P5::Real Processing::min(Real a, Real b, Real c) {
  return std::min({a, b, c});
}

inline P5::Real Processing::max(std::initializer_list<Real> list) {
  return std::max(list);
}

inline P5::Real Processing::max(Real a, Real b) {
  return std::max(a, b);
}

inline P5::Real Processing::max(Real a, Real b, Real c) {
  return std::max({a, b, c});
}

#pragma mark Math > Trigonometry

inline P5::Real Processing::sin(Real value) {
  return std::sin(value);
}

inline P5::Real Processing::cos(Real value) {
  return std::cos(value);
}

inline P5::Real Processing::tan(Real value) {
  return std::tan(value);
}

inline P5::Real Processing::asin(Real value) {
  return std::asin(value);
}

inline P5::Real Processing::acos(Real value) {
  return std::acos(value);
}

inline P5::Real Processing::atan(Real value) {
  return std::atan(value);
}

inline P5::Real Processing::atan2(Real x, Real y) {
  return std::atan2(x, y);
}

inline P5::Real Processing::degrees(Real radians) {
  return radians * math::radian<Real>;
}

inline P5::Real Processing::radians(Real degrees) {
  return degrees * math::degree<Real>;
}

#pragma mark -

#pragma mark Lifecycle overridden from Runnable

inline void Processing::setup(const AppEvent& event) {
  Runnable::setup(event);
}

inline void Processing::update(const AppEvent& event) {
  Runnable::update(event);
}

inline void Processing::draw(const AppEvent& event) {
  Runnable::draw(event);
  for (const auto& callback : event_queue_) {
    callback();
  }
  event_queue_.clear();
}

inline void Processing::post(const AppEvent& event) {
  Runnable::post(event);
}

inline void Processing::exit(const AppEvent& event) {
  Runnable::exit(event);
}

#pragma mark Events overridden from Runnable

inline void Processing::mouseDown(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mousePressed), this, event));
}

inline void Processing::mouseDrag(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseDragged), this, event));
}

inline void Processing::mouseUp(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseReleased), this, event));
}

inline void Processing::mouseMove(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseMoved), this, event));
}

inline void Processing::mouseEnter(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseEntered), this, event));
}

inline void Processing::mouseExit(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseExited), this, event));
}

inline void Processing::scrollWheel(const MouseEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MouseEvent&)>(
          &Processing::mouseWheel), this, event));
}

inline void Processing::keyDown(const KeyEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const KeyEvent&)>(
          &Processing::keyPressed), this, event));
}

inline void Processing::keyUp(const KeyEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const KeyEvent&)>(
          &Processing::keyReleased), this, event));
}

inline void Processing::touchesBegin(const TouchEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const TouchEvent&)>(
          &Processing::touchesBegan), this, event));
}

inline void Processing::touchesMove(const TouchEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const TouchEvent&)>(
          &Processing::touchesMoved), this, event));
}

inline void Processing::touchesCancel(const TouchEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const TouchEvent&)>(
          &Processing::touchesCancelled), this, event));
}

inline void Processing::touchesEnd(const TouchEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const TouchEvent&)>(
          &Processing::touchesEnded), this, event));
}

inline void Processing::motionBegin(const MotionEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MotionEvent&)>(
          &Processing::motionBegan), this, event));
}

inline void Processing::motionCancel(const MotionEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MotionEvent&)>(
          &Processing::motionCancelled), this, event));
}

inline void Processing::motionEnd(const MotionEvent& event) {
  event_queue_.emplace_back(std::bind(
      static_cast<void (Processing::*)(const MotionEvent&)>(
          &Processing::motionEnded), this, event));
}

#pragma mark Events

inline void Processing::mousePressed(const MouseEvent& event) {
  mousePressed();
}

inline void Processing::mouseDragged(const MouseEvent& event) {
  mouseDragged();
}

inline void Processing::mouseReleased(const MouseEvent& event) {
  mouseReleased();
}

inline void Processing::mouseMoved(const MouseEvent& event) {
  mouseMoved();
}

inline void Processing::mouseEntered(const MouseEvent& event) {
  mouseEntered();
}

inline void Processing::mouseExited(const MouseEvent& event) {
  mouseExited();
}

inline void Processing::mouseWheel(const MouseEvent& event) {
  mouseWheel();
}

inline void Processing::keyPressed(const KeyEvent& event) {
  keyPressed();
}

inline void Processing::keyReleased(const KeyEvent& event) {
  keyReleased();
}

inline void Processing::touchesBegan(const TouchEvent& event) {
  touchesBegan();
}

inline void Processing::touchesMoved(const TouchEvent& event) {
  touchesMoved();
}

inline void Processing::touchesCancelled(const TouchEvent& event) {
  touchesCancelled();
}

inline void Processing::touchesEnded(const TouchEvent& event) {
  touchesEnded();
}

inline void Processing::motionBegan(const MotionEvent& event) {
  motionBegan();
}

inline void Processing::motionCancelled(const MotionEvent& event) {
  motionCancelled();
}

inline void Processing::motionEnded(const MotionEvent& event) {
  motionEnded();
}

#pragma mark Argument conversions

inline P5::Real4 Processing::canonicalizeRectArgs(
    Real a, Real b, Real c, Real d, Constant mode) {
  switch (mode) {
    case Constant::CENTER:
      return std::make_tuple(a - c / 2, b - d / 2, c, d);
    case Constant::RADIUS:
      return std::make_tuple(a - c, b - d, c * 2, d * 2);
    case Constant::CORNER:
      return std::make_tuple(a, b, c, d);
    case Constant::CORNERS: {
      const auto x = std::min(a, c);
      const auto y = std::min(b, d);
      return std::make_tuple(x, y, std::max(a, c) - x, std::max(b, d) - y);
    }
    default:
      assert(false);
      break;
  }
  return std::make_tuple(a, b, c, d);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_PROCESSING_H_
