//
//  main.mm
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

#include <iostream>

#include "solas/app.h"
#include "solas/processing.h"

class Sketch : public solas::processing::Sketch {
 public:
  void setup() {
    std::cout << "setup" << std::endl;
  }

  void update() {
    std::cout << "update" << std::endl;
  }

  void draw() {
    std::cout << "draw" << std::endl;
  }

  void post() {
    std::cout << "post" << std::endl;
  }

  void exit() {
    std::cout << "exit" << std::endl;
  }

  void mousePressed() {
    std::cout << "mousePressed" << std::endl;
  }

  void mouseDragged() {
    std::cout << "mouseDragged" << std::endl;
  }

  void mouseReleased() {
    std::cout << "mouseReleased" << std::endl;
  }

  void mouseMoved() {
    std::cout << "mouseMoved" << std::endl;
  }

  void mouseEntered() {
    std::cout << "mouseEntered" << std::endl;
  }

  void mouseExited() {
    std::cout << "mouseExited" << std::endl;
  }

  void mouseWheel() {
    std::cout << "mouseWheel" << std::endl;
  }

  void keyPressed() {
    std::cout << "keyPressed" << std::endl;
  }

  void keyReleased() {
    std::cout << "keyReleased" << std::endl;
  }

  void touchesBegan() {
    std::cout << "touchesBegan" << std::endl;
  }

  void touchesMoved() {
    std::cout << "touchesMoved" << std::endl;
  }

  void touchesCancelled() {
    std::cout << "touchesCancelled" << std::endl;
  }

  void touchesEnded() {
    std::cout << "touchesEnded" << std::endl;
  }

  void motionBegan() {
    std::cout << "motionBegan" << std::endl;
  }

  void motionCancelled() {
    std::cout << "motionCancelled" << std::endl;
  }

  void motionEnded() {
    std::cout << "motionEnded" << std::endl;
  }
};

int main(int argc, char **argv) {
  return solas::app::Run<Sketch>(argc, argv);
}
