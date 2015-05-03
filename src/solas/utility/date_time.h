//
//  solas/utility/date_time.h
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
