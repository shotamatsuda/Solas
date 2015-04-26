//
//  solas/triangle/result.h
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

#pragma once
#ifndef SOLAS_TRIANGLE_RESULT_H_
#define SOLAS_TRIANGLE_RESULT_H_

#include <memory>

struct triangulateio;

namespace solas {
namespace triangle {

class Result final {
 public:
  // Constructors
  Result();
  ~Result();

  // Disallow copy and assign
  Result(const Result& other) = delete;
  Result& operator=(const Result& other) = delete;

  // Move
  Result(Result&& other) = default;

  // Operators
  struct triangulateio& operator*() { return *get(); }
  struct triangulateio * operator->() { return get(); }
  struct triangulateio * get() { return data_.get(); }

 private:
  std::unique_ptr<struct triangulateio> data_;
};

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_RESULT_H_