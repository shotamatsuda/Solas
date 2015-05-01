//
//  easing_test.cc
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

#include "gtest/gtest.h"

#include "solas/easing.h"

namespace solas {
namespace easing {

TEST(EasingTest, DefaultConstructible) {
  Easing<double> easing1 = BackEasing<double>::In;
  Easing<double> easing2 = BackEasing<double>::Out;
  Easing<double> easing3 = BackEasing<double>::InOut;
}

}  // namespace easing
}  // namespace solas
