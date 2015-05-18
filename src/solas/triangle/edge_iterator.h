//
//  solas/triangle/edge_iterator.h
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
#ifndef SOLAS_TRIANGLE_EDGE_ITERATOR_H_
#define SOLAS_TRIANGLE_EDGE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "solas/triangle/edge.h"
#include "solas/triangle/result.h"

struct triangulateio;

namespace solas {
namespace triangle {

class EdgeIterator final
    : public std::iterator<std::forward_iterator_tag, const Edge> {
 public:
  // Constructors
  EdgeIterator();
  EdgeIterator(const std::shared_ptr<Result>& result);
  EdgeIterator(const std::shared_ptr<Result>& result, const int *current);

  // Copy and assign
  EdgeIterator(const EdgeIterator& other) = default;
  EdgeIterator& operator=(const EdgeIterator& other) = default;

  // Comparison
  bool operator==(const EdgeIterator& other) const;
  bool operator!=(const EdgeIterator& other) const;

  // Iterator
  const Edge& operator*() const;
  const Edge * operator->() const { return &operator*(); }
  EdgeIterator& operator++();
  EdgeIterator operator++(int);

 private:
  std::shared_ptr<Result> result_;
  const int * const begin_;
  const int *current_;

  // Cache
  mutable const int *derived_;
  mutable Edge edge_;
};

#pragma mark -

inline EdgeIterator::EdgeIterator()
    : begin_(nullptr),
      current_(nullptr),
      derived_(nullptr) {}

#pragma mark Comparison

inline bool EdgeIterator::operator==(const EdgeIterator& other) const {
  return current_ == other.current_;
}

inline bool EdgeIterator::operator!=(const EdgeIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

inline EdgeIterator& EdgeIterator::operator++() {
  ++current_;
  return *this;
}

inline EdgeIterator EdgeIterator::operator++(int) {
  EdgeIterator result(*this);
  operator++();
  return result;
}

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_EDGE_ITERATOR_H_
