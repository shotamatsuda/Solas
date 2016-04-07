//
//  solas/run.h
//
//  The MIT License
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
#ifndef SOLAS_RUN_H_
#define SOLAS_RUN_H_

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>

#include "solas/runner.h"
#include "solas/run_options.h"

namespace solas {

template <class Runnable>
int run(int argc, char **argv, const RunOptions& options = RunOptions());
int run(int argc, char **argv);

class Run {
 public:
  // Disallow copy semantics
  Run(const Run&) = delete;
  Run& operator=(const Run&) = delete;

  // Singleton
  static Run& instance();

  // Configuring runners
  template <class Runnable>
  void set(const RunOptions& options = RunOptions());

  // Creating runners
  std::unique_ptr<Runner> create() const;
  const RunOptions& options() const { return options_; }

 private:
  Run() = default;
  static void deleteInstance();

 private:
  std::function<std::unique_ptr<Runner>()> invocation_;
  RunOptions options_;
  static std::atomic<Run *> instance_;
  static std::mutex instance_mutex_;
  static bool instance_deleted_;
};

#pragma mark -

template <class Runnable>
inline int run(int argc, char **argv, const RunOptions& options) {
  Run::instance().set<Runnable>(options);
  return run(argc, argv);
}

#pragma mark Configuring runners

template <class Runnable>
inline void Run::set(const RunOptions& options) {
  options_ = options;
  invocation_ = [this]() -> std::unique_ptr<Runner> {
    return std::make_unique<Runner>(std::make_unique<Runnable>(),
                                    options_.runner());
  };
}

#pragma mark Creating runners

inline std::unique_ptr<Runner> Run::create() const {
  if (invocation_) {
    return invocation_();
  }
  return std::unique_ptr<Runner>();
}

}  // namespace solas

#endif  // SOLAS_RUN_H_
