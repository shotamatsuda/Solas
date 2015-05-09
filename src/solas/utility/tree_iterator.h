//
//  solas/utility/tree_iterator.h
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
#ifndef SOLAS_UTILITY_TREE_ITERATOR_H_
#define SOLAS_UTILITY_TREE_ITERATOR_H_

#include <iterator>

namespace solas {
namespace utility {

// Primary template
template <typename T, typename... Iterators>
class TreeIterator;

#pragma mark -

// Terminating partial specialization
template <typename T, typename Iterator>
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
template <typename T, typename Iterator, typename... RestIterators>
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

template <typename T, typename Iterator>
inline TreeIterator<T, Iterator>::TreeIterator() : current_() {}

template <typename T, typename Iterator>
inline TreeIterator<T, Iterator>
    ::TreeIterator(Iterator begin, Iterator end)
    : current_(begin) {}

template <typename T, typename Iterator, typename... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    ::TreeIterator()
    : current_(),
      end_() {}

template <typename T, typename Iterator, typename... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    ::TreeIterator(Iterator begin, Iterator end)
    : current_(begin),
      end_(end) {
  validate();
}

#pragma mark Comparison

template <typename T, typename Iterator>
inline bool TreeIterator<T, Iterator>
    ::operator==(const TreeIterator& other) const {
  return current_ == other.current_;
}

template <typename T, typename Iterator>
inline bool TreeIterator<T, Iterator>
    ::operator!=(const TreeIterator& other) const {
  return !operator==(other);
}

template <typename T, typename Iterator, typename... RestIterators>
inline bool TreeIterator<T, Iterator, RestIterators...>
    ::operator==(const TreeIterator& other) const {
  return current_ == other.current_ && rest_ == other.rest_;
}

template <typename T, typename Iterator, typename... RestIterators>
inline bool TreeIterator<T, Iterator, RestIterators...>
    ::operator!=(const TreeIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

template <typename T, typename Iterator>
inline T& TreeIterator<T, Iterator>::operator*() const {
  return *current_;
}

template <typename T, typename Iterator, typename... RestIterators>
inline T& TreeIterator<T, Iterator, RestIterators...>::operator*() const {
  return *rest_;
}

template <typename T, typename Iterator>
inline TreeIterator<T, Iterator>&
    TreeIterator<T, Iterator>::operator++() {
  ++current_;
  return *this;
}

template <typename T, typename Iterator, typename... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>&
    TreeIterator<T, Iterator, RestIterators...>::operator++() {
  using RestIterator = TreeIterator<T, RestIterators...>;
  if (++rest_ == RestIterator(current_->end(), current_->end())) {
    ++current_;
    validate();
  }
  return *this;
}

template <typename T, typename Iterator, typename... RestIterators>
inline void TreeIterator<T, Iterator, RestIterators...>::validate() {
  using RestIterator = TreeIterator<T, RestIterators...>;
  if (current_ == end_) {
    // Set the rest iterator to the default-constructed value so that
    // it can be comparred with end iterators.
    rest_ = RestIterator();
    return;
  }
  rest_ = RestIterator(current_->begin(), current_->end());
  while (!&*rest_ && current_ != end_) {
    ++current_;
    if (current_ != end_) {
      rest_ = RestIterator(current_->begin(), current_->end());
    } else {
      // Same discussion above
      rest_ = RestIterator();
    }
  }
}

template <typename T, typename Iterator>
inline TreeIterator<T, Iterator>
    TreeIterator<T, Iterator>::operator++(int) {
  TreeIterator result(*this);
  operator++();
  return result;
}

template <typename T, typename Iterator, typename... RestIterators>
inline TreeIterator<T, Iterator, RestIterators...>
    TreeIterator<T, Iterator, RestIterators...>::operator++(int) {
  TreeIterator result(*this);
  operator++();
  return result;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_TREE_ITERATOR_H_
