//
//  solas/graphics/fill.h
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
#ifndef SOLAS_GRAPHICS_FILL_H_
#define SOLAS_GRAPHICS_FILL_H_

#include "solas/graphics/color.h"

namespace solas {
namespace graphics {

enum class FillType {
  NONE,
  SOLID
};

class Fill final {
 public:
  using Real = double;

 public:
  // Constructors
  Fill();
  explicit Fill(const Color4<Real>& color);

  // Copy and assign
  Fill(const Fill& other) = default;
  Fill(Fill&& other) = default;
  Fill& operator=(const Fill& other) = default;
  Fill& operator=(Fill&& other) = default;

  // Comparison
  bool operator==(const Fill& other) const;
  bool operator!=(const Fill& other) const;

  // Conversion
  operator bool() const { return type != FillType::NONE; }

 public:
  FillType type;
  Color4<Real> color;
};

#pragma mark -

inline Fill::Fill()
    : type(FillType::NONE) {}

inline Fill::Fill(const Color4<Real>& color)
    : type(FillType::SOLID),
      color(color) {}

#pragma mark Comparison

inline bool Fill::operator==(const Fill& other) const {
  return type == other.type && color == other.color;
}

inline bool Fill::operator!=(const Fill& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_FILL_H_
