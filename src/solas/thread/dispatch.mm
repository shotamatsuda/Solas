//
//  solas/thread/dispatch.mm
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

#include "solas/thread/dispatch.h"

#include <dispatch/dispatch.h>
#include <Foundation/Foundation.h>

#include <cassert>

namespace solas {
namespace thread {

namespace {

inline long Prioritize(Queue queue) {
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

void Async(Queue queue, const std::function<void()>& task) {
  auto captured_task = task;
  dispatch_block_t block = ^{ @autoreleasepool { captured_task(); } };
  if (queue == Queue::MAIN) {
    dispatch_async(dispatch_get_main_queue(), block);
  } else {
    auto global_queue = dispatch_get_global_queue(Prioritize(queue), 0);
    dispatch_async(global_queue, block);
  }
}

void Sync(Queue queue, const std::function<void()>& task) {
  dispatch_block_t block = ^{ @autoreleasepool { task(); } };
  if (queue == Queue::MAIN) {
    if ([NSThread isMainThread]) {
      task();
    } else {
      dispatch_sync(dispatch_get_main_queue(), block);
    }
  } else {
    auto global_queue = dispatch_get_global_queue(Prioritize(queue), 0);
    dispatch_async(global_queue, block);
  }
}

}  // namespace thread
}  // namespace solas
