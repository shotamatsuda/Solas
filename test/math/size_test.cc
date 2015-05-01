//
//  math/size_test.cc
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
#include <tuple>
#include <type_traits>

#include "gtest/gtest.h"

#include "solas/math/size.h"

namespace solas {
namespace math {

template <typename T>
class SizeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    engine_ = std::default_random_engine(random_device_());
  }

  T Random() {
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
  float,
  double
>;
TYPED_TEST_CASE(SizeTest, Types);

TYPED_TEST(SizeTest, DefaultConstructible) {
  Size2<TypeParam> s2;
  ASSERT_EQ(s2.width, TypeParam());
  ASSERT_EQ(s2.height, TypeParam());

  Size3<TypeParam> s3;
  ASSERT_EQ(s3.width, TypeParam());
  ASSERT_EQ(s3.height, TypeParam());
  ASSERT_EQ(s3.depth, TypeParam());
}

TYPED_TEST(SizeTest, ConstructibleWithValue) {
  const auto value = this->Random();

  Size2<TypeParam> s2(value);
  ASSERT_EQ(s2.width, value);
  ASSERT_EQ(s2.height, value);

  Size3<TypeParam> s3(value);
  ASSERT_EQ(s3.width, value);
  ASSERT_EQ(s3.height, value);
  ASSERT_EQ(s3.depth, value);
}

TYPED_TEST(SizeTest, ConstructibleWithValues) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2(width, height);
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, height);

  Size3<TypeParam> s3(width, height, depth);
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, depth);
}

TYPED_TEST(SizeTest, ConstructibleWithTuple) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2(std::make_tuple(width, height));
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, height);

  Size3<TypeParam> s3(std::make_tuple(width, height, depth));
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, depth);
}

TYPED_TEST(SizeTest, ConstructibleWithInitializerList) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2_1{};
  ASSERT_EQ(s2_1.width, TypeParam());
  ASSERT_EQ(s2_1.height, TypeParam());
  Size2<TypeParam> s2_2{width};
  ASSERT_EQ(s2_2.width, width);
  ASSERT_EQ(s2_2.height, TypeParam());
  Size2<TypeParam> s2_3{width, height};
  ASSERT_EQ(s2_3.width, width);
  ASSERT_EQ(s2_3.height, height);
  Size2<TypeParam> s2_4{width, height, this->Random()};
  ASSERT_EQ(s2_4.width, width);
  ASSERT_EQ(s2_4.height, height);

  Size3<TypeParam> s3_1{};
  ASSERT_EQ(s3_1.width, TypeParam());
  ASSERT_EQ(s3_1.height, TypeParam());
  ASSERT_EQ(s3_1.depth, TypeParam());
  Size3<TypeParam> s3_2{width};
  ASSERT_EQ(s3_2.width, width);
  ASSERT_EQ(s3_2.height, TypeParam());
  ASSERT_EQ(s3_2.depth, TypeParam());
  Size3<TypeParam> s3_3{width, height};
  ASSERT_EQ(s3_3.width, width);
  ASSERT_EQ(s3_3.height, height);
  ASSERT_EQ(s3_3.depth, TypeParam());
  Size3<TypeParam> s3_4{width, height, depth};
  ASSERT_EQ(s3_4.width, width);
  ASSERT_EQ(s3_4.height, height);
  ASSERT_EQ(s3_4.depth, depth);
  Size3<TypeParam> s3_5{width, height, depth, this->Random()};
  ASSERT_EQ(s3_5.width, width);
  ASSERT_EQ(s3_5.height, height);
  ASSERT_EQ(s3_5.depth, depth);
}

TYPED_TEST(SizeTest, CopyConstructible) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2_1(width, height);
  Size2<TypeParam> s2_2(s2_1);
  ASSERT_EQ(s2_1, s2_2);

  Size3<TypeParam> s3_1(width, height, depth);
  Size3<TypeParam> s3_2(s3_1);
  ASSERT_EQ(s3_1, s3_2);
}

TYPED_TEST(SizeTest, CopyAssignable) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2_1(width, height);
  Size2<TypeParam> s2_2;
  s2_2 = s2_1;
  ASSERT_EQ(s2_1, s2_2);

  Size3<TypeParam> s3_1(width, height, depth);
  Size3<TypeParam> s3_2;
  s3_2 = s3_1;
  ASSERT_EQ(s3_1, s3_2);
}

TYPED_TEST(SizeTest, TupleAssignable) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2;
  s2 = std::make_tuple(width, height);
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, height);

  Size3<TypeParam> s3;
  s3 = std::make_tuple(width, height, depth);
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, depth);
}

TYPED_TEST(SizeTest, InitializerListAssignable) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2;
  s2 = {};
  ASSERT_EQ(s2.width, TypeParam());
  ASSERT_EQ(s2.height, TypeParam());
  s2 = {width};
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, TypeParam());
  s2 = {width, height};
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, height);
  s2 = {width, height, this->Random()};
  ASSERT_EQ(s2.width, width);
  ASSERT_EQ(s2.height, height);

  Size3<TypeParam> s3;
  s3 = {};
  ASSERT_EQ(s3.width, TypeParam());
  ASSERT_EQ(s3.height, TypeParam());
  ASSERT_EQ(s3.depth, TypeParam());
  s3 = {width};
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, TypeParam());
  ASSERT_EQ(s3.depth, TypeParam());
  s3 = {width, height};
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, TypeParam());
  s3 = {width, height, depth};
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, depth);
  s3 = {width, height, depth, this->Random()};
  ASSERT_EQ(s3.width, width);
  ASSERT_EQ(s3.height, height);
  ASSERT_EQ(s3.depth, depth);
}

TYPED_TEST(SizeTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto width = this->Random();
  const auto height = this->Random();
  const auto depth = this->Random();

  Size2<TypeParam> s2(width, height);
  Size2<bool> s2_bool(s2);
  Size2<char> s2_char(s2);
  Size2<std::int8_t> s2_int8(s2);
  Size2<std::uint8_t> s2_uint8(s2);
  Size2<std::int16_t> s2_int16(s2);
  Size2<std::uint16_t> s2_uint16(s2);
  Size2<std::int32_t> s2_int32(s2);
  Size2<std::uint32_t> s2_uint32(s2);
  Size2<float> s2_float(s2);
  Size2<double> s2_double(s2);
  ASSERT_EQ(s2_bool.width, static_cast<bool>(width));
  ASSERT_EQ(s2_char.width, static_cast<char>(width));
  ASSERT_EQ(s2_int8.width, static_cast<std::int8_t>(width));
  ASSERT_EQ(s2_uint8.width, static_cast<std::uint8_t>(width));
  ASSERT_EQ(s2_int16.width, static_cast<std::int16_t>(width));
  ASSERT_EQ(s2_uint16.width, static_cast<std::uint16_t>(width));
  ASSERT_EQ(s2_int32.width, static_cast<std::int32_t>(width));
  ASSERT_EQ(s2_uint32.width, static_cast<std::uint32_t>(width));
  ASSERT_EQ(s2_float.width, static_cast<float>(width));
  ASSERT_EQ(s2_double.width, static_cast<double>(width));
  ASSERT_EQ(s2_bool.height, static_cast<bool>(height));
  ASSERT_EQ(s2_char.height, static_cast<char>(height));
  ASSERT_EQ(s2_int8.height, static_cast<std::int8_t>(height));
  ASSERT_EQ(s2_uint8.height, static_cast<std::uint8_t>(height));
  ASSERT_EQ(s2_int16.height, static_cast<std::int16_t>(height));
  ASSERT_EQ(s2_uint16.height, static_cast<std::uint16_t>(height));
  ASSERT_EQ(s2_int32.height, static_cast<std::int32_t>(height));
  ASSERT_EQ(s2_uint32.height, static_cast<std::uint32_t>(height));
  ASSERT_EQ(s2_float.height, static_cast<float>(height));
  ASSERT_EQ(s2_double.height, static_cast<double>(height));

  Size3<TypeParam> s3(width, height, depth);
  Size3<bool> s3_bool(s3);
  Size3<char> s3_char(s3);
  Size3<std::int8_t> s3_int8(s3);
  Size3<std::uint8_t> s3_uint8(s3);
  Size3<std::int16_t> s3_int16(s3);
  Size3<std::uint16_t> s3_uint16(s3);
  Size3<std::int32_t> s3_int32(s3);
  Size3<std::uint32_t> s3_uint32(s3);
  Size3<float> s3_float(s3);
  Size3<double> s3_double(s3);
  ASSERT_EQ(s3_bool.width, static_cast<bool>(width));
  ASSERT_EQ(s3_char.width, static_cast<char>(width));
  ASSERT_EQ(s3_int8.width, static_cast<std::int8_t>(width));
  ASSERT_EQ(s3_uint8.width, static_cast<std::uint8_t>(width));
  ASSERT_EQ(s3_int16.width, static_cast<std::int16_t>(width));
  ASSERT_EQ(s3_uint16.width, static_cast<std::uint16_t>(width));
  ASSERT_EQ(s3_int32.width, static_cast<std::int32_t>(width));
  ASSERT_EQ(s3_uint32.width, static_cast<std::uint32_t>(width));
  ASSERT_EQ(s3_float.width, static_cast<float>(width));
  ASSERT_EQ(s3_double.width, static_cast<double>(width));
  ASSERT_EQ(s3_bool.height, static_cast<bool>(height));
  ASSERT_EQ(s3_char.height, static_cast<char>(height));
  ASSERT_EQ(s3_int8.height, static_cast<std::int8_t>(height));
  ASSERT_EQ(s3_uint8.height, static_cast<std::uint8_t>(height));
  ASSERT_EQ(s3_int16.height, static_cast<std::int16_t>(height));
  ASSERT_EQ(s3_uint16.height, static_cast<std::uint16_t>(height));
  ASSERT_EQ(s3_int32.height, static_cast<std::int32_t>(height));
  ASSERT_EQ(s3_uint32.height, static_cast<std::uint32_t>(height));
  ASSERT_EQ(s3_float.height, static_cast<float>(height));
  ASSERT_EQ(s3_double.height, static_cast<double>(height));
  ASSERT_EQ(s3_bool.depth, static_cast<bool>(depth));
  ASSERT_EQ(s3_char.depth, static_cast<char>(depth));
  ASSERT_EQ(s3_int8.depth, static_cast<std::int8_t>(depth));
  ASSERT_EQ(s3_uint8.depth, static_cast<std::uint8_t>(depth));
  ASSERT_EQ(s3_int16.depth, static_cast<std::int16_t>(depth));
  ASSERT_EQ(s3_uint16.depth, static_cast<std::uint16_t>(depth));
  ASSERT_EQ(s3_int32.depth, static_cast<std::int32_t>(depth));
  ASSERT_EQ(s3_uint32.depth, static_cast<std::uint32_t>(depth));
  ASSERT_EQ(s3_float.depth, static_cast<float>(depth));
  ASSERT_EQ(s3_double.depth, static_cast<double>(depth));
}

TYPED_TEST(SizeTest, SupportsArithmetic) {
  Size2<TypeParam> s2;
  Size2<TypeParam> s2_op;
  s2_op.set(this->Random(), this->Random());
  s2 = Size2<TypeParam>();
  s2 += s2_op;
  ASSERT_EQ(s2, s2_op);
  s2_op.set(this->Random(), this->Random());
  s2 = Size2<TypeParam>() + s2_op;
  ASSERT_EQ(s2, s2_op);
}

TYPED_TEST(SizeTest, SupportsScalarArithmetic) {
  Size2<TypeParam> s2;
  TypeParam scalar;
  scalar = this->Random();
  s2 = Size2<TypeParam>();
  s2 += scalar;
  ASSERT_EQ(s2.width, scalar);
  ASSERT_EQ(s2.height, scalar);
  scalar = this->Random();
  s2 = Size2<TypeParam>() + scalar;
  ASSERT_EQ(s2.width, scalar);
  ASSERT_EQ(s2.height, scalar);
}

}  // namespace math
}  // namespace solas
