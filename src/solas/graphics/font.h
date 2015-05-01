//
//  solas/graphics/font.h
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
#ifndef SOLAS_GRAPHICS_FONT_H_
#define SOLAS_GRAPHICS_FONT_H_

namespace solas {
namespace graphics {

class Font final {
 public:
  // Constructors
  Font() = default;

  // Copy and assign
  Font(const Font& other) = default;
  Font(Font&& other) = default;
  Font& operator=(const Font& other) = default;
  Font& operator=(Font&& other) = default;

  // Comparison
  bool operator==(const Font& other) const;
  bool operator!=(const Font& other) const;
};

#pragma mark -
#pragma mark Comparison

inline bool Font::operator==(const Font& other) const {
  return &other == this;
}

inline bool Font::operator!=(const Font& other) const {
  return !operator==(other);
}

}  // namespace graphics
}  // namespace solas

#endif  // SOLAS_GRAPHICS_FONT_H_
