//
//  tween/interval_test.cc
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

#include <cstdint>
#include <random>
#include <type_traits>

#include "gtest/gtest.h"

#include "solas/tween/interval.h"

namespace solas {
namespace tween {

template <typename T>
class IntervalTest : public ::testing::Test {
 protected:
  void SetUp() override {
    engine_ = std::default_random_engine(random_device_());
  }

  T random() {
    if (std::is_integral<T>::value) {
      std::uniform_int_distribution<T> distribution(
          std::numeric_limits<T>::min(),
          std::numeric_limits<T>::max());
      return distribution(engine_);
    } else if (std::is_floating_point<T>::value) {
      std::uniform_real_distribution<T> distribution(
          std::numeric_limits<T>::min(),
          std::numeric_limits<T>::max());
      return distribution(engine_);
    }
  }

 private:
  std::random_device random_device_;
  std::default_random_engine engine_;
};

using Types = ::testing::Types<
  bool,
  char,
  std::int8_t,
  std::uint8_t,
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  std::int64_t,
  std::uint64_t,
  float,
  double
>;
TYPED_TEST_CASE(IntervalTest, Types);

TYPED_TEST(IntervalTest, DefaultConstructible) {
  Interval<TypeParam> interval;
  ASSERT_EQ(interval.count(), TypeParam());
}

TYPED_TEST(IntervalTest, ValueConstructible) {
  const auto value = this->random();
  Interval<TypeParam> interval(value);
  ASSERT_EQ(interval.count(), value);
}

TYPED_TEST(IntervalTest, CopyConstructible) {
  const auto value = this->random();
  Interval<TypeParam> interval1(value);
  Interval<TypeParam> interval2(interval1);
  ASSERT_EQ(interval1, interval2);
}

TYPED_TEST(IntervalTest, Assignable) {
  const auto value = this->random();
  Interval<TypeParam> interval1(value);
  Interval<TypeParam> interval2;
  interval2 = interval1;
  ASSERT_EQ(interval1, interval2);
}

TYPED_TEST(IntervalTest, Comparable) {
  const auto min = std::numeric_limits<TypeParam>::min();
  const auto max = std::numeric_limits<TypeParam>::max();
  ASSERT_TRUE(Interval<TypeParam>(min) == Interval<TypeParam>(min));
  ASSERT_TRUE(Interval<TypeParam>(min) != Interval<TypeParam>(max));
  ASSERT_TRUE(Interval<TypeParam>(min) < Interval<TypeParam>(max));
  ASSERT_TRUE(Interval<TypeParam>(max) > Interval<TypeParam>(min));
  ASSERT_TRUE(Interval<TypeParam>(min) <= Interval<TypeParam>(min));
  ASSERT_TRUE(Interval<TypeParam>(min) <= Interval<TypeParam>(max));
  ASSERT_TRUE(Interval<TypeParam>(min) >= Interval<TypeParam>(min));
  ASSERT_TRUE(Interval<TypeParam>(max) >= Interval<TypeParam>(min));
}

TYPED_TEST(IntervalTest, Arithmetic) {
  Interval<TypeParam> interval;
  const auto epsilon = std::numeric_limits<TypeParam>::epsilon();
  interval += Interval<TypeParam>(epsilon);
  ASSERT_EQ(interval.count(), epsilon);
  interval -= Interval<TypeParam>(epsilon);
  ASSERT_EQ(interval.count(), TypeParam());
}

TYPED_TEST(IntervalTest, Count) {
  const auto value = this->random();
  Interval<TypeParam> interval(value);
  ASSERT_EQ(interval.count(), value);
}

TYPED_TEST(IntervalTest, Empty) {
  Interval<TypeParam> interval;
  ASSERT_TRUE(interval.empty());
}

}  // namespace tween
}  // namespace solas
