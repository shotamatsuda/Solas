//
//  solas/utility/null_mutex.h
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
#ifndef SOLAS_UTILITY_NULL_MUTEX_H_
#define SOLAS_UTILITY_NULL_MUTEX_H_

namespace solas {
namespace utility {

class NullMutex final {
 public:
  // Constructors
  NullMutex() = default;

  // Disallow copy and assign
  NullMutex& operator=(const NullMutex& other) = delete;
  NullMutex(const NullMutex& other) = delete;

  // Lockable concept
  void lock() {}
  void unlock() {}
  bool try_lock() { return true; }
};

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_NULL_MUTEX_H_
