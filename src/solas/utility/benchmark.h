//
//  solas/utility/benchmark.h
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
#ifndef SOLAS_UTILITY_BENCHMARK_H_
#define SOLAS_UTILITY_BENCHMARK_H_

#include <chrono>
#include <ostream>

namespace solas {
namespace utility {

template <typename Duration = std::chrono::milliseconds>
class Benchmark final {
 public:
  // Constructors
  Benchmark() = default;
  template <typename Task>
  Benchmark(Task task);

  // Disallow copy and assign
  Benchmark(const Benchmark& otherother) = delete;
  Benchmark& operator=(const Benchmark& otherother) = delete;

  // Benchmarking
  void start();
  void stop();

  // Attributes
  Duration duration() const;
  typename Duration::rep count() const;

 public:
  // Suffix for duration
  static const char *suffix;

 private:
  // Time points
  std::chrono::high_resolution_clock::time_point started_time_;
  std::chrono::high_resolution_clock::time_point stopped_time_;
};

#pragma mark -

template <typename Duration>
template <typename Task>
inline Benchmark<Duration>::Benchmark(Task task) {
  start();
  task();
  stop();
}

#pragma mark Benchmarking

template <typename Duration>
inline void Benchmark<Duration>::start() {
  started_time_ = std::chrono::high_resolution_clock::now();
}

template <typename Duration>
inline void Benchmark<Duration>::stop() {
  stopped_time_ = std::chrono::high_resolution_clock::now();
}

#pragma mark Attributes

template <typename Duration>
Duration Benchmark<Duration>::duration() const {
  return std::chrono::duration_cast<Duration>(stopped_time_ - started_time_);
}

template <typename Duration>
typename Duration::rep Benchmark<Duration>::count() const {
  return duration().count();
}

#pragma mark Stream

template <typename Duration>
inline std::ostream& operator<<(
    std::ostream& os, const Benchmark<Duration>& benchmark) {
  return os << benchmark.count() << " " << benchmark.suffix;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_BENCHMARK_H_
