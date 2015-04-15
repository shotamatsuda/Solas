//
//  main_touch.cc
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

#define NANOVG_GLES3_IMPLEMENTATION

#include <OpenGLES/ES3/gl.h>

#include "nanovg.h"
#include "nanovg_gl.h"
#include "solas/app.h"

class App : public solas::app::View {
 public:
  void setup() {
    context = nvgCreateGLES3(NVG_DEBUG);
  }

  void draw() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nvgBeginFrame(context, width(), height(), width() / height());
    nvgStrokeColor(context, nvgRGBAf(0,0,0, 0.3));
    nvgStrokeWidth(context, 1);
    for (int i = 0; i < 1000; ++i) {
      nvgBeginPath(context);
      nvgMoveTo(context, random(width()), random(height()));
      nvgLineTo(context, random(width()), random(height()));
      nvgStroke(context);
    }
    nvgEndFrame(context);
  }

  NVGcontext *context;
};

int main(int argc, char **argv) {
  return solas::app::Run<App>(argc, argv);
}
