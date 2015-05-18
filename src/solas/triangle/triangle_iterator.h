//
//  solas/triangle/triangle_iterator.h
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

#pragma once
#ifndef SOLAS_TRIANGLE_TRIANGLE_ITERATOR_H_
#define SOLAS_TRIANGLE_TRIANGLE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "solas/triangle/result.h"
#include "solas/triangle/type.h"

namespace solas {
namespace triangle {

class TriangleIterator final
    : public std::iterator<std::forward_iterator_tag, const Triangle> {
 public:
  // Constructors
  TriangleIterator();
  TriangleIterator(const std::shared_ptr<Result>& result);
  TriangleIterator(const std::shared_ptr<Result>& result, const int *current);

  // Copy and assign
  TriangleIterator(const TriangleIterator& other) = default;
  TriangleIterator& operator=(const TriangleIterator& other) = default;

  // Comparison
  bool operator==(const TriangleIterator& other) const;
  bool operator!=(const TriangleIterator& other) const;

  // Iterator
  const Triangle& operator*() const;
  const Triangle * operator->() const { return &operator*(); }
  TriangleIterator& operator++();
  TriangleIterator operator++(int);

 private:
  std::shared_ptr<Result> result_;
  const int * const begin_;
  const int *current_;

  // Cache
  mutable const int *derived_;
  mutable Triangle triangle_;
};

#pragma mark -

inline TriangleIterator::TriangleIterator()
    : begin_(nullptr),
      current_(nullptr),
      derived_(nullptr) {}

#pragma mark Comparison

inline bool TriangleIterator::operator==(const TriangleIterator& other) const {
  return current_ == other.current_;
}

inline bool TriangleIterator::operator!=(const TriangleIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

inline TriangleIterator& TriangleIterator::operator++() {
  current_ += 3;
  return *this;
}

inline TriangleIterator TriangleIterator::operator++(int) {
  TriangleIterator result(*this);
  operator++();
  return result;
}

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_TRIANGLE_ITERATOR_H_
