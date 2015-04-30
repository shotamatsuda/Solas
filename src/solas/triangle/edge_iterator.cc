//
//  solas/triangle/edge_iterator.cc
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

#include "solas/triangle/edge_iterator.h"

#include <memory>

#include "solas/triangle/edge.h"
#include "solas/triangle/lib.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

EdgeIterator::EdgeIterator(const std::shared_ptr<Result>& result)
    : result_(result),
      begin_((*result)->edgelist),
      current_(begin_),
      derived_(nullptr)  {}

EdgeIterator::EdgeIterator(const std::shared_ptr<Result>& result,
                           const int *current)
    : result_(result),
      begin_((*result)->edgelist),
      current_(current),
      derived_(nullptr)  {}

#pragma mark Iterator

const Edge& EdgeIterator::operator*() const {
  if (derived_ != current_) {
    const auto a = *(current_ + 0) * 2;
    const auto b = *(current_ + 1) * 2;
    const auto points = (*result_)->pointlist;
    const auto normals = (*result_)->normlist;
    if (b < 0) {
      // Infinite
      edge_.finite = false;
      edge_.line.set(Vector(points + a), Vector(normals + (current_ - begin_)));
    } else {
      // Finite
      edge_.finite = true;
      edge_.line.set(Vector(points + a), Vector(points + b));
    }
    derived_ = current_;
  }
  return edge_;
}

}  // namespace triangle
}  // namespace solas
