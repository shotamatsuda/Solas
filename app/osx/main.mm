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

#include "solas/math.h"
#include "solas/app.h"
#include "solas/graphics.h"

class App : public solas::app::Runnable {
 public:
};

int main(int argc, char **argv) {

  std::cout << "bool " << typeid(bool).name() << std::endl;
  std::cout << "char " << typeid(char).name() << std::endl;
  std::cout << "int8_t " << typeid(std::int8_t).name() << std::endl;
  std::cout << "uint8_t " << typeid(std::uint8_t).name() << std::endl;
  std::cout << "int16_t " << typeid(std::int16_t).name() << std::endl;
  std::cout << "uint16_t " << typeid(std::uint16_t).name() << std::endl;
  std::cout << "int32_t " << typeid(std::int32_t).name() << std::endl;
  std::cout << "uint32_t " << typeid(std::uint32_t).name() << std::endl;
  std::cout << "int64_t " << typeid(std::int64_t).name() << std::endl;
  std::cout << "uint64_t " << typeid(std::uint64_t).name() << std::endl;
  std::cout << "float " << typeid(float).name() << std::endl;
  std::cout << "double " << typeid(double).name() << std::endl;

  return solas::app::Run<App>(argc, argv);
}
