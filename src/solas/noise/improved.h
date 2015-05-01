//
//  solas/noise/improved.h
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
#ifndef SOLAS_NOISE_IMPROVED_H_
#define SOLAS_NOISE_IMPROVED_H_

namespace solas {
namespace noise {

template <typename T>
struct Improved final {
  T operator()(T x);
  T operator()(T x, T y);
  T operator()(T x, T y, T z);
  T operator()(T x, T y, T z, T w);
};

}  // namespace noise
}  // namespace solas

#endif  // SOLAS_NOISE_IMPROVED_H_
