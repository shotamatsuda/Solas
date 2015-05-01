//
//  solas/thread/dispatch.h
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
#ifndef SOLAS_THREAD_DISPATCH_H_
#define SOLAS_THREAD_DISPATCH_H_

#include <functional>

namespace solas {
namespace thread {

enum class Queue {
  MAIN,
  HIGH,
  DEFAULT,
  LOW,
  BACKGROUND
};

void Async(Queue queue, const std::function<void()>& task);
void Sync(Queue queue, const std::function<void()>& task);

}  // namespace thread
}  // namespace solas

#endif  // SOLAS_THREAD_DISPATCH_H_
