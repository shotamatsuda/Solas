//
//  solas/utility/iterator_iterator.h
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
#ifndef SOLAS_UTILITY_ITERATOR_ITERATOR_H_
#define SOLAS_UTILITY_ITERATOR_ITERATOR_H_

#include <iterator>

namespace solas {
namespace utility {

template <typename T, typename... Iterators>
class IteratorIterator;

template <typename T, typename Iterator>
class IteratorIterator<T, Iterator> final
    : public std::iterator<std::forward_iterator_tag, T> {
 public:
  // Constructors
  IteratorIterator();
  IteratorIterator(Iterator begin, Iterator end);

  // Copy and assign
  IteratorIterator(const IteratorIterator& other) = default;
  IteratorIterator& operator=(const IteratorIterator& other) = default;

  // Comparison
  bool operator==(const IteratorIterator& other) const;
  bool operator!=(const IteratorIterator& other) const;

  // Iterator
  T& operator*() const;
  T * operator->() const { return &operator*(); }
  IteratorIterator& operator++();
  IteratorIterator operator++(int);

 private:
  Iterator current_;
};

template <typename T, typename Iterator, typename... RestIterators>
class IteratorIterator<T, Iterator, RestIterators...> final
    : public std::iterator<std::forward_iterator_tag, T> {
 public:
  // Constructors
  IteratorIterator();
  IteratorIterator(Iterator begin, Iterator end);

  // Copy and assign
  IteratorIterator(const IteratorIterator& other) = default;
  IteratorIterator& operator=(const IteratorIterator& other) = default;

  // Comparison
  bool operator==(const IteratorIterator& other) const;
  bool operator!=(const IteratorIterator& other) const;

  // Iterator
  T& operator*() const;
  T * operator->() const { return &operator*(); }
  IteratorIterator& operator++();
  IteratorIterator operator++(int);

 private:
  Iterator current_;
  Iterator end_;
  IteratorIterator<T, RestIterators...> rest_;
};

#pragma mark -

template <typename T, typename Iterator>
inline IteratorIterator<T, Iterator>::IteratorIterator()
  : current_() {}

template <typename T, typename Iterator>
inline IteratorIterator<T, Iterator>
    ::IteratorIterator(Iterator begin, Iterator end)
  : current_(begin) {}

template <typename T, typename Iterator, typename... RestIterators>
inline IteratorIterator<T, Iterator, RestIterators...>
    ::IteratorIterator()
  : current_(),
    end_() {}

template <typename T, typename Iterator, typename... RestIterators>
inline IteratorIterator<T, Iterator, RestIterators...>
    ::IteratorIterator(Iterator begin, Iterator end)
  : current_(begin),
    end_(end) {
  using RestIterator = IteratorIterator<T, RestIterators...>;
  if (current_ != end_) {
    rest_ = RestIterator(current_->begin(), current_->end());
  }
}

#pragma mark Comparison

template <typename T, typename Iterator>
inline bool IteratorIterator<T, Iterator>
    ::operator==(const IteratorIterator& other) const {
  return current_ == other.current_;
}

template <typename T, typename Iterator>
inline bool IteratorIterator<T, Iterator>
    ::operator!=(const IteratorIterator& other) const {
  return !operator==(other);
}

template <typename T, typename Iterator, typename... RestIterators>
inline bool IteratorIterator<T, Iterator, RestIterators...>
    ::operator==(const IteratorIterator& other) const {
  return current_ == other.current_ && rest_ == other.rest_;
}

template <typename T, typename Iterator, typename... RestIterators>
inline bool IteratorIterator<T, Iterator, RestIterators...>
    ::operator!=(const IteratorIterator& other) const {
  return !operator==(other);
}

#pragma mark Iterator

template <typename T, typename Iterator>
inline T& IteratorIterator<T, Iterator>::operator*() const {
  return *current_;
}

template <typename T, typename Iterator, typename... RestIterators>
inline T& IteratorIterator<T, Iterator, RestIterators...>::operator*() const {
  return *rest_;
}

template <typename T, typename Iterator>
inline IteratorIterator<T, Iterator>&
    IteratorIterator<T, Iterator>::operator++() {
  ++current_;
  return *this;
}

template <typename T, typename Iterator, typename... RestIterators>
inline IteratorIterator<T, Iterator, RestIterators...>&
    IteratorIterator<T, Iterator, RestIterators...>::operator++() {
  using RestIterator = IteratorIterator<T, RestIterators...>;
  ++rest_;
  if (rest_ == RestIterator(current_->end(), current_->end())) {
    ++current_;
    if (current_ != end_) {
      rest_ = RestIterator(current_->begin(), current_->end());
    } else {
      rest_ = RestIterator();
    }
  }
  return *this;
}

template <typename T, typename Iterator>
inline IteratorIterator<T, Iterator>
    IteratorIterator<T, Iterator>::operator++(int) {
  IteratorIterator result(*this);
  operator++();
  return result;
}

template <typename T, typename Iterator, typename... RestIterators>
inline IteratorIterator<T, Iterator, RestIterators...>
    IteratorIterator<T, Iterator, RestIterators...>::operator++(int) {
  IteratorIterator result(*this);
  operator++();
  return result;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_ITERATOR_ITERATOR_H_
