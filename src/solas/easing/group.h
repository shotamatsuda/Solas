//
//  solas/easing/group.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//  Copyright (C) 2014-2015 takram design engineering
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

namespace solas {
namespace easing {

template <typename T, T (*Function)(T)>
struct Group {
  static constexpr Function In = Function();
  static constexpr ReverseFunction Out = ReverseFunction();
  static constexpr SymmetricFunction InOut = SymmetricFunction();
};

#pragma mark -

template <double (*Function)(double)>
inline double Group<Function>::In_::operator()(double t) const {
  return Function(t);
}

template <double (*Function)(double)>
inline double Group<Function>::Out_::operator()(double t) const {
  return 1.0 - Function(1.0 - t);
}

template <double (*Function)(double)>
inline double Group<Function>::InOut_::operator()(double t) const {
  if (t < 0.5) {
    return In_()(2.0 * t) / 2.0;
  } else {
    return 0.5 + Out_()(2.0 * t - 1.0) / 2.0;
  }
}

template <double (*Function)(double)>
constexpr typename EasingGroup<Function>::In_ EasingGroup<Function>::In;
template <double (*Function)(double)>
constexpr typename EasingGroup<Function>::Out_ EasingGroup<Function>::Out;
template <double (*Function)(double)>
constexpr typename EasingGroup<Function>::InOut_ EasingGroup<Function>::InOut;

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_GROUP_H_
