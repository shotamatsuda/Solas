//
//  solas/graphics/shape.h
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
#ifndef SOLAS_GRAPHICS_SHAPE_H_
#define SOLAS_GRAPHICS_SHAPE_H_

namespace solas {
namespace graphics {

class Shape final {
 public:
  // Constructors
  Shape() = default;

  // Copy and assign
  Shape(const Shape& other) = default;
  Shape(Shape&& other) = default;
  Shape& operator=(const Shape& other) = default;
  Shape& operator=(Shape&& other) = default;

  // Comparison
  bool operator==(const Shape& other) const;
  bool operator!=(const Shape& other) const;

 private:
  // Properties
};

#pragma mark -
#pragma mark Comparison

inline bool Shape::operator==(const Shape& other) const {
  return &other == this;
}

inline bool Shape::operator!=(const Shape& other) const {
  return !operator==(other);
}

}  // namespace graphics

namespace gfx = graphics;

}  // namespace solas

#endif  // SOLAS_GRAPHICS_SHAPE_H_
