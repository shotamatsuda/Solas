//
//  solas/easing/group.h
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
