//
//  solas/utility/singleton.h
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
#ifndef SOLAS_UTILITY_SINGLETON_H_
#define SOLAS_UTILITY_SINGLETON_H_

#include <atomic>
#include <memory>
#include <mutex>

namespace solas {
namespace utility {

template <typename T, typename Deleter = std::default_delete<T>>
class Singleton final {
 public:
  using Type = T;

 public:
  // Constructors
  Singleton();
  ~Singleton();

  // Disallow copy and assign
  Singleton(const Singleton& other) = delete;
  Singleton& operator=(const Singleton& other) = delete;

  // Accessing the instance
  T * get();
  const T * get() const { return get(); }
  T& operator*() { return *get(); }
  const T& operator*() const { return *get(); }
  T * operator->() { return get(); }
  const T * operator->() const { return get(); }

  // Implicit conversion
  operator T&() { return *get(); }
  const operator T&() const { return *get(); }

 private:
  std::atomic<T *> instance_;
  std::mutex mutex_;
};

#pragma mark -

template <typename T, typename Deleter>
inline Singleton<T, Deleter>::Singleton() : instance_(nullptr) {}

template <typename T, typename Deleter>
inline Singleton<T, Deleter>::~Singleton() {
  Deleter()(get());
}

#pragma mark Accessing the instance

template <typename T, typename Deleter>
inline T * Singleton<T, Deleter>::get() {
  auto instance = instance_.load(std::memory_order_consume);
  if (!instance) {
    std::lock_guard<std::mutex> lock(mutex_);
    instance = instance_.load(std::memory_order_consume);
    if (!instance) {
      instance = new T();
      instance_.store(instance, std::memory_order_release);
    }
  }
  return instance;
}

}  // namespace utility
}  // namespace solas

#endif  // SOLAS_UTILITY_SINGLETON_H_
