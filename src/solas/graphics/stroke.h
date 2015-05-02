//
//  solas/graphics/stroke.h
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
#ifndef SOLAS_GRAPHICS_STROKE_H_
#define SOLAS_GRAPHICS_STROKE_H_

#include "solas/graphics/color.h"

namespace solas {
namespace graphics {

class Stroke final {
 public:
  using Real = double;

 public:
  enum class Type {
    NONE,
    SOLID
  };

  enum class Cap {
    BUTT,
    ROUND,
    PROJECT
  };

  enum class Join {
    MITER,
    ROUND,
    BEVEL
  };

 public:
  // Constructors
  Stroke();
  Stroke(const Color4<Real>& color, Real weight);
  Stroke(const Color4<Real>& color, Real weight,
         Stroke::Cap cap, Stroke::Join join);

  // Copy and assign
  Stroke(const Stroke& other) = default;
  Stroke(Stroke&& other) = default;
  Stroke& operator=(const Stroke& other) = default;
  Stroke& operator=(Stroke&& other) = default;

  // Comparison
  bool operator==(const Stroke& other) const;
  bool operator!=(const Stroke& other) const;

  // Conversion
  operator bool() const { return type != Stroke::Type::NONE; }

 public:
  Stroke::Type type;
  Color4<Real> color;
  Real weight;
  Stroke::Cap cap;
  Stroke::Join join;
};

#pragma mark -

inline Stroke::Stroke()
    : type(Stroke::Type::NONE),
      weight(),
      cap(Stroke::Cap::BUTT),
      join(Stroke::Join::MITER) {}

inline Stroke::Stroke(const Color4<Real>& color, Real weight)
    : type(Stroke::Type::SOLID),
      color(color),
      weight(weight),
      cap(Stroke::Cap::BUTT),
      join(Stroke::Join::MITER) {}

inline Stroke::Stroke(const Color4<Real>& color, Real weight,
                      Stroke::Cap cap, Stroke::Join join)
    : type(Stroke::Type::SOLID),
      color(color),
      weight(weight),
      cap(cap),
      join(join) {}

#pragma mark Comparison

inline bool Stroke::operator==(const Stroke& other) const {
  return (type == other.type && weight == other.weight &&
          cap == other.cap && join == other.join);
}

inline bool Stroke::operator!=(const Stroke& other) const {
  return !operator==(other);
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_STROKE_H_
