//
//  math/vector_test.cc
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#include <cstdint>
#include <random>
#include <type_traits>

#include "gtest/gtest.h"

#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T>
class VectorTest : public ::testing::Test {
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
  std::int64_t,
  std::uint64_t,
  float,
  double
>;
TYPED_TEST_CASE(VectorTest, Types);

TYPED_TEST(VectorTest, DefaultConstructible) {
  Vector2<TypeParam> v2;
  ASSERT_EQ(v2.x, TypeParam());
  ASSERT_EQ(v2.y, TypeParam());

  Vector3<TypeParam> v3;
  ASSERT_EQ(v3.x, TypeParam());
  ASSERT_EQ(v3.y, TypeParam());
  ASSERT_EQ(v3.z, TypeParam());

  Vector4<TypeParam> v4;
  ASSERT_EQ(v4.x, TypeParam());
  ASSERT_EQ(v4.y, TypeParam());
  ASSERT_EQ(v4.z, TypeParam());
  ASSERT_EQ(v4.w, TypeParam());
}

TYPED_TEST(VectorTest, ConstructibleWithValue) {
  const auto value = this->Random();

  Vector2<TypeParam> v2(value);
  ASSERT_EQ(v2.x, value);
  ASSERT_EQ(v2.y, value);

  Vector3<TypeParam> v3(value);
  ASSERT_EQ(v3.x, value);
  ASSERT_EQ(v3.y, value);
  ASSERT_EQ(v3.z, value);

  Vector4<TypeParam> v4(value);
  ASSERT_EQ(v4.x, value);
  ASSERT_EQ(v4.y, value);
  ASSERT_EQ(v4.z, value);
  ASSERT_EQ(v4.w, value);
}

TYPED_TEST(VectorTest, ConstructibleWithValues) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto z = this->Random();
  const auto w = this->Random();

  Vector2<TypeParam> v2(x, y);
  ASSERT_EQ(v2.x, x);
  ASSERT_EQ(v2.y, y);

  Vector3<TypeParam> v3(x, y, z);
  ASSERT_EQ(v3.x, x);
  ASSERT_EQ(v3.y, y);
  ASSERT_EQ(v3.z, z);

  Vector4<TypeParam> v4(x, y, z, w);
  ASSERT_EQ(v4.x, x);
  ASSERT_EQ(v4.y, y);
  ASSERT_EQ(v4.z, z);
  ASSERT_EQ(v4.w, w);
}

TYPED_TEST(VectorTest, ConstructibleWithInitializerList) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto z = this->Random();
  const auto w = this->Random();

  Vector2<TypeParam> v2_1{};
  ASSERT_EQ(v2_1.x, TypeParam());
  ASSERT_EQ(v2_1.y, TypeParam());
  Vector2<TypeParam> v2_2{x};
  ASSERT_EQ(v2_2.x, x);
  ASSERT_EQ(v2_2.y, TypeParam());
  Vector2<TypeParam> v2_3{x, y};
  ASSERT_EQ(v2_3.x, x);
  ASSERT_EQ(v2_3.y, y);
  Vector2<TypeParam> v2_4{x, y, this->Random()};
  ASSERT_EQ(v2_4.x, x);
  ASSERT_EQ(v2_4.y, y);

  Vector3<TypeParam> v3_1{};
  ASSERT_EQ(v3_1.x, TypeParam());
  ASSERT_EQ(v3_1.y, TypeParam());
  ASSERT_EQ(v3_1.z, TypeParam());
  Vector3<TypeParam> v3_2{x};
  ASSERT_EQ(v3_2.x, x);
  ASSERT_EQ(v3_2.y, TypeParam());
  ASSERT_EQ(v3_2.z, TypeParam());
  Vector3<TypeParam> v3_3{x, y};
  ASSERT_EQ(v3_3.x, x);
  ASSERT_EQ(v3_3.y, y);
  ASSERT_EQ(v3_3.z, TypeParam());
  Vector3<TypeParam> v3_4{x, y, z};
  ASSERT_EQ(v3_4.x, x);
  ASSERT_EQ(v3_4.y, y);
  ASSERT_EQ(v3_4.z, z);
  Vector3<TypeParam> v3_5{x, y, z, this->Random()};
  ASSERT_EQ(v3_5.x, x);
  ASSERT_EQ(v3_5.y, y);
  ASSERT_EQ(v3_5.z, z);

  Vector4<TypeParam> v4_1{};
  ASSERT_EQ(v4_1.x, TypeParam());
  ASSERT_EQ(v4_1.y, TypeParam());
  ASSERT_EQ(v4_1.z, TypeParam());
  ASSERT_EQ(v4_1.w, TypeParam());
  Vector4<TypeParam> v4_2{x};
  ASSERT_EQ(v4_2.x, x);
  ASSERT_EQ(v4_2.y, TypeParam());
  ASSERT_EQ(v4_2.z, TypeParam());
  ASSERT_EQ(v4_2.w, TypeParam());
  Vector4<TypeParam> v4_3{x, y};
  ASSERT_EQ(v4_3.x, x);
  ASSERT_EQ(v4_3.y, y);
  ASSERT_EQ(v4_3.z, TypeParam());
  ASSERT_EQ(v4_3.w, TypeParam());
  Vector4<TypeParam> v4_4{x, y, z};
  ASSERT_EQ(v4_4.x, x);
  ASSERT_EQ(v4_4.y, y);
  ASSERT_EQ(v4_4.z, z);
  ASSERT_EQ(v4_4.w, TypeParam());
  Vector4<TypeParam> v4_5{x, y, z, w};
  ASSERT_EQ(v4_5.x, x);
  ASSERT_EQ(v4_5.y, y);
  ASSERT_EQ(v4_5.z, z);
  ASSERT_EQ(v4_5.w, w);
  Vector4<TypeParam> v4_6{x, y, z, w, this->Random()};
  ASSERT_EQ(v4_6.x, x);
  ASSERT_EQ(v4_6.y, y);
  ASSERT_EQ(v4_6.z, z);
  ASSERT_EQ(v4_6.w, w);
}

TYPED_TEST(VectorTest, CopyConstructible) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto z = this->Random();
  const auto w = this->Random();

  Vector2<TypeParam> v2_1(x, y);
  Vector2<TypeParam> v2_2(v2_1);
  ASSERT_EQ(v2_1, v2_2);

  Vector3<TypeParam> v3_1(x, y, z);
  Vector3<TypeParam> v3_2(v3_1);
  ASSERT_EQ(v3_1, v3_2);

  Vector4<TypeParam> v4_1(x, y, z, w);
  Vector4<TypeParam> v4_2(v4_1);
  ASSERT_EQ(v4_1, v4_2);
}

TYPED_TEST(VectorTest, CopyAssignable) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto z = this->Random();
  const auto w = this->Random();

  Vector2<TypeParam> v2_1(x, y);
  Vector2<TypeParam> v2_2;
  v2_2 = v2_1;
  ASSERT_EQ(v2_1, v2_2);

  Vector3<TypeParam> v3_1(x, y, z);
  Vector3<TypeParam> v3_2;
  v3_2 = v3_1;
  ASSERT_EQ(v3_1, v3_2);

  Vector4<TypeParam> v4_1(x, y, z, w);
  Vector4<TypeParam> v4_2;
  v4_2 = v4_1;
  ASSERT_EQ(v4_1, v4_2);
}

TYPED_TEST(VectorTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto z = this->Random();
  const auto w = this->Random();

  Vector2<TypeParam> v2(x, y);
  Vector2<bool> v2_bool(v2);
  Vector2<char> v2_char(v2);
  Vector2<std::int8_t> v2_int8(v2);
  Vector2<std::uint8_t> v2_uint8(v2);
  Vector2<std::int16_t> v2_int16(v2);
  Vector2<std::uint16_t> v2_uint16(v2);
  Vector2<std::int32_t> v2_int32(v2);
  Vector2<std::uint32_t> v2_uint32(v2);
  Vector2<std::int64_t> v2_int64(v2);
  Vector2<std::uint64_t> v2_uint64(v2);
  Vector2<float> v2_float(v2);
  Vector2<double> v2_double(v2);
  ASSERT_EQ(v2_bool.x, static_cast<bool>(x));
  ASSERT_EQ(v2_char.x, static_cast<char>(x));
  ASSERT_EQ(v2_int8.x, static_cast<std::int8_t>(x));
  ASSERT_EQ(v2_uint8.x, static_cast<std::uint8_t>(x));
  ASSERT_EQ(v2_int16.x, static_cast<std::int16_t>(x));
  ASSERT_EQ(v2_uint16.x, static_cast<std::uint16_t>(x));
  ASSERT_EQ(v2_int32.x, static_cast<std::int32_t>(x));
  ASSERT_EQ(v2_uint32.x, static_cast<std::uint32_t>(x));
  ASSERT_EQ(v2_int64.x, static_cast<std::int64_t>(x));
  ASSERT_EQ(v2_uint64.x, static_cast<std::uint64_t>(x));
  ASSERT_EQ(v2_float.x, static_cast<float>(x));
  ASSERT_EQ(v2_double.x, static_cast<double>(x));
  ASSERT_EQ(v2_bool.y, static_cast<bool>(y));
  ASSERT_EQ(v2_char.y, static_cast<char>(y));
  ASSERT_EQ(v2_int8.y, static_cast<std::int8_t>(y));
  ASSERT_EQ(v2_uint8.y, static_cast<std::uint8_t>(y));
  ASSERT_EQ(v2_int16.y, static_cast<std::int16_t>(y));
  ASSERT_EQ(v2_uint16.y, static_cast<std::uint16_t>(y));
  ASSERT_EQ(v2_int32.y, static_cast<std::int32_t>(y));
  ASSERT_EQ(v2_uint32.y, static_cast<std::uint32_t>(y));
  ASSERT_EQ(v2_int64.y, static_cast<std::int64_t>(y));
  ASSERT_EQ(v2_uint64.y, static_cast<std::uint64_t>(y));
  ASSERT_EQ(v2_float.y, static_cast<float>(y));
  ASSERT_EQ(v2_double.y, static_cast<double>(y));

  Vector3<TypeParam> v3(x, y, z);
  Vector3<bool> v3_bool(v3);
  Vector3<char> v3_char(v3);
  Vector3<std::int8_t> v3_int8(v3);
  Vector3<std::uint8_t> v3_uint8(v3);
  Vector3<std::int16_t> v3_int16(v3);
  Vector3<std::uint16_t> v3_uint16(v3);
  Vector3<std::int32_t> v3_int32(v3);
  Vector3<std::uint32_t> v3_uint32(v3);
  Vector3<std::int64_t> v3_int64(v3);
  Vector3<std::uint64_t> v3_uint64(v3);
  Vector3<float> v3_float(v3);
  Vector3<double> v3_double(v3);
  ASSERT_EQ(v3_bool.x, static_cast<bool>(x));
  ASSERT_EQ(v3_char.x, static_cast<char>(x));
  ASSERT_EQ(v3_int8.x, static_cast<std::int8_t>(x));
  ASSERT_EQ(v3_uint8.x, static_cast<std::uint8_t>(x));
  ASSERT_EQ(v3_int16.x, static_cast<std::int16_t>(x));
  ASSERT_EQ(v3_uint16.x, static_cast<std::uint16_t>(x));
  ASSERT_EQ(v3_int32.x, static_cast<std::int32_t>(x));
  ASSERT_EQ(v3_uint32.x, static_cast<std::uint32_t>(x));
  ASSERT_EQ(v3_int64.x, static_cast<std::int64_t>(x));
  ASSERT_EQ(v3_uint64.x, static_cast<std::uint64_t>(x));
  ASSERT_EQ(v3_float.x, static_cast<float>(x));
  ASSERT_EQ(v3_double.x, static_cast<double>(x));
  ASSERT_EQ(v3_bool.y, static_cast<bool>(y));
  ASSERT_EQ(v3_char.y, static_cast<char>(y));
  ASSERT_EQ(v3_int8.y, static_cast<std::int8_t>(y));
  ASSERT_EQ(v3_uint8.y, static_cast<std::uint8_t>(y));
  ASSERT_EQ(v3_int16.y, static_cast<std::int16_t>(y));
  ASSERT_EQ(v3_uint16.y, static_cast<std::uint16_t>(y));
  ASSERT_EQ(v3_int32.y, static_cast<std::int32_t>(y));
  ASSERT_EQ(v3_uint32.y, static_cast<std::uint32_t>(y));
  ASSERT_EQ(v3_int64.y, static_cast<std::int64_t>(y));
  ASSERT_EQ(v3_uint64.y, static_cast<std::uint64_t>(y));
  ASSERT_EQ(v3_float.y, static_cast<float>(y));
  ASSERT_EQ(v3_double.y, static_cast<double>(y));
  ASSERT_EQ(v3_bool.z, static_cast<bool>(z));
  ASSERT_EQ(v3_char.z, static_cast<char>(z));
  ASSERT_EQ(v3_int8.z, static_cast<std::int8_t>(z));
  ASSERT_EQ(v3_uint8.z, static_cast<std::uint8_t>(z));
  ASSERT_EQ(v3_int16.z, static_cast<std::int16_t>(z));
  ASSERT_EQ(v3_uint16.z, static_cast<std::uint16_t>(z));
  ASSERT_EQ(v3_int32.z, static_cast<std::int32_t>(z));
  ASSERT_EQ(v3_uint32.z, static_cast<std::uint32_t>(z));
  ASSERT_EQ(v3_int64.z, static_cast<std::int64_t>(z));
  ASSERT_EQ(v3_uint64.z, static_cast<std::uint64_t>(z));
  ASSERT_EQ(v3_float.z, static_cast<float>(z));
  ASSERT_EQ(v3_double.z, static_cast<double>(z));

  Vector4<TypeParam> v4(x, y, z, w);
  Vector4<bool> v4_bool(v4);
  Vector4<char> v4_char(v4);
  Vector4<std::int8_t> v4_int8(v4);
  Vector4<std::uint8_t> v4_uint8(v4);
  Vector4<std::int16_t> v4_int16(v4);
  Vector4<std::uint16_t> v4_uint16(v4);
  Vector4<std::int32_t> v4_int32(v4);
  Vector4<std::uint32_t> v4_uint32(v4);
  Vector4<std::int64_t> v4_int64(v4);
  Vector4<std::uint64_t> v4_uint64(v4);
  Vector4<float> v4_float(v4);
  Vector4<double> v4_double(v4);
  ASSERT_EQ(v4_bool.x, static_cast<bool>(x));
  ASSERT_EQ(v4_char.x, static_cast<char>(x));
  ASSERT_EQ(v4_int8.x, static_cast<std::int8_t>(x));
  ASSERT_EQ(v4_uint8.x, static_cast<std::uint8_t>(x));
  ASSERT_EQ(v4_int16.x, static_cast<std::int16_t>(x));
  ASSERT_EQ(v4_uint16.x, static_cast<std::uint16_t>(x));
  ASSERT_EQ(v4_int32.x, static_cast<std::int32_t>(x));
  ASSERT_EQ(v4_uint32.x, static_cast<std::uint32_t>(x));
  ASSERT_EQ(v4_int64.x, static_cast<std::int64_t>(x));
  ASSERT_EQ(v4_uint64.x, static_cast<std::uint64_t>(x));
  ASSERT_EQ(v4_float.x, static_cast<float>(x));
  ASSERT_EQ(v4_double.x, static_cast<double>(x));
  ASSERT_EQ(v4_bool.y, static_cast<bool>(y));
  ASSERT_EQ(v4_char.y, static_cast<char>(y));
  ASSERT_EQ(v4_int8.y, static_cast<std::int8_t>(y));
  ASSERT_EQ(v4_uint8.y, static_cast<std::uint8_t>(y));
  ASSERT_EQ(v4_int16.y, static_cast<std::int16_t>(y));
  ASSERT_EQ(v4_uint16.y, static_cast<std::uint16_t>(y));
  ASSERT_EQ(v4_int32.y, static_cast<std::int32_t>(y));
  ASSERT_EQ(v4_uint32.y, static_cast<std::uint32_t>(y));
  ASSERT_EQ(v4_int64.y, static_cast<std::int64_t>(y));
  ASSERT_EQ(v4_uint64.y, static_cast<std::uint64_t>(y));
  ASSERT_EQ(v4_float.y, static_cast<float>(y));
  ASSERT_EQ(v4_double.y, static_cast<double>(y));
  ASSERT_EQ(v4_bool.z, static_cast<bool>(z));
  ASSERT_EQ(v4_char.z, static_cast<char>(z));
  ASSERT_EQ(v4_int8.z, static_cast<std::int8_t>(z));
  ASSERT_EQ(v4_uint8.z, static_cast<std::uint8_t>(z));
  ASSERT_EQ(v4_int16.z, static_cast<std::int16_t>(z));
  ASSERT_EQ(v4_uint16.z, static_cast<std::uint16_t>(z));
  ASSERT_EQ(v4_int32.z, static_cast<std::int32_t>(z));
  ASSERT_EQ(v4_uint32.z, static_cast<std::uint32_t>(z));
  ASSERT_EQ(v4_int64.z, static_cast<std::int64_t>(z));
  ASSERT_EQ(v4_uint64.z, static_cast<std::uint64_t>(z));
  ASSERT_EQ(v4_float.z, static_cast<float>(z));
  ASSERT_EQ(v4_double.z, static_cast<double>(z));
  ASSERT_EQ(v4_bool.w, static_cast<bool>(w));
  ASSERT_EQ(v4_char.w, static_cast<char>(w));
  ASSERT_EQ(v4_int8.w, static_cast<std::int8_t>(w));
  ASSERT_EQ(v4_uint8.w, static_cast<std::uint8_t>(w));
  ASSERT_EQ(v4_int16.w, static_cast<std::int16_t>(w));
  ASSERT_EQ(v4_uint16.w, static_cast<std::uint16_t>(w));
  ASSERT_EQ(v4_int32.w, static_cast<std::int32_t>(w));
  ASSERT_EQ(v4_uint32.w, static_cast<std::uint32_t>(w));
  ASSERT_EQ(v4_int64.w, static_cast<std::int64_t>(w));
  ASSERT_EQ(v4_uint64.w, static_cast<std::uint64_t>(w));
  ASSERT_EQ(v4_float.w, static_cast<float>(w));
  ASSERT_EQ(v4_double.w, static_cast<double>(w));
}

TYPED_TEST(VectorTest, SupportsArithmetic) {
  Vector2<TypeParam> v2;
  Vector2<TypeParam> v2_op;
  v2_op.set(this->Random(), this->Random());
  v2 = Vector2<TypeParam>();
  v2 += v2_op;
  ASSERT_EQ(v2, v2_op);
  v2_op.set(this->Random(), this->Random());
  v2 = Vector2<TypeParam>() + v2_op;
  ASSERT_EQ(v2, v2_op);
}

TYPED_TEST(VectorTest, SupportsScalarArithmetic) {
  Vector2<TypeParam> v2;
  TypeParam scalar;
  scalar = this->Random();
  v2 = Vector2<TypeParam>();
  v2 += scalar;
  ASSERT_EQ(v2.x, scalar);
  ASSERT_EQ(v2.y, scalar);
  scalar = this->Random();
  v2 = Vector2<TypeParam>() + scalar;
  ASSERT_EQ(v2.x, scalar);
  ASSERT_EQ(v2.y, scalar);
}

}  // namespace math
}  // namespace solas
