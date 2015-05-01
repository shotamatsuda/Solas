//
//  solas/utility/benchmark.cc
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

#include "solas/utility/benchmark.h"

#include <chrono>

namespace solas {
namespace utility {

template <> const char * Benchmark<std::chrono::nanoseconds>::suffix = "ns";
template <> const char * Benchmark<std::chrono::microseconds>::suffix = "us";
template <> const char * Benchmark<std::chrono::milliseconds>::suffix = "ms";
template <> const char * Benchmark<std::chrono::seconds>::suffix = "s";
template <> const char * Benchmark<std::chrono::minutes>::suffix = "m";
template <> const char * Benchmark<std::chrono::hours>::suffix = "h";

}  // namespace utility
}  // namespace solas
