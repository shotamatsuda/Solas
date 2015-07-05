//
//  solas/utility/tree_iterator.h
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

#pragma once
#ifndef SOLAS_UTILITY_TREE_ITERATOR_H_
#define SOLAS_UTILITY_TREE_ITERATOR_H_

#include <iterator>

namespace solas {
namespace utility {

// Primary template
template <class T, class... Iterators>
class TreeIterator;

#pragma mark -

// Terminating partial specialization
template <class T, class Iterator>
class TreeIterator<T, Iterator> final
    : public std::iterator<std::forward_iterator_tag, T> {
 public:
  // Constructors
  TreeIterator();
  TreeIterator(Iterator begin, Iterator end);

  // Copy and assign
  TreeIterator(const TreeIterator& other) = default;
  TreeIterator& operator=(const TreeIterator& other) = default;

  // Comparison
  bool operator==(const TreeIterator& other) const;
  bool operator!=(const TreeIterator& other) const;

  // Iterator
  T& operator*() const;
  T * operator->() const { return &operator*(); }
  TreeIterator& operator++();
  TreeIterator operator++(int);

 private:
  Iterator current_;
};

#pragma mark -

// Recursive partial specialization
template <class T, class Iterator, class... RestIterators>
class TreeIterator<T, Iterator, RestIterators...> final
    : public std::iterator<std::forward_iterator_tag, T> {
 public:
  // Constructors
  TreeIterator();
  TreeIterator(Iterator begin, Iterator end);

  // Copy and assign
  TreeIterator(const TreeIterator& other) = default;
  TreeIterator& operator=(const TreeIterator& other) = default;

  // Comparison
  bool operator==(const TreeIterator& other) const;
  bool operator!=(const TreeIterator& other) const;

  // Iterator
  T& operator*() const;
  T * operator->() const { return &operator*(); }
  TreeIterator& operator++();
  TreeIterator operator++(int);

 private:
  void validate();

 private:
  Iterator current_;
  Iterator end_;
  TreeIterator<T, RestIterators...> rest_;
};

#pragma mark -

template <class T, class Iterator>
inline TreeIterator<T, Iterator>::TreeIterator() : current_() {}

template <class T, class Iterator>
inline TreeIterator<T, Iterator>
    ::TreeIterator(Iterator begin, Iterator end)
    : current_(begin) {}

template <class T, class Iterator, class... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    ::TreeIterator()
    : current_(),
      end_() {}

template <class T, class Iterator, class... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    ::TreeIterator(Iterator begin, Iterator end)
    : current_(begin),
      end_(end) {
  validate();
}

#pragma mark Comparison

template <class T, class Iterator>
inline bool TreeIterator<T, Iterator>
    ::operator==(const TreeIterator& other) const {
  return current_ == other.current_;
}

template <class T, class Iterator>
inline bool TreeIterator<T, Iterator>
    ::operator!=(const TreeIterator& other) const {
  return !operator==(other);
}

template <class T, class Iterator, class... RestIterators>
inline bool TreeIterator<T, Iterator, RestIterators...>
    ::operator==(const TreeIterator& other) const {
  return current_ == other.current_ && rest_ == other.rest_;
}

template <class T, class Iterator, class... RestIterators>
inline bool TreeIterator<T, Iterator, RestIterators...>
    ::operator!=(const TreeIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

template <class T, class Iterator>
inline T& TreeIterator<T, Iterator>::operator*() const {
  return *current_;
}

template <class T, class Iterator, class... RestIterators>
inline T& TreeIterator<T, Iterator, RestIterators...>::operator*() const {
  return *rest_;
}

template <class T, class Iterator>
inline TreeIterator<T, Iterator>&
    TreeIterator<T, Iterator>::operator++() {
  ++current_;
  return *this;
}

template <class T, class Iterator, class... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>&
    TreeIterator<T, Iterator, RestIterators...>::operator++() {
  using RestIterator = TreeIterator<T, RestIterators...>;
  if (++rest_ == RestIterator(current_->end(), current_->end())) {
    ++current_;
    validate();
  }
  return *this;
}

template <class T, class Iterator, class... RestIterators>
inline void TreeIterator<T, Iterator, RestIterators...>::validate() {
  using RestIterator = TreeIterator<T, RestIterators...>;
  if (current_ == end_) {
    // Set the rest iterator to the default-constructed value so that
    // it can be comparred with end iterators.
    rest_ = RestIterator();
    return;
  }
  rest_ = RestIterator(current_->begin(), current_->end());
  while (rest_ == RestIterator() && current_ != end_) {
    ++current_;
    if (current_ != end_) {
      rest_ = RestIterator(current_->begin(), current_->end());
    } else {
      // Same discussion above
      rest_ = RestIterator();
    }
  }
}

template <class T, class Iterator>
inline TreeIterator<T, Iterator>
    TreeIterator<T, Iterator>::operator++(int) {
  TreeIterator result(*this);
  operator++();
  return result;
}

template <class T, class Iterator, class... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    TreeIterator<T, Iterator, RestIterators...>::operator++(int) {
  TreeIterator result(*this);
  operator++();
  return result;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_TREE_ITERATOR_H_
