//
//  solas/gl/layer_framebuffer.h
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 takram design engineering
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
#ifndef SOLAS_GL_LAYER_FRAMEBUFFER_H_
#define SOLAS_GL_LAYER_FRAMEBUFFER_H_

#include <OpenGL/gltypes.h>

namespace solas {
namespace gl {

class LayerFramebuffer {
 public:
  LayerFramebuffer();

  // Disallow copy semantics
  LayerFramebuffer(const LayerFramebuffer& other) = delete;
  LayerFramebuffer& operator=(const LayerFramebuffer& other) = delete;

  // Using the framebuffer
  void update(GLsizei width, GLsizei height, double scale = 1.0);
  void transfer(GLuint framebuffer);
  void bind();

 private:
  GLsizei width_;
  GLsizei height_;
  GLuint framebuffer_;
  GLuint color_renderbuffer_;
  GLuint depth_stencil_renderbuffer_;
};

#pragma mark -

inline LayerFramebuffer::LayerFramebuffer()
    : width_(),
      height_(),
      framebuffer_(),
      color_renderbuffer_(),
      depth_stencil_renderbuffer_() {}

}  // namespace gl
}  // namespace solas

#endif  // SOLAS_GL_LAYER_FRAMEBUFFER_H_
