//
//  solas/date_time.h
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
#ifndef SOLAS_DATE_TIME_H_
#define SOLAS_DATE_TIME_H_

#include <chrono>
#include <ctime>

namespace solas {

int year();
int month();
int day();
int hour();
int minute();
int second();

#pragma mark -

inline int year() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_year;
}

inline int month() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mon + 1;
}

inline int day() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_mday;
}

inline int hour() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_hour;
}

inline int minute() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_min;
}

inline int second() {
  using Clock = std::chrono::system_clock;
  const auto now = Clock::to_time_t(Clock::now());
  return std::localtime(&now)->tm_sec;
}

}  // namespace solas

#endif  // SOLAS_DATE_TIME_H_
