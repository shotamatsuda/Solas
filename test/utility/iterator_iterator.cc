//
//  utility/tree_iterator.cc
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

#include <iterator>
#include <vector>

#include "gtest/gtest.h"

#include "solas/utility/tree_iterator.h"

namespace solas {
namespace utility {

namespace {

using C = std::vector<int>;
using B = std::vector<C>;
using A = std::vector<B>;
using Iterator = TreeIterator<int, A::iterator, B::iterator, C::iterator>;

}  // namespace

TEST(TreeIteratorTest, Traversing) {
  {
    A a;
    auto begin = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_EQ(begin, end);
  } {
    int i{};
    A a{{{++i, ++i}, {++i, ++i}}, {{++i, ++i}, {++i, ++i}}};
    auto itr = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_NE(itr, end);
    int j{};
    for (; itr != end; ++itr) {
      ASSERT_EQ(*itr, ++j);
    }
    ASSERT_EQ(itr, end);
  } {
    int i{};
    A a{{}, {{}, {++i}, {}}, {}, {{}, {++i}, {}}, {}};
    auto itr = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_NE(itr, end);
    int j{};
    for (; itr != end; ++itr) {
      ASSERT_EQ(*itr, ++j);
    }
    ASSERT_EQ(itr, end);
  }
}

TEST(TreeIteratorTest, Distance) {
  {
    A a;
    auto begin = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_EQ(begin, end);
    ASSERT_EQ(std::distance(begin, end), 0);
  } {
    int i{};
    A a{{{++i, ++i}, {++i, ++i}}, {{++i, ++i}, {++i, ++i}}};
    auto begin = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_EQ(std::distance(begin, end), i);
  } {
    int i{};
    A a{{}, {{}, {++i}, {}}, {}, {{}, {++i}, {}}, {}};
    auto begin = Iterator(a.begin(), a.end());
    auto end = Iterator(a.end(), a.end());
    ASSERT_EQ(std::distance(begin, end), i);
  }
}

}  // namespace utility
}  // namespace solas
