//
//  solas/easing/group.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
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
#ifndef SOLAS_EASING_GROUP_H_
#define SOLAS_EASING_GROUP_H_

#include <functional>

#include "solas/easing/inflector.h"
#include "solas/easing/reverse_inflector.h"
#include "solas/easing/symmetric_inflector.h"

namespace solas {
namespace easing {

template <typename T, template <typename = T> class Function>
struct Group {
  static Inflector<T, Function> In;
  static ReverseInflector<T, Function> Out;
  static SymmetricInflector<T, Function> InOut;
};

#pragma mark -

template <typename T, template <typename> class Function>
Inflector<T, Function> Group<T, Function>::In;
template <typename T, template <typename> class Function>
ReverseInflector<T, Function> Group<T, Function>::Out;
template <typename T, template <typename> class Function>
SymmetricInflector<T, Function> Group<T, Function>::InOut;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_GROUP_H_
