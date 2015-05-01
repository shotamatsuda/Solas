//
//  solas/easing/symmetric_inflector.h
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
#ifndef SOLAS_EASING_SYMMETRIC_INFLECTOR_H_
#define SOLAS_EASING_SYMMETRIC_INFLECTOR_H_

#include "solas/easing/inflector.h"
#include "solas/easing/reverse_inflector.h"

namespace solas {
namespace easing {

template <typename T, template <typename = T> class Function>
struct SymmetricInflector {
  T operator()(T parameter);
};

#pragma mark -

template <typename T, template <typename> class Function>
inline T SymmetricInflector<T, Function>::operator()(T parameter) {
  if (parameter < 0.5) {
    return Inflector<T, Function>()(2.0 * parameter) / 2.0;
  } else {
    return 0.5 + ReverseInflector<T, Function>()(2.0 * parameter - 1.0) / 2.0;
  }
}

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_SYMMETRIC_INFLECTOR_H_
