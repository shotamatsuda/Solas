//
//  solas/layer_framebuffer.cc
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

#include "solas/layer_framebuffer.h"

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

namespace solas {

#pragma mark Using the framebuffer

void LayerFramebuffer::update(GLsizei width, GLsizei height, double scale) {
  width *= scale;
  height *= scale;
  if (width == width_ && height == height_) {
    return;
  }
  width_ = width;
  height_ = height;
  if (!framebuffer_) {
    glGenFramebuffers(1, &framebuffer_);
  }
  GLint framebuffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
  GLint multisample;
  glGetIntegerv(GL_MAX_SAMPLES, &multisample);

  // Color renderbuffer
  if (!color_renderbuffer_) {
    glGenRenderbuffers(1, &color_renderbuffer_);
  }
  glBindRenderbuffer(GL_RENDERBUFFER, color_renderbuffer_);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample,
                                   GL_RGBA, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_RENDERBUFFER, color_renderbuffer_);

  // Depth and stencil renderbuffer
  if (!depth_stencil_renderbuffer_) {
    glGenRenderbuffers(1, &depth_stencil_renderbuffer_);
  }
  glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_renderbuffer_);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample,
                                   GL_DEPTH_STENCIL, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, depth_stencil_renderbuffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void LayerFramebuffer::transfer(GLuint framebuffer) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
  glBlitFramebuffer(GLint(), GLint(), width_, height_,
                    GLint(), GLint(), width_, height_,
                    GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void LayerFramebuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
}

}  // namespace solas
