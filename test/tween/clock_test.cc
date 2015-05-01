//
//  tween/interval_test.cc
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

#include <chrono>
#include <thread>

#include "gtest/gtest.h"

#include "solas/tween/clock.h"

namespace solas {
namespace tween {

TEST(ClockTest, DefaultConstructible) {
  Clock<Time> time_clock;
  Clock<Frame> frame_clock;
  ASSERT_NE(time_clock.now(), Time());
  ASSERT_NE(frame_clock.now(), Frame());
}

TEST(ClockTest, CopyConstructible) {
  Clock<Time> time_clock1;
  Clock<Frame> frame_clock1;
  Clock<Time> time_clock2(time_clock1);
  Clock<Frame> frame_clock2(frame_clock1);
  ASSERT_EQ(time_clock1, time_clock2);
  ASSERT_EQ(frame_clock1, frame_clock2);
}

TEST(ClockTest, Assignable) {
  Clock<Time> time_clock1;
  Clock<Frame> frame_clock1;
  Clock<Time> time_clock2;
  Clock<Frame> frame_clock2;
  time_clock2 = time_clock1;
  frame_clock2 = frame_clock1;
  ASSERT_EQ(time_clock1, time_clock2);
  ASSERT_EQ(frame_clock1, frame_clock2);
}

TEST(ClockTest, Advance) {
  Clock<Time> time_clock;
  auto time = time_clock.now();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  time_clock.advance();
  ASSERT_GE((time_clock.now() - time).count(), 0.5);
  ASSERT_NEAR((time_clock.now() - time).count(), 0.5, 1.0 / 60.0);
  Clock<Frame> frame_clock;
  auto frame = frame_clock.now();
  frame_clock.advance();
  ASSERT_EQ((frame_clock.now() - frame).count(), 1);
}

}  // namespace tween
}  // namespace solas
