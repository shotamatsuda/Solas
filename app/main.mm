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

#import <Cocoa/Cocoa.h>

#include <list>
#include <iostream>

#include "solas/math.h"
#include "solas/thread.h"
#include "solas/graphics/processing.h"

int main(int argc, const char * argv[]) {
  using namespace solas::math;
  using namespace solas::graphics;

  {
    Triangle2<double> p1({1,2,3,4});
    std::cout << p1 << std::endl;
    Triangle2<double> p2({{1,2},{3,4}});
    std::cout << p2 << std::endl;
    Triangle2<double> p3(std::vector<double>{1,2,3,4});
    std::cout << p3 << std::endl;
    Triangle2<double> p4(std::vector<Vec2d>{{1,2},{3,4}});
    std::cout << p4 << std::endl;
  }

  return NSApplicationMain(argc, argv);
}
