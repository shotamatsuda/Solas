//
//  solas/app/layer.h
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
#ifndef SOLAS_APP_LAYER_H_
#define SOLAS_APP_LAYER_H_

#include <cassert>

#include "solas/app/composite.h"

namespace solas {
namespace app {

template <class View>
class Layer : public Composite {
 public:
  // Constructors
  explicit Layer(View *parent);
  explicit Layer(Layer *parent);

  // Aggregation
  View& view() const;
};

#pragma mark -

template <class View>
inline Layer<View>::Layer(View *parent) : Composite(parent) {}

template <class View>
inline Layer<View>::Layer(Layer *parent) : Composite(parent) {}

#pragma mark Aggregation

template <class View>
inline View& Layer<View>::view() const {
  Composite *current = parent();
  assert(current);
  while (current->parent()) {
    current = current->parent();
  }
  return static_cast<View&>(*current);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_LAYER_H_
