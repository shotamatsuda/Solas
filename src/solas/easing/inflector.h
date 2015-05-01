//
//  solas/easing/inflector.h
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
#ifndef SOLAS_EASING_INFLECTOR_H_
#define SOLAS_EASING_INFLECTOR_H_

namespace solas {
namespace easing {

template <typename T, template <typename = T> class Function>
struct Inflector {
  T operator()(T parameter);
};

#pragma mark -

template <typename T, template <typename> class Function>
inline T Inflector<T, Function>::operator()(T parameter) {
  return Function<T>()(parameter);
}

}  // namespace easing
}  // namespace solas

#endif  // SOLAS_EASING_INFLECTOR_H_
