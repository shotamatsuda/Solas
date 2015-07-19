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

#include "solas.h"

class App : public solas::Canvas {
 public:
  void setup() override {
    std::cout << "setup" << std::endl;
  }
  void update() override {}
  void pre() override {}
  void draw() override {}
  void post() override {}
  void exit() override {
    std::cout << "exit" << std::endl;
  }
  void mousePressed() override {
    std::cout << "mousePressed" << std::endl;
  }
  void mouseDragged() override {
    std::cout << "mouseDragged" << std::endl;
  }
  void mouseReleased() override {
    std::cout << "mouseReleased" << std::endl;
  }
  void mouseMoved() override {
    std::cout << "mouseMoved" << std::endl;
  }
  void mouseEntered() override {
    std::cout << "mouseEntered" << std::endl;
  }
  void mouseExited() override {
    std::cout << "mouseExited" << std::endl;
  }
  void mouseWheel() override {
    std::cout << "mouseWheel" << std::endl;
  }
  void keyPressed() override {
    std::cout << "keyPressed" << std::endl;
  }
  void keyReleased() override {
    std::cout << "keyReleased" << std::endl;
  }
  void touchesBegan() override {
    std::cout << "touchesBegan" << std::endl;
  }
  void touchesMoved() override {
    std::cout << "touchesMoved" << std::endl;
  }
  void touchesCancelled() override {
    std::cout << "touchesCancelled" << std::endl;
  }
  void touchesEnded() override {
    std::cout << "touchesEnded" << std::endl;
  }
  void gestureBegan() override {
    std::cout << "gestureBegan" << std::endl;
  }
  void gestureChanged() override {
    std::cout << "gestureChanged" << std::endl;
  }
  void gestureCancelled() override {
    std::cout << "gestureCancelled" << std::endl;
  }
  void gestureEnded() override {
    std::cout << "gestureEnded" << std::endl;
  }
  void motionBegan() override {
    std::cout << "motionBegan" << std::endl;
  }
  void motionCancelled() override {
    std::cout << "motionCancelled" << std::endl;
  }
  void motionEnded() override {
    std::cout << "motionEnded" << std::endl;
  }
};

int main(int argc, char **argv) {
  solas::RunOptions options;
  return solas::run<App>(argc, argv, options);
}
