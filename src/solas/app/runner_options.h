//
//  solas/app/runner_options.h
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
#ifndef SOLAS_APP_RUNNER_OPTIONS_H_
#define SOLAS_APP_RUNNER_OPTIONS_H_

namespace solas {
namespace app {

class RunnerOptions final {
 public:
  // Constructors
  RunnerOptions();

  // Copy and assign
  RunnerOptions(const RunnerOptions& other) = default;
  RunnerOptions& operator=(const RunnerOptions& other) = default;

  // Comparison
  bool operator==(const RunnerOptions& other) const;
  bool operator!=(const RunnerOptions& other) const;

  // Properties
  bool multiple_windows() const { return multiple_windows_; }
  void set_multiple_windows(bool value) { multiple_windows_ = value; }

 private:
  bool multiple_windows_;
};

#pragma mark -

inline RunnerOptions::RunnerOptions()
    : multiple_windows_(true) {}

#pragma mark Comparison

inline bool RunnerOptions::operator==(const RunnerOptions& other) const {
  return multiple_windows_ == other.multiple_windows_;
}

inline bool RunnerOptions::operator!=(const RunnerOptions& other) const {
  return !operator==(other);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUNNER_OPTIONS_H_
