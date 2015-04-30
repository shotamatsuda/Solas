//
//  solas/utility/singleton.h
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
  Singleton() = default;
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
