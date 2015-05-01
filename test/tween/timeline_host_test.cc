//
//  tween/timeline_host_test.cc
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
#include "solas/tween.h"

namespace solas {
namespace tween {

namespace {

class Type {
 public:
  Type() = default;
  explicit Type(double value) : value_(value) {}
  double value() const { return value_; }
  void set_value(double value) { value_ = value; }

 private:
  double value_;
};

}  // namespace

//TEST(TimelineHostTest, TweenWithPointer) {
//  double value;
//  Host::Interval::Value interval;
//  const auto easing = LinearEasing::In;
//  const auto callback = []() {};
//  Host host;
//  Host::Tween tween;
//  tween = host.tween(&value, value, easing, interval);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), Host::Interval::Value());
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, value, easing, interval, callback);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), Host::Interval::Value());
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, value, easing, interval, interval);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), interval);
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, value, easing, interval, interval, callback);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), interval);
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//}
//
//TEST(TimelineHostTest, TweenWithAccessor) {
//  Type value;
//  Host::Interval::Value interval;
//  const auto easing = LinearEasing::In;
//  const auto callback = []() {};
//  Host host;
//  Host::Tween tween;
//  tween = host.tween(&value, &Type::value, &Type::set_value,
//                     "value", value.value(),
//                     easing, interval);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), Host::Interval::Value());
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, &Type::value, &Type::set_value,
//                     "value", value.value(),
//                     easing, interval, callback);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), Host::Interval::Value());
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, &Type::value, &Type::set_value,
//                     "value", value.value(),
//                     easing, interval, interval);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), interval);
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//  tween = host.tween(&value, &Type::value, &Type::set_value,
//                     "value", value.value(),
//                     easing, interval, interval, callback);
//  ASSERT_EQ(tween.duration(), interval);
//  ASSERT_EQ(tween.delay(), interval);
//  ASSERT_EQ(tween.timeline(), &host.timeline());
//}

}  // namespace tween
}  // namespace solas
