//
//  solas/math/sphere.h
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
#ifndef SOLAS_MATH_SPHERE_H_
#define SOLAS_MATH_SPHERE_H_

#include <ostream>

#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T>
class Sphere final {
 public:
  using Type = T;

 public:
  // Constructors
  Sphere();
  Sphere(const Vector3<T>& center, T radius);

  // Implicit conversion
  template <typename U>
  Sphere(const Sphere<U>& other);

  // Copy and assign
  Sphere(const Sphere& other) = default;
  Sphere& operator=(const Sphere& other) = default;

  // Mutators
  void set(const Vector3<T>& center, T radius);
  void set(const Sphere& other);
  void reset();

  // Comparison
  template <typename U>
  bool operator==(const Sphere<U>& other) const;
  template <typename U>
  bool operator!=(const Sphere<U>& other) const;

  // Properties
  const Vector3<T>& center() const { return center_; }
  void set_center(const Vector3<T>& value);
  T radius() const { return radius_; }
  void set_radius(T value);

  // Attributes
  bool empty() const { return !radius_; }

 private:
  Vector3<T> center_;
  T radius_;
};

#pragma mark -

template <typename T>
inline Sphere<T>::Sphere()
    : radius_() {}

template <typename T>
inline Sphere<T>::Sphere(const Vector3<T>& center, T radius)
    : center_(center),
      radius_(radius) {}

#pragma mark Implicit conversion

template <typename T>
template <typename U>
inline Sphere<T>::Sphere(const Sphere<U>& other)
    : center_(other.center_),
      radius_(other.radius_) {}

#pragma mark Mutators

template <typename T>
inline void Sphere<T>::set(const Vector3<T>& center, T radius) {
  center_ = center;
  radius_ = radius;
}

template <typename T>
inline void Sphere<T>::set(const Sphere& other) {
  *this = other;
}

template <typename T>
inline void Sphere<T>::reset() {
  *this = Sphere<T>();
}

#pragma mark Comparison

template <typename T>
template <typename U>
inline bool Sphere<T>::operator==(const Sphere<U>& other) const {
  return center_ == other.center_ && radius_ == other.radius_;
}

template <typename T>
template <typename U>
inline bool Sphere<T>::operator!=(const Sphere<U>& other) const {
  return !operator==(other);
}

#pragma mark Properties

template <typename T>
inline void Sphere<T>::set_center(const Vector3<T>& value) {
  center_ = value;
}

template <typename T>
inline void Sphere<T>::set_radius(T value) {
  radius_ = value;
}

#pragma mark Stream

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Sphere<T>& other) {
  return os << "( " << other.center() << ", " << other.radius() << " )";
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_SPHERE_H_
