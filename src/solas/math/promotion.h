//
//  solas/math/promotion.h
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
#ifndef SOLAS_MATH_PROMOTION_H_
#define SOLAS_MATH_PROMOTION_H_

#include <boost/math/tools/promotion.hpp>

namespace solas {
namespace math {

template <typename T, typename U = T>
using Promote = typename boost::math::tools::promote_args_2<T, U>::type;

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_PROMOTION_H_
