//
//  main.cc
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

#include <iostream>

#include "solas/app.h"
#include "solas/graphics.h"
#include "solas/nanovg.h"

class App : public solas::app::View {
 public:
  solas::nvg::Context context;

 public:
  void setup() {
    context.init();
  }

  void pre() {
    nvgBeginFrame(context, width(), height(), 2);
  }

  void post() {
    nvgEndFrame(context);
  }

  void draw() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void touchesBegan() {
    std::cout << "touchesBegan" << std::endl;
  }

  void touchesMoved(const solas::app::TouchEvent& event) {
    solas::nvg::Scope save;
    nvgFillColor(context, solas::gfx::Color3f::Black());
    for (const auto& touch : event.touches()) {
      nvgBeginPath(context);
      nvgCircle(context, touch.x, touch.y, 20);
      nvgFill(context);
    }
  }

  void touchesCancelled() {
    std::cout << "touchesCancelled" << std::endl;
  }

  void touchesEnded() {
    std::cout << "touchesEnded" << std::endl;
  }

  void gestureBegan(const solas::app::GestureEvent& event) {
    std::cout << "gestureBegan: " << event << std::endl;
  }

  void gestureChanged(const solas::app::GestureEvent& event) {
    std::cout << "gestureChanged: " << event << std::endl;
  }

  void gestureCancelled(const solas::app::GestureEvent& event) {
    std::cout << "gestureCancelled: " << event << std::endl;
  }

  void gestureEnded(const solas::app::GestureEvent& event) {
    std::cout << "gestureEnded: " << event << std::endl;
  }
};

int main(int argc, char **argv) {
  return solas::app::Run<App>(argc, argv);
}
