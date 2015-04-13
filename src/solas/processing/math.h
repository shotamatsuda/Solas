//
//  solas/processing/math.h
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
#ifndef SOLAS_PROCESSING_MATH_H_
#define SOLAS_PROCESSING_MATH_H_

#include <algorithm>
#include <cmath>
#include <initializer_list>

#include "solas/math/constants.h"
#include "solas/math/functions.h"
#include "solas/math/random.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

// Calculation
Real sq(Real n);
Real sqrt(Real n);
Real pow(Real n, Real e);
Real exp(Real n);
Real log(Real n);
Real abs(Real n);
Real floor(Real n);
Real ceil(Real n);
Real round(Real n);
Real lerp(Real start, Real stop, Real amount);
Real norm(Real amount, Real start, Real stop);
Real constrain(Real value, Real min, Real max);
Real map(Real value, Real min1, Real max1, Real min2, Real max2);
Real mag(Real a, Real b);
Real mag(Real a, Real b, Real c);
Real mag(Real a, Real b, Real c, Real d);
Real mag(const Vec2& v);
Real mag(const Vec3& v);
Real dist(Real x1, Real y1, Real x2, Real y2);
Real dist(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2);
Real dist(const Vec2& a, const Vec2& b);
Real dist(const Vec3& a, const Vec3& b);
Real min(std::initializer_list<Real> list);
Real min(Real a, Real b);
Real min(Real a, Real b, Real c);
Real max(std::initializer_list<Real> list);
Real max(Real a, Real b);
Real max(Real a, Real b, Real c);

// Trigonometry
Real sin(Real value);
Real cos(Real value);
Real tan(Real value);
Real asin(Real value);
Real acos(Real value);
Real atan(Real value);
Real atan2(Real x, Real y);
Real degrees(Real radians);
Real radians(Real degrees);

// Random
Real noise(Real x);
Real noise(Real x, Real y);
Real noise(Real x, Real y, Real z);
Real noiseDetail(Real lod);
Real noiseDetail(Real lod, Real falloff);
void noiseSeed(Real seed);
Real random(Real high);
Real random(Real low, Real high);
Real randomGaussian();
void randomSeed(Real seed);

#pragma mark -

#pragma mark Calculation

inline Real sq(Real n) {
  return n * n;
}

inline Real sqrt(Real n) {
  return std::sqrt(n);
}

inline Real pow(Real n, Real e) {
  return std::pow(n, e);
}

inline Real exp(Real n) {
  return std::exp(n);
}

inline Real log(Real n) {
  return std::log(n);
}

inline Real abs(Real n) {
  return std::abs(n);
}

inline Real floor(Real n) {
  return std::floor(n);
}

inline Real ceil(Real n) {
  return std::ceil(n);
}

inline Real round(Real n) {
  return std::round(n);
}

inline Real lerp(Real start, Real stop, Real amount) {
  return math::Lerp(start, stop, amount);
}

inline Real norm(Real amount, Real start, Real stop) {
  return math::Norm(amount, start, stop);
}

inline Real constrain(Real value, Real min, Real max) {
  return math::Clamp(value, min, max);
}

inline Real map(Real value, Real min1, Real max1, Real min2, Real max2) {
  return math::Map(value, min1, max1, min2, max2);
}

inline Real mag(Real a, Real b) {
  return std::sqrt(a * a + b * b);
}

inline Real mag(Real a, Real b, Real c) {
  return std::sqrt(a * a + b * b + c * c);
}

inline Real mag(Real a, Real b, Real c, Real d) {
  return std::sqrt(a * a + b * b + c * c + d * d);
}

inline Real mag(const Vec2& v) {
  return v.magnitude();
}

inline Real mag(const Vec3& v) {
  return v.magnitude();
}

inline Real dist(Real x1, Real y1, Real x2, Real y2) {
  return mag(x1 - x2, y1 - y2);
}

inline Real dist(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2) {
  return mag(x1 - x2, y1 - y2, z1 - z2);
}

inline Real dist(const Vec2& a, const Vec2& b) {
  return a.distance(b);
}

inline Real dist(const Vec3& a, const Vec3& b) {
  return a.distance(b);
}

inline Real min(std::initializer_list<Real> list) {
  return std::min(list);
}

inline Real min(Real a, Real b) {
  return std::min(a, b);
}

inline Real min(Real a, Real b, Real c) {
  return std::min({a, b, c});
}

inline Real max(std::initializer_list<Real> list) {
  return std::max(list);
}

inline Real max(Real a, Real b) {
  return std::max(a, b);
}

inline Real max(Real a, Real b, Real c) {
  return std::max({a, b, c});
}

#pragma mark Trigonometry

inline Real sin(Real value) {
  return std::sin(value);
}

inline Real cos(Real value) {
  return std::cos(value);
}

inline Real tan(Real value) {
  return std::tan(value);
}

inline Real asin(Real value) {
  return std::asin(value);
}

inline Real acos(Real value) {
  return std::acos(value);
}

inline Real atan(Real value) {
  return std::atan(value);
}

inline Real atan2(Real x, Real y) {
  return std::atan2(x, y);
}

inline Real degrees(Real radians) {
  return radians * math::radian<Real>;
}

inline Real radians(Real degrees) {
  return degrees * math::degree<Real>;
}

#pragma mark Random

inline Real random(Real high) {
  return math::Random<>::Shared().uniform<Real>(high);
}

inline Real random(Real low, Real high) {
  return math::Random<>::Shared().uniform<Real>(low, high);
}

inline Real randomGaussian() {
  return math::Random<>::Shared().gaussian<Real>();
}

inline void randomSeed(Real seed) {
  math::Random<>::Shared().seed(seed);
}

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_MATH_H_
