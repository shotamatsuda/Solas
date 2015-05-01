//
//  tween/timeline_test.cc
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

#include <memory>

#include "gtest/gtest.h"

#include "solas/easing.h"
#include "solas/tween/accessor_adaptor.h"
#include "solas/tween/interval.h"
#include "solas/tween/pointer_adaptor.h"
#include "solas/tween/timeline.h"
#include "solas/tween/tween.h"

namespace solas {
namespace tween {

template <typename T>
class TweenTest : public ::testing::Test {};

using Types = ::testing::Types<
  Time,
  Frame
>;
TYPED_TEST_CASE(TweenTest, Types);

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

TYPED_TEST(TweenTest, DefaultConstructible) {
  Tween<TypeParam> tween;
  ASSERT_EQ(tween, false);
  ASSERT_EQ(tween.empty(), true);
  ASSERT_EQ(tween.timeline(), nullptr);
}

TYPED_TEST(TweenTest, CopyConstructible) {
  double value;
  const auto adaptor = std::make_shared<PointerAdaptor<TypeParam, double>>(
      &value, value, LinearEasing::In, TypeParam(), TypeParam(), nullptr);
  Timeline<TypeParam> timeline;
  Tween<TypeParam> tween1(adaptor, &timeline);
  Tween<TypeParam> tween2(tween1);
  ASSERT_TRUE(tween1 == tween2);
}

TYPED_TEST(TweenTest, Assignable) {
  double value;
  const auto adaptor = std::make_shared<PointerAdaptor<TypeParam, double>>(
      &value, value, LinearEasing::In, TypeParam(), TypeParam(), nullptr);
  Timeline<TypeParam> timeline;
  Tween<TypeParam> tween1(adaptor, &timeline);
  Tween<TypeParam> tween2;
  tween2 = tween1;
  ASSERT_TRUE(tween1 == tween2);
}

TYPED_TEST(TweenTest, ConstructibleWithPointer) {
  double value;
  const auto interval = typename TypeParam::Value();
  const auto easing = LinearEasing::In;
  const auto callback = []() {};
  using Tween = Tween<TypeParam>;
  Tween tween;
  tween = Tween(&value, value, easing, interval);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, value, easing, interval, callback);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, value, easing, interval, interval);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, value, easing, interval, interval, callback);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), nullptr);
  Timeline<TypeParam> timeline;
  tween = Tween(&value, value, easing, interval, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, value, easing, interval, callback, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, value, easing, interval, interval, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, value, easing, interval, interval, callback, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), &timeline);
}

TYPED_TEST(TweenTest, ConstructibleWithAccessor) {
  Type value;
  const auto interval = typename TypeParam::Value();
  const auto easing = LinearEasing::In;
  const auto callback = []() {};
  using Tween = Tween<TypeParam>;
  Tween tween;
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, callback);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, interval);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), nullptr);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, interval, callback);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), nullptr);
  Timeline<TypeParam> timeline;
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, callback, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), typename TypeParam::Value());
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, interval, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), &timeline);
  tween = Tween(&value, &Type::value, &Type::set_value,
                "value", value.value(),
                easing, interval, interval, callback, &timeline);
  ASSERT_EQ(tween.duration(), interval);
  ASSERT_EQ(tween.delay(), interval);
  ASSERT_EQ(tween.timeline(), &timeline);
}

}  // namespace tween
}  // namespace solas
