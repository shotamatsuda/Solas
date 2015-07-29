//
//  solas/framebuffer.cc
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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

#include "solas/framebuffer.h"

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

namespace solas {

#pragma mark Using the framebuffer

void Framebuffer::update(GLsizei width, GLsizei height, double scale) {
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

void Framebuffer::transfer(GLuint framebuffer) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
  glBlitFramebuffer(GLint(), GLint(), width_, height_,
                    GLint(), GLint(), width_, height_,
                    GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Framebuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
}

}  // namespace solas
