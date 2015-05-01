//
//  solas/app/runner_factory.h
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
#ifndef SOLAS_APP_RUNNER_FACTORY_H_
#define SOLAS_APP_RUNNER_FACTORY_H_

#include <functional>
#include <memory>

#include "solas/app/runner.h"
#include "solas/app/runner_options.h"

namespace solas {
namespace app {

class RunnerFactory final {
 private:
  friend class solas::utility::Singleton<RunnerFactory>;

 public:
  // Disallow copy and assign
  RunnerFactory(const RunnerFactory& other) = delete;
  RunnerFactory& operator=(const RunnerFactory& other) = delete;

  // Factory
  static RunnerFactory& Shared();

  // Configuring runners
  template <typename Runnable>
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

template <typename Runnable>
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

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUNNER_FACTORY_H_
