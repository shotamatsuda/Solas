//
//  solas/graphics/fill.h
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
#ifndef SOLAS_GRAPHICS_FILL_H_
#define SOLAS_GRAPHICS_FILL_H_

#include "solas/graphics/color.h"

namespace solas {
namespace graphics {

enum class FillType {
  NONE,
  SOLID
};

template <typename T>
class Fill {
 public:
  using Type = T;

 public:
  // Constructors
  Fill();
  explicit Fill(const Color4<T>& color);

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
  Color4<T> color;
};

#pragma mark -

template <typename T>
inline Fill<T>::Fill()
    : type(FillType::NONE) {}

template <typename T>
inline Fill<T>::Fill(const Color4<T>& color)
    : type(FillType::SOLID),
      color(color) {}

#pragma mark Comparison

template <typename T>
inline bool Fill<T>::operator==(const Fill& other) const {
  return type == other.type && color == other.color;
}

template <typename T>
inline bool Fill<T>::operator!=(const Fill& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_FILL_H_
