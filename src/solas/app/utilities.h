//
//  solas/app/utilities.h
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
#ifndef SOLAS_APP_UTILITIES_H_
#define SOLAS_APP_UTILITIES_H_

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <initializer_list>
#include <limits>

#include "solas/math/constants.h"
#include "solas/math/functions.h"
#include "solas/math/random.h"
#include "solas/math/size.h"
#include "solas/math/vector.h"

namespace solas {
namespace app {

class Utilities {
 public:
  // Time and date
  static int year();
  static int month();
  static int day();
  static int hour();
  static int minute();
  static int second();

  // Calculation
  static double sq(double n);
  static double sqrt(double n);
  static double pow(double n, double e);
  static double exp(double n);
  static double log(double n);
  static double abs(double n);
  static double floor(double n);
  static double ceil(double n);
  static double round(double n);
  static double lerp(double start, double stop, double amount);
  static double norm(double amount, double start, double stop);
  static double constrain(double value, double min, double max);
  static double map(double value, double min1, double max1,
                    double min2, double max2);
  static double mag(double a, double b);
  static double mag(double a, double b, double c);
  static double mag(double a, double b, double c, double d);
  static double mag(const math::Vec2<double>& v);
  static double mag(const math::Vec3<double>& v);
  static double dist(double x1, double y1, double x2, double y2);
  static double dist(double x1, double y1, double z1,
                     double x2, double y2, double z2);
  static double dist(const math::Vec2<double>& a, const math::Vec2<double>& b);
  static double dist(const math::Vec3<double>& a, const math::Vec3<double>& b);
  static double min(std::initializer_list<double> list);
  static double min(double a, double b);
  static double min(double a, double b, double c);
  static double max(std::initializer_list<double> list);
  static double max(double a, double b);
  static double max(double a, double b, double c);

  // Trigonometry
  static double sin(double value);
  static double cos(double value);
  static double tan(double value);
  static double asin(double value);
  static double acos(double value);
  static double atan(double value);
  static double atan2(double x, double y);
  static double degrees(double radians);
  static double radians(double degrees);

  // Random
  static double noise(double x);
  static double noise(double x, double y);
  static double noise(double x, double y, double z);
  static double noiseDetail(double lod);
  static double noiseDetail(double lod, double falloff);
  static void noiseSeed(double seed);
  static double random(double high);
  static double random(double low, double high);
  static double randomGaussian();
  static void randomSeed(double seed);

 public:
  static constexpr const double E = math::e<double>;
  static constexpr const double PI = math::pi<double>;
  static constexpr const double HALF_PI = math::half_pi<double>;
  static constexpr const double THIRD_PI = math::third_pi<double>;
  static constexpr const double QUARTER_PI = math::quarter_pi<double>;
  static constexpr const double TWO_PI = math::two_pi<double>;
  static constexpr const double TAU = math::two_pi<double>;
};

#pragma mark -

#pragma mark Time and date

inline int Utilities::year() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_year;
}

inline int Utilities::month() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mon + 1;
}

inline int Utilities::day() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mday;
}

inline int Utilities::hour() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_hour;
}

inline int Utilities::minute() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_min;
}

inline int Utilities::second() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_sec;
}

#pragma mark Calculation

inline double Utilities::sq(double n) {
  return n * n;
}

inline double Utilities::sqrt(double n) {
  return std::sqrt(n);
}

inline double Utilities::pow(double n, double e) {
  return std::pow(n, e);
}

inline double Utilities::exp(double n) {
  return std::exp(n);
}

inline double Utilities::log(double n) {
  return std::log(n);
}

inline double Utilities::abs(double n) {
  return std::abs(n);
}

inline double Utilities::floor(double n) {
  return std::floor(n);
}

inline double Utilities::ceil(double n) {
  return std::ceil(n);
}

inline double Utilities::round(double n) {
  return std::round(n);
}

inline double Utilities::lerp(double start, double stop, double amount) {
  return math::Lerp(start, stop, amount);
}

inline double Utilities::norm(double amount, double start, double stop) {
  return math::Norm(amount, start, stop);
}

inline double Utilities::constrain(double value, double min, double max) {
  return math::Clamp(value, min, max);
}

inline double Utilities::map(double value,
                             double min1, double max1,
                             double min2, double max2) {
  return math::Map(value, min1, max1, min2, max2);
}

inline double Utilities::mag(double a, double b) {
  return std::sqrt(a * a + b * b);
}

inline double Utilities::mag(double a, double b, double c) {
  return std::sqrt(a * a + b * b + c * c);
}

inline double Utilities::mag(double a, double b, double c, double d) {
  return std::sqrt(a * a + b * b + c * c + d * d);
}

inline double Utilities::mag(const math::Vec2<double>& v) {
  return v.magnitude();
}

inline double Utilities::mag(const math::Vec3<double>& v) {
  return v.magnitude();
}

inline double Utilities::dist(double x1, double y1, double x2, double y2) {
  return mag(x1 - x2, y1 - y2);
}

inline double Utilities::dist(double x1, double y1,
                              double z1, double x2,
                              double y2, double z2) {
  return mag(x1 - x2, y1 - y2, z1 - z2);
}

inline double Utilities::dist(const math::Vec2<double>& a,
                              const math::Vec2<double>& b) {
  return a.distance(b);
}

inline double Utilities::dist(const math::Vec3<double>& a,
                              const math::Vec3<double>& b) {
  return a.distance(b);
}

inline double Utilities::min(std::initializer_list<double> list) {
  return std::min(list);
}

inline double Utilities::min(double a, double b) {
  return std::min(a, b);
}

inline double Utilities::min(double a, double b, double c) {
  return std::min({a, b, c});
}

inline double Utilities::max(std::initializer_list<double> list) {
  return std::max(list);
}

inline double Utilities::max(double a, double b) {
  return std::max(a, b);
}

inline double Utilities::max(double a, double b, double c) {
  return std::max({a, b, c});
}

#pragma mark Trigonometry

inline double Utilities::sin(double value) {
  return std::sin(value);
}

inline double Utilities::cos(double value) {
  return std::cos(value);
}

inline double Utilities::tan(double value) {
  return std::tan(value);
}

inline double Utilities::asin(double value) {
  return std::asin(value);
}

inline double Utilities::acos(double value) {
  return std::acos(value);
}

inline double Utilities::atan(double value) {
  return std::atan(value);
}

inline double Utilities::atan2(double x, double y) {
  return std::atan2(x, y);
}

inline double Utilities::degrees(double radians) {
  return radians * math::radian<double>;
}

inline double Utilities::radians(double degrees) {
  return degrees * math::degree<double>;
}

#pragma mark Random

inline double Utilities::random(double high) {
  return math::Random<>::Shared().uniform<double>(high);
}

inline double Utilities::random(double low, double high) {
  return math::Random<>::Shared().uniform<double>(low, high);
}

inline double Utilities::randomGaussian() {
  return math::Random<>::Shared().gaussian<double>();
}

inline void Utilities::randomSeed(double seed) {
  math::Random<>::Shared().seed(seed);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_UTILITIES_H_
