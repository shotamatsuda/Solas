//
//  solas/framebuffer.h
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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
#ifndef SOLAS_FRAMEBUFFER_H_
#define SOLAS_FRAMEBUFFER_H_

#include <cstdint>

namespace solas {

class Framebuffer {
 public:
  Framebuffer();

  // Disallow copy semantics
  Framebuffer(const Framebuffer&) = delete;
  Framebuffer& operator=(const Framebuffer&) = delete;

  // Using the framebuffer
  void update(std::int32_t width, std::int32_t height, double scale = 1.0);
  void transfer(std::uint32_t framebuffer);
  void bind();

 private:
  std::int32_t width_;
  std::int32_t height_;
  std::uint32_t framebuffer_;
  std::uint32_t color_renderbuffer_;
  std::uint32_t depth_stencil_renderbuffer_;
};

#pragma mark -

inline Framebuffer::Framebuffer()
    : width_(),
      height_(),
      framebuffer_(),
      color_renderbuffer_(),
      depth_stencil_renderbuffer_() {}

}  // namespace solas

#endif  // SOLAS_FRAMEBUFFER_H_
