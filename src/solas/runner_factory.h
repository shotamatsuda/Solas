//
//  solas/runner_factory.h
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
#ifndef SOLAS_RUNNER_FACTORY_H_
#define SOLAS_RUNNER_FACTORY_H_

#include <functional>
#include <memory>

#include "solas/runner.h"
#include "solas/runner_options.h"
#include "solas/singleton.h"

namespace solas {

class RunnerFactory final {
 private:
  friend class solas::Singleton<RunnerFactory>;

 public:
  // Disallow copy and assign
  RunnerFactory(const RunnerFactory& other) = delete;
  RunnerFactory& operator=(const RunnerFactory& other) = delete;

  // Factory
  static RunnerFactory& Shared();

  // Configuring runners
  template <class Runnable>
  void set(const RunnerOptions& options = RunnerOptions());

  // Creating runners
  std::unique_ptr<Runner> create() const;
  const RunnerOptions& options() const { return options_; }

 private:
  // Constructors
  RunnerFactory() = default;

 private:
  std::function<std::unique_ptr<Runner>()> invocation_;
  RunnerOptions options_;
};

#pragma mark -

#pragma mark Configuring runners

template <class Runnable>
inline void RunnerFactory::set(const RunnerOptions& options) {
  options_ = options;
  invocation_ = []() -> std::unique_ptr<Runner> {
    return std::make_unique<Runner>(std::make_unique<Runnable>());
  };
}

#pragma mark Creating runners

inline std::unique_ptr<Runner> RunnerFactory::create() const {
  if (invocation_) {
    return invocation_();
  }
  return std::unique_ptr<Runner>();
}

}  // namespace solas

#endif  // SOLAS_RUNNER_FACTORY_H_
