//
//  solas/dispatch.mm
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

#include "solas/dispatch.h"

#include <dispatch/dispatch.h>
#include <Foundation/Foundation.h>

#include <cassert>

namespace solas {
namespace thread {

namespace {

inline long prioritize(Queue queue) {
  switch (queue) {
    case Queue::HIGH:
      return DISPATCH_QUEUE_PRIORITY_HIGH;
    case Queue::DEFAULT:
      return DISPATCH_QUEUE_PRIORITY_DEFAULT;
    case Queue::LOW:
      return DISPATCH_QUEUE_PRIORITY_LOW;
    case Queue::BACKGROUND:
      return DISPATCH_QUEUE_PRIORITY_BACKGROUND;
    default:
      assert(false);
      break;
  }
  return DISPATCH_QUEUE_PRIORITY_DEFAULT;
}

}  // namespace

void async(Queue queue, const std::function<void()>& task) {
  auto captured_task = task;
  dispatch_block_t block = ^{ @autoreleasepool { captured_task(); } };
  if (queue == Queue::MAIN) {
    dispatch_async(dispatch_get_main_queue(), block);
  } else {
    auto global_queue = dispatch_get_global_queue(prioritize(queue), 0);
    dispatch_async(global_queue, block);
  }
}

void sync(Queue queue, const std::function<void()>& task) {
  dispatch_block_t block = ^{ @autoreleasepool { task(); } };
  if (queue == Queue::MAIN) {
    if ([NSThread isMainThread]) {
      task();
    } else {
      dispatch_sync(dispatch_get_main_queue(), block);
    }
  } else {
    auto global_queue = dispatch_get_global_queue(prioritize(queue), 0);
    dispatch_async(global_queue, block);
  }
}

}  // namespace thread
}  // namespace solas
