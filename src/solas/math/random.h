//
//  solas/math/random.h
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

#pragma once
#ifndef SOLAS_MATH_RANDOM_H_
#define SOLAS_MATH_RANDOM_H_

#include <cassert>
#include <limits>
#include <mutex>
#include <random>

#include "solas/math/promotion.h"
#include "solas/thread/null_mutex.h"
#include "solas/utility/singleton.h"

namespace solas {
namespace math {

template <typename Engine = std::mt19937, typename Mutex = utility::NullMutex>
class Random {
 public:
  using Type = typename Engine::result_type;

 public:
  // Constructors
  Random() = default;
  explicit Random(Type seed);

  // Copy and assign
  Random(const Random& other) = default;
  Random(Random&& other) = default;
  Random& operator=(const Random& other) = default;
  Random& operator=(Random&& other) = default;

  // Shared instance
  static Random<Engine, std::mutex>& Shared();

  // Random generation
  void seed(Type value);
  void randomize();
  Type next();
  template <typename Distribution>
  Type next(Distribution *distribution);

  // Distribution
  template <typename T>
  T uniform();
  template <typename T>
  T uniform(T max);
  template <typename T>
  T uniform(T min, T max);
  template <typename T>
  T normal();
  template <typename T>
  T normal(Promote<T> mean, Promote<T> stddev);

 private:
  Engine engine_;
  Mutex mutex_;
  static utility::Singleton<Random<Engine, std::mutex>> shared_;
};

template <typename Engine, typename Mutex>
utility::Singleton<Random<Engine, std::mutex>> Random<Engine, Mutex>::shared_;

#pragma mark -

template <typename Engine, typename Mutex>
inline Random<Engine, Mutex>::Random(Type seed)
    : engine_(seed) {}

#pragma Shared instance

template <typename Engine, typename Mutex>
inline Random<Engine, std::mutex>& Random<Engine, Mutex>::Shared() {
  return *shared_;
}

#pragma mark Random generation

template <typename Engine, typename Mutex>
inline void Random<Engine, Mutex>::seed(Type value) {
  std::lock_guard<Mutex> lock(mutex_);
  engine_.seed(value);
}

template <typename Engine, typename Mutex>
inline void Random<Engine, Mutex>::randomize() {
  std::lock_guard<Mutex> lock(mutex_);
  engine_.seed(std::random_device()());
}

template <typename Engine, typename Mutex>
inline typename Random<Engine, Mutex>::Type Random<Engine, Mutex>::next() {
  std::lock_guard<Mutex> lock(mutex_);
  return engine_();
}

template <typename Engine, typename Mutex>
template <typename Distribution>
inline typename Random<Engine, Mutex>::Type Random<Engine, Mutex>::next(
    Distribution *distribution) {
  assert(distribution);
  std::lock_guard<Mutex> lock(mutex_);
  return (*distribution)(engine_);
}

#pragma mark Distribution

template <typename Engine, typename Mutex>
template <typename T>
inline T Random<Engine, Mutex>::uniform() {
  return uniform<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::max());
}

template <typename Engine, typename Mutex>
template <typename T>
inline T Random<Engine, Mutex>::uniform(T max) {
  return uniform<T>(T(), max);
}

template <typename Engine, typename Mutex>
template <typename T>
inline T Random<Engine, Mutex>::uniform(T min, T max) {
  std::lock_guard<Mutex> lock(mutex_);
  using distribution = typename std::conditional<
      std::is_integral<T>::value,
      std::uniform_int_distribution<T>,
      std::uniform_real_distribution<T>>::type;
  return distribution(min, max)(engine_);
}

template <typename Engine, typename Mutex>
template <typename T>
inline T Random<Engine, Mutex>::normal() {
  std::lock_guard<Mutex> lock(mutex_);
  return std::normal_distribution<Promote<T>>()(engine_);
}

template <typename Engine, typename Mutex>
template <typename T>
inline T Random<Engine, Mutex>::normal(Promote<T> mean, Promote<T> stddev) {
  std::lock_guard<Mutex> lock(mutex_);
  return std::normal_distribution<Promote<T>>(mean, stddev)(engine_);
}

}  // namespace math
}  // namespace solas

#endif  // SOLAS_MATH_RANDOM_H_
