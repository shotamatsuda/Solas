//
//  math/vector_test.cc
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

#include "solas/math/promotion.h"
#include "solas/math/random.h"
#include "solas/math/vector.h"

namespace solas {
namespace math {

template <typename T>
class VectorTest : public ::testing::Test {};

using Types = ::testing::Types<
  std::int8_t,
  std::uint8_t,
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  float,
  double
>;
TYPED_TEST_CASE(VectorTest, Types);

TYPED_TEST(VectorTest, DefaultConstructible) {
  {
    Vector2<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vector3<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector4<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  }
}

TYPED_TEST(VectorTest, ConstructibleWithValue) {
  const auto value = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
  } {
    Vector3<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
    ASSERT_EQ(v.z, value);
  } {
    Vector4<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
    ASSERT_EQ(v.z, value);
    ASSERT_EQ(v.w, value);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithValues) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v(x, y);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector3<TypeParam> v(x, y, z);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector4<TypeParam> v(x, y, z, w);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithTuple) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v(std::make_tuple(x, y));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector3<TypeParam> v(std::make_tuple(x, y, z));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector4<TypeParam> v(std::make_tuple(x, y, z, w));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithInitializerList) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v{};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vector2<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vector2<TypeParam> v{x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector2<TypeParam> v{x, y, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector3<TypeParam> v{};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v{x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v{x, y, z};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector3<TypeParam> v{x, y, z, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector4<TypeParam> v{};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v{x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v{x, y, z};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v{x, y, z, w};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  } {
    Vector4<TypeParam> v{x, y, z, w, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, CopyConstructible) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v1(x, y);
    Vector2<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  } {
    Vector3<TypeParam> v1(x, y, z);
    Vector3<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  } {
    Vector4<TypeParam> v1(x, y, z, w);
    Vector4<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  }
}

TYPED_TEST(VectorTest, CopyAssignable) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v1(x, y);
    Vector2<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  } {
    Vector3<TypeParam> v1(x, y, z);
    Vector3<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  } {
    Vector4<TypeParam> v1(x, y, z, w);
    Vector4<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  }
}

TYPED_TEST(VectorTest, TupleAssignable) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v;
    v = std::make_tuple(x, y);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector3<TypeParam> v;
    v = std::make_tuple(x, y, z);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector4<TypeParam> v;
    v = std::make_tuple(x, y, z, w);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, InitializerListAssignable) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v;
    v = {};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vector2<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vector2<TypeParam> v;
    v = {x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector2<TypeParam> v;
    v = {x, y, math::Random<>::Shared().uniform<TypeParam>()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vector3<TypeParam> v;
    v = {};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v;
    v = {x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vector3<TypeParam> v;
    v = {x, y, z};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector3<TypeParam> v;
    v = {x, y, z, math::Random<>::Shared().uniform<TypeParam>()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vector4<TypeParam> v;
    v = {};
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v;
    v = {x, y};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v;
    v = {x, y, z};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vector4<TypeParam> v;
    v = {x, y, z, w};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  } {
    Vector4<TypeParam> v;
    v = {x, y, z, w, math::Random<>::Shared().uniform<TypeParam>()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto x = math::Random<>::Shared().uniform<TypeParam>();
  const auto y = math::Random<>::Shared().uniform<TypeParam>();
  const auto z = math::Random<>::Shared().uniform<TypeParam>();
  const auto w = math::Random<>::Shared().uniform<TypeParam>();
  {
    Vector2<TypeParam> v(x, y);
    Vector2<std::int8_t> v_int8(v);
    Vector2<std::uint8_t> v_uint8(v);
    Vector2<std::int16_t> v_int16(v);
    Vector2<std::uint16_t> v_uint16(v);
    Vector2<std::int32_t> v_int32(v);
    Vector2<std::uint32_t> v_uint32(v);
    Vector2<float> v_float(v);
    Vector2<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
  } {
    Vector3<TypeParam> v(x, y, z);
    Vector3<std::int8_t> v_int8(v);
    Vector3<std::uint8_t> v_uint8(v);
    Vector3<std::int16_t> v_int16(v);
    Vector3<std::uint16_t> v_uint16(v);
    Vector3<std::int32_t> v_int32(v);
    Vector3<std::uint32_t> v_uint32(v);
    Vector3<float> v_float(v);
    Vector3<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
    ASSERT_EQ(v_int8.z, static_cast<std::int8_t>(z));
    ASSERT_EQ(v_uint8.z, static_cast<std::uint8_t>(z));
    ASSERT_EQ(v_int16.z, static_cast<std::int16_t>(z));
    ASSERT_EQ(v_uint16.z, static_cast<std::uint16_t>(z));
    ASSERT_EQ(v_int32.z, static_cast<std::int32_t>(z));
    ASSERT_EQ(v_uint32.z, static_cast<std::uint32_t>(z));
    ASSERT_EQ(v_float.z, static_cast<float>(z));
    ASSERT_EQ(v_double.z, static_cast<double>(z));
  } {
    Vector4<TypeParam> v(x, y, z, w);
    Vector4<std::int8_t> v_int8(v);
    Vector4<std::uint8_t> v_uint8(v);
    Vector4<std::int16_t> v_int16(v);
    Vector4<std::uint16_t> v_uint16(v);
    Vector4<std::int32_t> v_int32(v);
    Vector4<std::uint32_t> v_uint32(v);
    Vector4<float> v_float(v);
    Vector4<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
    ASSERT_EQ(v_int8.z, static_cast<std::int8_t>(z));
    ASSERT_EQ(v_uint8.z, static_cast<std::uint8_t>(z));
    ASSERT_EQ(v_int16.z, static_cast<std::int16_t>(z));
    ASSERT_EQ(v_uint16.z, static_cast<std::uint16_t>(z));
    ASSERT_EQ(v_int32.z, static_cast<std::int32_t>(z));
    ASSERT_EQ(v_uint32.z, static_cast<std::uint32_t>(z));
    ASSERT_EQ(v_float.z, static_cast<float>(z));
    ASSERT_EQ(v_double.z, static_cast<double>(z));
    ASSERT_EQ(v_int8.w, static_cast<std::int8_t>(w));
    ASSERT_EQ(v_uint8.w, static_cast<std::uint8_t>(w));
    ASSERT_EQ(v_int16.w, static_cast<std::int16_t>(w));
    ASSERT_EQ(v_uint16.w, static_cast<std::uint16_t>(w));
    ASSERT_EQ(v_int32.w, static_cast<std::int32_t>(w));
    ASSERT_EQ(v_uint32.w, static_cast<std::uint32_t>(w));
    ASSERT_EQ(v_float.w, static_cast<float>(w));
    ASSERT_EQ(v_double.w, static_cast<double>(w));
  }
}

TYPED_TEST(VectorTest, SupportsArithmetic) {
  {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector2<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector2<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector2<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector2<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector3<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand.z);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector3<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand.z);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector3<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand.z);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector3<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand.z);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector4<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) + operand.w);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector4<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) - operand.w);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector4<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand.w);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    Vector4<TypeParam> operand(math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>(),
                               math::Random<>::Shared().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) / operand.w);
  }
}

TYPED_TEST(VectorTest, SupportsScalarArithmetic) {
  {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
  } {
    Vector2<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand);
  } {
    Vector3<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) + operand);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) - operand);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) / operand);
  } {
    Vector4<TypeParam> v(math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>(),
                         math::Random<>::Shared().uniform<TypeParam>());
    TypeParam operand = math::Random<>::Shared().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand);
  }
}

}  // namespace math
}  // namespace solas
