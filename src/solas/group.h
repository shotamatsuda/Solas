//
//  solas/group.h
//
//  The MIT License
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
#ifndef SOLAS_GROUP_H_
#define SOLAS_GROUP_H_

#include <cassert>

#include "solas/composite.h"

namespace solas {

template <class View>
class Group : public Composite {
 public:
  explicit Group(View *parent);
  explicit Group(Group *parent);

  // Disallow copy semantics
  Group(const Group&) = delete;
  Group& operator=(const Group&) = delete;

  // Move semantics
  Group(Group&& other) = default;
  Group& operator=(Group&& other) = default;

  // Aggregation
  View& view() const;
};

#pragma mark -

template <class View>
inline Group<View>::Group(View *parent) : Composite(parent) {}

template <class View>
inline Group<View>::Group(Group *parent) : Composite(parent) {}

#pragma mark Aggregation

template <class View>
inline View& Group<View>::view() const {
  Composite *current = parent();
  assert(current);
  while (current->parent()) {
    current = current->parent();
  }
  assert(current);
  return static_cast<View&>(*current);
}

}  // namespace solas

#endif  // SOLAS_GROUP_H_
