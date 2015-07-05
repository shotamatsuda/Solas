//
//  solas/utility/date_time.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
#ifndef SOLAS_UTILITY_DATE_TIME_H_
#define SOLAS_UTILITY_DATE_TIME_H_

#include <chrono>
#include <ctime>

namespace solas {
namespace utility {

int Year();
int Month();
int Day();
int Hour();
int Minute();
int Second();

#pragma mark -

inline int Year() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_year;
}

inline int Month() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mon + 1;
}

inline int Day() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mday;
}

inline int Hour() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_hour;
}

inline int Minute() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_min;
}

inline int Second() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_sec;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_DATE_TIME_H_
