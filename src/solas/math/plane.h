//
//  solas/math/plane.h
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
#ifndef SOLAS_MATH_PLANE_H_
#define SOLAS_MATH_PLANE_H_

#include <array>
#include <cassert>
#include <ostream>

#include "solas/math/vector3.h"

namespace solas {
namespace math {

template <typename T>
class Plane final {
 public:
  using Type = T;

 public:
  // Constructors
  Plane();
  Plane(T a, T b, T c, T d);
  Plane(const Vector3<T>& normal, T distance);
  Plane(const Vector3<T>& point, const Vector3<T>& normal);
  Plane(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3);

  // Implicit conversion
  template <typename U>
  Plane(const Plane<U>& other);

  // Copy and assign
  Plane(const Plane& other) = default;
  Plane& operator=(const Plane& other) = default;

  // Mutators
  void set(T a, T b, T c, T d);
  void set(const Vector3<T>& normal, T distance);
  void set(const Vector3<T>& point, const Vector3<T>& normal);
  void set(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3);
  void reset();

  // Comparison
  template <typename U>
  bool operator==(const Plane<U>& other) const;
  template <typename U>
  bool operator!=(const Plane<U>& other) const;

  // Properties
  const Vector3<T>& normal() const { return normal_; }
  void set_normal(const Vector3<T>& value);
  T distance() const { return distance_; }
  void set_distance(T value);

  // Attributes
  bool empty() const { return normal_.empty(); }
  Vector3<T> point() const;
  std::array<T, 4> equation() const;

 private:
  // Hessian normal form
  Vector3<T> normal_;
  T distance_;
};

#pragma mark -

template <typename T>
inline Plane<T>::Plane()
    : distance_() {}

template <typename T>
inline Plane<T>::Plane(T a, T b, T c, T d)
    : distance_() {
  set(a, b, c, d);
}

template <typename T>
inline Plane<T>::Plane(const Vector3<T>& normal, T distance)
    : distance_() {
  set(normal, distance);
}

template <typename T>
inline Plane<T>::Plane(const Vector3<T>& point, const Vector3<T>& normal)
    : distance_() {
  set(point, normal);
}

template <typename T>
inline Plane<T>::Plane(const Vector3<T>& p1,
                       const Vector3<T>& p2,
                       const Vector3<T>& p3)
    : distance_() {
  set(p1, p2, p3);
}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Plane<T>::Plane(const Plane<U>& other)
    : normal_(other.normal_),
      distance_(other.distance_) {}

#pragma mark Mutators

template <typename T>
inline void Plane<T>::set(T a, T b, T c, T d) {
  const Vector3<T> normal(a, b, c);
  assert(!normal.empty());
  normal_ = normal.normalized();
  distance_ = d / normal.length();
}

template <typename T>
inline void Plane<T>::set(const Vector3<T>& normal, T distance) {
  assert(!normal.empty());
  normal_ = normal.normalized();
  distance_ = distance;
}

template <typename T>
inline void Plane<T>::set(const Vector3<T>& point, const Vector3<T>& normal) {
  assert(!normal.empty());
  normal_ = normal.normalized();
  distance_ = normal_.dot(point);
}

template <typename T>
inline void Plane<T>::set(const Vector3<T>& p1,
                          const Vector3<T>& p2,
                          const Vector3<T>& p3) {
  const Vector3<T> normal((p2 - p1).cross(p3 - p1));
  assert(!normal.empty());
  normal_ = normal.normalized();
  distance_ = normal_.dot(p1);
}

template <typename T>
inline void Plane<T>::reset() {
  *this = Plane<T>();
}

#pragma mark Properties

template <typename T>
inline void Plane<T>::set_normal(const Vector3<T>& value) {
  assert(!value.empty());
  normal_ = value;
}

template <typename T>
inline void Plane<T>::set_distance(T value) {
  distance_ = value;
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Plane<T>::operator==(const Plane<U>& other) const {
  return normal_ == other.normal_ && distance_ == other.distance_;
}

template <typename T>
template <typename U>
inline bool Plane<T>::operator!=(const Plane<U>& other) const {
  return !operator==(other);
}

#pragma mark Attributes

template <typename T>
inline Vector3<T> Plane<T>::point() const {
  return normal_ * distance_;
}

template <typename T>
inline std::array<T, 4> Plane<T>::equation() const {
  return std::array<T, 4>{
    normal_.x, normal_.y, normal_.z, -normal_.dot(point())
  };
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Plane<T>& other) {
  return os << "( " << other.normal() << ", " << other.distance() << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_PLANE_H_
