//
//  solas/triangle/triangle_iterator.cc
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
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

#include "solas/triangle/triangle_iterator.h"

#include <memory>

#include "solas/triangle/lib.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

TriangleIterator::TriangleIterator(const std::shared_ptr<Result>& result)
    : result_(result),
      begin_((*result)->trianglelist),
      current_(begin_),
      derived_(nullptr)  {}

TriangleIterator::TriangleIterator(const std::shared_ptr<Result>& result,
                                   const int *current)
    : result_(result),
      begin_((*result)->trianglelist),
      current_(current),
      derived_(nullptr)  {}

#pragma mark Iterator

const Triangle& TriangleIterator::operator*() const {
  if (derived_ != current_) {
    const auto a = *(current_ + 0) * 2;
    const auto b = *(current_ + 1) * 2;
    const auto c = *(current_ + 2) * 2;
    const auto points = (*result_)->pointlist;
    triangle_.set(Vector(points + a), Vector(points + b), Vector(points + c));
    derived_ = current_;
  }
  return triangle_;
}

}  // namespace triangle
}  // namespace solas
