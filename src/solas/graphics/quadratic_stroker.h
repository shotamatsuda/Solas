//
//  solas/graphics/quadratic_stroker.h
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
#ifndef SOLAS_GRAPHICS_STROKER_H_
#define SOLAS_GRAPHICS_STROKER_H_

#include "solas/graphics/path.h"
#include "solas/graphics/stroke.h"

namespace solas {
namespace graphics {

class QuadraticStroker final {
 public:
  using Real = double;

 public:
  // Constructors
  QuadraticStroker();

  // Copy and assign
  QuadraticStroker(const QuadraticStroker& other) = default;
  QuadraticStroker(QuadraticStroker&& other) = default;
  QuadraticStroker& operator=(const QuadraticStroker& other) = default;
  QuadraticStroker& operator=(QuadraticStroker&& other) = default;

  // Stroking
  Path operator()(const Path& path) const;

  // Comparison
  bool operator==(const QuadraticStroker& other) const;
  bool operator!=(const QuadraticStroker& other) const;

  // Parameters
  Real width() const { return width_; }
  void set_width(Real value) { width_ = value; }
  Real miter() const { return miter_; }
  void set_miter(Real value) { miter_ = value; }
  Stroke::Cap cap() const { return cap_; }
  void set_cap(Stroke::Cap value) { cap_ = value; }
  Stroke::Join join() const { return join_; }
  void set_join(Stroke::Join value) { join_ = value; }
  Real tolerance() const { return tolerance_; }
  void set_tolerance(Real value) { tolerance_ = value; }
  bool simplifies() const { return simplifies_; }
  void set_simplifies(bool value) { simplifies_ = value; }

 private:
  Real width_;
  Real miter_;
  Stroke::Cap cap_;
  Stroke::Join join_;
  Real tolerance_;
  bool simplifies_;
};

#pragma mark -

inline QuadraticStroker::QuadraticStroker()
    : width_(),
      miter_(),
      cap_(Stroke::Cap::BUTT),
      join_(Stroke::Join::MITER),
      tolerance_(1.0),
      simplifies_(false) {}

#pragma mark Comparison

inline bool QuadraticStroker::operator==(const QuadraticStroker& other) const {
  return (width_ == other.width_ &&
          miter_ == other.miter_ &&
          cap_ == other.cap_ &&
          join_ == other.join_ &&
          tolerance_ == other.tolerance_ &&
          simplifies_ == other.simplifies_);
}

inline bool QuadraticStroker::operator!=(const QuadraticStroker& other) const {
  return !operator==(other);
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_STROKER_H_
