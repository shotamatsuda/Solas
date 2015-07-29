//
//  solas/run_options.h
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
#ifndef SOLAS_RUN_OPTIONS_H_
#define SOLAS_RUN_OPTIONS_H_

#include "solas/runner_options.h"

namespace solas {

class RunOptions final {
 public:
  RunOptions();

  // Copy semantics
  RunOptions(const RunOptions& other) = default;
  RunOptions& operator=(const RunOptions& other) = default;

  // Comparison
  bool operator==(const RunOptions& other) const;
  bool operator!=(const RunOptions& other) const;

  // Properties
  RunnerOptions& runner_options() { return runner_options_; }
  const RunnerOptions& runner_options() const { return runner_options_; }
  bool multiple_windows() const { return multiple_windows_; }
  void set_multiple_windows(bool value) { multiple_windows_ = value; }
  bool dark_content() const { return dark_content_; }
  void set_dark_content(bool value) { dark_content_ = value; }
  bool full_size_content() const { return full_size_content_; }
  void set_full_size_content(bool value) { full_size_content_ = value; }

 private:
  RunnerOptions runner_options_;
  bool multiple_windows_;
  bool dark_content_;
  bool full_size_content_;
};

#pragma mark -

inline RunOptions::RunOptions()
    : multiple_windows_(true),
      dark_content_(false),
      full_size_content_(true) {}

#pragma mark Comparison

inline bool RunOptions::operator==(const RunOptions& other) const {
  return (runner_options_ == other.runner_options_ &&
          multiple_windows_ == other.multiple_windows_ &&
          dark_content_ == other.dark_content_ &&
          full_size_content_ == other.full_size_content_);
}

inline bool RunOptions::operator!=(const RunOptions& other) const {
  return !operator==(other);
}

}  // namespace solas

#endif  // SOLAS_RUN_OPTIONS_H_
