//
//  solas/run.mm
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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

#include "solas/run.h"

#include <atomic>
#include <cassert>
#include <cstdlib>
#include <mutex>

#import "SLSApplicationMain.h"

namespace solas {

std::atomic<Run *> Run::instance_;
std::mutex Run::instance_mutex_;
bool Run::instance_deleted_;

#pragma mark Singleton

Run& Run::instance() {
  auto instance = instance_.load(std::memory_order_consume);
  if (!instance) {
    std::lock_guard<std::mutex> lock(instance_mutex_);
    instance = instance_.load(std::memory_order_consume);
    if (!instance) {
      assert(!instance_deleted_);
      instance = new Run;
      instance_.store(instance, std::memory_order_release);
      std::atexit(&deleteInstance);
    }
  }
  return *instance;
}

inline void Run::deleteInstance() {
  std::lock_guard<std::mutex> lock(instance_mutex_);
  delete instance_.exchange(nullptr);
  instance_deleted_ = true;
}

#pragma mark -

int run(int argc, char **argv) {
  return SLSApplicationMain(argc, argv);
}

}  // namespace solas
