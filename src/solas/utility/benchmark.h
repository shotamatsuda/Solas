//
//  solas/utility/benchmark.h
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
  Benchmark(const Benchmark& other) = delete;
  Benchmark& operator=(const Benchmark& other) = delete;

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
