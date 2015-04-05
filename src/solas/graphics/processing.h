//
//  solas/graphics/processing.h
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
#ifndef SOLAS_GRAPHICS_PROCESSING_H_
#define SOLAS_GRAPHICS_PROCESSING_H_

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <ctime>
#include <initializer_list>

#include "solas/math/constants.h"
#include "solas/math/size.h"
#include "solas/math/vector.h"

namespace solas {
namespace graphics {

template <typename Renderer, typename Real = double>
class Processing {
 public:
  template <std::size_t Dimension>
  using Vec = math::Vector<Dimension, Real>;
  using Vec2 = math::Vector2<Real>;
  using Vec3 = math::Vector3<Real>;
  using Vec4 = math::Vector4<Real>;
  using Size2 = math::Size2<Real>;
  using Size3 = math::Size3<Real>;

 public:
  enum class RectMode {
    CENTER,
    RADIUS,
    CORNER,
    CORNERS
  };
  enum class EllipseMode {
    CENTER,
    RADIUS,
    CORNER,
    CORNERS
  };
  enum class StrokeCap {
    SQUARE,
    PROJECT,
    ROUND
  };
  enum class StrokeJoin {
    MITER,
    BEVEL,
    ROUND
  };

 public:
  // Constructors
  Processing();
  virtual ~Processing() = 0;

  // Shape / 2D primitive
  void point(Real x, Real y) const;
  void point(const Vec2& p) const;
  void line(Real x1, Real y1, Real x2, Real y2) const;
  void line(const Vec2& p1, const Vec2& p2) const;
  void triangle(Real x1, Real y1, Real x2, Real y2, Real x3, Real y3) const;
  void triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3) const;
  void quad(Real x1, Real y1, Real x2, Real y2,
            Real x3, Real y3, Real x4, Real y4) const;
  void quad(const Vec2& p1, const Vec2& p2,
            const Vec2& p3, const Vec2& p4) const;
  void rect(Real a, Real b, Real c, Real d) const;
  void rect(Real a, Real b, Real c, Real d, Real r) const;
  void rect(Real a, Real b, Real c, Real d,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(const Vec2& p1, const Vec2& p2) const;
  void rect(const Vec2& p1, const Vec2& p2, Real r) const;
  void rect(const Vec2& p1, const Vec2& p2,
            Real tl, Real tr, Real br, Real bl) const;
  void rect(const Vec2& p, const Size2& s) const;
  void rect(const Vec2& p, const Size2& s, Real r) const;
  void rect(const Vec2& p, const Size2& s,
            Real tl, Real tr, Real br, Real bl) const;
  void arc(Real a, Real b, Real c, Real d,
           Real start, Real stop) const;
  void arc(Real a, Real b, Real c, Real d,
           Real start, Real stop, EllipseMode mode) const;
  void arc(const Vec2& p1, const Vec2& p2,
           Real start, Real stop) const;
  void arc(const Vec2& p1, const Vec2& p2,
           Real start, Real stop, EllipseMode mode) const;
  void arc(const Vec2& p, const Size2& s,
           Real start, Real stop) const;
  void arc(const Vec2& p, const Size2& s,
           Real start, Real stop, EllipseMode mode) const;
  void ellipse(Real a, Real b, Real c, Real d) const;
  void ellipse(const Vec2& p1, const Vec2& p2) const;
  void ellipse(const Vec2& p, const Size2& s) const;

  // Shape / Attributes
  void smooth();
  void noSmooth();
  Real strokeWeight() const;
  void strokeWeight(Real weight);
  StrokeCap strokeCap() const;
  void strokeCap(StrokeCap cap);
  StrokeJoin strokeJoin() const;
  void strokeJoin(StrokeJoin join);
  RectMode rectMode() const;
  void rectMode(RectMode mode);
  EllipseMode ellipseMode() const;
  void ellipseMode(EllipseMode mode);

  // Transform
  template <typename Source>
  void applyMatrix(const Source& source);
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

  // Input / Time & Date
  static int year();
  static int month();
  static int day();
  static int hour();
  static int minute();
  static int second();
  std::chrono::milliseconds::rep millis() const;

  // Math / Calculation
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
  static Real constrain(Real amount, Real low, Real high);
  static Real norm(Real value, Real start, Real stop);
  static Real map(Real value, Real start1, Real stop1, Real start2, Real stop2);
  static Real mag(Real a, Real b);
  static Real mag(Real a, Real b, Real c);
  static Real mag(Real a, Real b, Real c, Real d);
  template <std::size_t Dimension>
  static Real mag(const Vec<Dimension>& v);
  static Real dist(Real x1, Real y1, Real x2, Real y2);
  static Real dist(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2);
  static Real dist(Real x1, Real y1, Real z1, Real w1,
                   Real x2, Real y2, Real z2, Real w2);
  template <std::size_t Dimension>
  static Real dist(const Vec<Dimension>& a, const Vec<Dimension>& b);
  static Real min(std::initializer_list<Real> list);
  static Real min(Real a, Real b);
  static Real min(Real a, Real b, Real c);
  static Real max(std::initializer_list<Real> list);
  static Real max(Real a, Real b);
  static Real max(Real a, Real b, Real c);

  // Math / Trigonometry
  static Real sin(Real value);
  static Real cos(Real value);
  static Real tan(Real value);
  static Real asin(Real value);
  static Real acos(Real value);
  static Real atan(Real value);
  static Real atan2(Real x, Real y);
  static Real degrees(Real radians);
  static Real radians(Real degrees);

 public:
  // Constants
  static constexpr Real PI = math::PI<Real>;
  static constexpr Real HALF_PI = math::HALF_PI<Real>;
  static constexpr Real TWO_PI = math::TWO_PI<Real>;
  static constexpr Real TAU = math::TAU<Real>;
  static constexpr Real E = math::E<Real>;

 private:
  Renderer renderer_;

  // Attributes
  Real stroke_weight_;
  StrokeCap stroke_cap_;
  StrokeJoin stroke_join_;
  RectMode rect_mode_;
  EllipseMode ellipse_mode_;

  // Time & Date
  std::chrono::system_clock::time_point started_time_;
};

#pragma mark -

template <typename Renderer, typename Real>
inline Processing<Renderer, Real>::Processing()
    : stroke_weight_(1),
      stroke_cap_(StrokeCap::ROUND),
      stroke_join_(StrokeJoin::MITER),
      rect_mode_(RectMode::CORNER),
      ellipse_mode_(EllipseMode::CORNER),
      started_time_(std::chrono::system_clock::now()) {}

#pragma mark Shape / 2D primitive

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    Real a, Real b, Real c, Real d, Real start, Real stop) const {
  renderer_.arc(a, b, c, d, start, stop, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    Real a, Real b, Real c, Real d, Real start, Real stop,
    EllipseMode mode) const {
  renderer_.arc(a, b, c, d, start, stop, mode);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    const Vec2& p1, const Vec2& p2, Real start, Real stop) const {
  renderer_.arc(p1.x, p1.y, p2.x, p2.y, start, stop, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    const Vec2& p1, const Vec2& p2, Real start, Real stop,
    EllipseMode mode) const {
  renderer_.arc(p1.x, p1.y, p2.x, p2.y, start, stop, mode);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    const Vec2& p, const Size2& s, Real start, Real stop) const {
  renderer_.arc(p.x, p.y, s.width, s.height, start, stop, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::arc(
    const Vec2& p, const Size2& s, Real start, Real stop,
    EllipseMode mode) const {
  renderer_.arc(p.x, p.y, s.width, s.height, start, stop, mode);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::ellipse(
    Real a, Real b, Real c, Real d) const {
  renderer_.ellipse(a, b, c, d, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::ellipse(
    const Vec2& p1, const Vec2& p2) const {
  renderer_.ellipse(p1.x, p1.y, p2.x, p2.y, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::ellipse(
    const Vec2& p, const Size2& s) const {
  renderer_.ellipse(p.x, p.y, s.width, s.height, ellipse_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::line(
    Real x1, Real y1, Real x2, Real y2) const {
  renderer_.line(x1, y1, x2, y2);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::line(
    const Vec2& p1, const Vec2& p2) const {
  renderer_.line(p1.x, p1.y, p2.x, p2.y);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::point(Real x, Real y) const {
  renderer_.point(x, y);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::point(const Vec2& p) const {
  renderer_.point(p.x, p.y);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::quad(
    Real x1, Real y1, Real x2, Real y2,
    Real x3, Real y3, Real x4, Real y4) const {
  renderer_.quad(x1, y1, x2, y2, x3, y3, x4, y4);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::quad(
    const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4) const {
  renderer_.quad(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    Real a, Real b, Real c, Real d) const {
  renderer_.rect(a, b, c, d, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    Real a, Real b, Real c, Real d, Real r) const {
  renderer_.rect(a, b, c, d, r, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    Real a, Real b, Real c, Real d, Real tl, Real tr, Real br, Real bl) const {
  renderer_.rect(a, b, c, d, tl, tr, br, bl, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p1, const Vec2& p2) const {
  renderer_.rect(p1.x, p1.y, p2.x, p2.y, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p1, const Vec2& p2, Real r) const {
  renderer_.rect(p1.x, p1.y, p2.x, p2.y, r, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p1, const Vec2& p2, Real tl, Real tr, Real br, Real bl) const {
  renderer_.rect(p1.x, p1.y, p2.x, p2.y, tl, tr, br, bl, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p, const Size2& s) const {
  renderer_.rect(p.x, p.y, s.width, s.height, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p, const Size2& s, Real r) const {
  renderer_.rect(p.x, p.y, s.width, s.height, r, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rect(
    const Vec2& p, const Size2& s, Real tl, Real tr, Real br, Real bl) const {
  renderer_.rect(p.x, p.y, s.width, s.height, tl, tr, br, bl, rect_mode_);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::triangle(
    Real x1, Real y1, Real x2, Real y2, Real x3, Real y3) const {
  renderer_.triangle(x1, y1, x2, y2, x3, y3);
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::triangle(
    const Vec2& p1, const Vec2& p2, const Vec2& p3) const {
  renderer_.triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

#pragma mark Shape / Attributes

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::smooth() {
  renderer_.smooth();
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::noSmooth() {
  renderer_.noSmooth();
}

template <typename Renderer, typename Real>
inline typename Processing<Renderer, Real>::EllipseMode
    Processing<Renderer, Real>::ellipseMode() const {
  return ellipse_mode_;
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::ellipseMode(EllipseMode mode) {
  ellipse_mode_ = mode;
}

template <typename Renderer, typename Real>
inline typename Processing<Renderer, Real>::RectMode
    Processing<Renderer, Real>::rectMode() const {
  return rect_mode_;
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::rectMode(RectMode mode) {
  rect_mode_ = mode;
}

template <typename Renderer, typename Real>
inline typename Processing<Renderer, Real>::StrokeCap
    Processing<Renderer, Real>::strokeCap() const {
  return stroke_cap_;
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::strokeCap(StrokeCap cap) {
  stroke_cap_ = cap;
}

template <typename Renderer, typename Real>
inline typename Processing<Renderer, Real>::StrokeJoin
    Processing<Renderer, Real>::strokeJoin() const {
  return stroke_join_;
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::strokeJoin(StrokeJoin join) {
  stroke_join_ = join;
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::strokeWeight() const {
  return stroke_weight_;
}

template <typename Renderer, typename Real>
inline void Processing<Renderer, Real>::strokeWeight(Real weight) {
  stroke_weight_ = weight;
}

#pragma mark -

#pragma mark Input / Time & Date

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::year() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_year;
}

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::month() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_mon + 1;
}

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::day() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_mday;
}

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::hour() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_hour;
}

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::minute() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_min;
}

template <typename Renderer, typename Real>
inline int Processing<Renderer, Real>::second() {
  const auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  return std::localtime(&now)->tm_sec;
}

template <typename Renderer, typename Real>
inline std::chrono::milliseconds::rep
    Processing<Renderer, Real>::millis() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - started_time_);
}

#pragma mark -

#pragma mark Math / Calculation

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::sq(Real n) {
  return n * n;
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::sqrt(Real n) {
  return std::sqrt(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::pow(Real n, Real e) {
  return std::pow(n, e);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::exp(Real n) {
  return std::exp(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::log(Real n) {
  return std::log(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::abs(Real n) {
  return std::abs(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::floor(Real n) {
  return std::floor(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::ceil(Real n) {
  return std::ceil(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::round(Real n) {
  return std::round(n);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::lerp(
    Real start, Real stop, Real amount) {
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::constrain(
    Real amount, Real low, Real high) {
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::norm(
    Real value, Real start, Real stop) {
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::map(
    Real value, Real start1, Real stop1, Real start2, Real stop2) {
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::mag(Real a, Real b) {
  return std::sqrt(a * a + b * b);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::mag(Real a, Real b, Real c) {
  return std::sqrt(a * a + b * b + c * c);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::mag(Real a, Real b, Real c, Real d) {
  return std::sqrt(a * a + b * b + c * c + d * d);
}

template <typename Renderer, typename Real>
template <std::size_t Dimension>
inline Real Processing<Renderer, Real>::mag(const Vec<Dimension>& v) {
  return v.magnitude();
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::dist(
    Real x1, Real y1, Real x2, Real y2) {
  return mag(x1 - x2, y1 - y2);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::dist(
    Real x1, Real y1, Real z1, Real x2, Real y2, Real z2) {
  return mag(x1 - x2, y1 - y2, z1 - z2);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::dist(
    Real x1, Real y1, Real z1, Real w1, Real x2, Real y2, Real z2, Real w2) {
  return mag(x1 - x2, y1 - y2, z1 - z2, w1 - w2);
}

template <typename Renderer, typename Real>
template <std::size_t Dimension>
inline Real Processing<Renderer, Real>::dist(
    const Vec<Dimension>& a, const Vec<Dimension>& b) {
  return a.distance(b);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::min(std::initializer_list<Real> list) {
  return std::min(list);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::min(Real a, Real b) {
  return std::min(a, b);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::min(Real a, Real b, Real c) {
  return std::min({a, b, c});
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::max(std::initializer_list<Real> list) {
  return std::max(list);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::max(Real a, Real b) {
  return std::max(a, b);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::max(Real a, Real b, Real c) {
  return std::max({a, b, c});
}

#pragma mark Math / Trigonometry

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::sin(Real value) {
  return std::sin(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::cos(Real value) {
  return std::cos(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::tan(Real value) {
  return std::tan(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::asin(Real value) {
  return std::asin(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::acos(Real value) {
  return std::acos(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::atan(Real value) {
  return std::atan(value);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::atan2(Real x, Real y) {
  return std::atan2(x, y);
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::degrees(Real radians) {
  return radians * math::RADIAN<Real>;
}

template <typename Renderer, typename Real>
inline Real Processing<Renderer, Real>::radians(Real degrees) {
  return degrees * math::DEGREE<Real>;
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_PROCESSING_H_
