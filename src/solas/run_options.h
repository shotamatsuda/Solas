//
//  solas/run_options.h
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
#ifndef SOLAS_RUN_OPTIONS_H_
#define SOLAS_RUN_OPTIONS_H_

#include "solas/runner_options.h"

namespace solas {

class RunOptions final {
 public:
  RunOptions();

  // Copy semantics
  RunOptions(const RunOptions&) = default;
  RunOptions& operator=(const RunOptions&) = default;

  // Properties
  RunnerOptions& runner() { return runner_; }
  const RunnerOptions& runner() const { return runner_; }
  bool multiple_windows() const { return multiple_windows_; }
  void set_multiple_windows(bool value) { multiple_windows_ = value; }
  bool dark_content() const { return dark_content_; }
  void set_dark_content(bool value) { dark_content_ = value; }
  bool full_size_content() const { return full_size_content_; }
  void set_full_size_content(bool value) { full_size_content_ = value; }

 private:
  RunnerOptions runner_;
  bool multiple_windows_;
  bool dark_content_;
  bool full_size_content_;
};

// Comparison
bool operator==(const RunOptions& lhs, const RunOptions& rhs);
bool operator!=(const RunOptions& lhs, const RunOptions& rhs);

#pragma mark -

inline RunOptions::RunOptions()
    : multiple_windows_(true),
      dark_content_(false),
      full_size_content_(true) {}

#pragma mark Comparison

inline bool operator==(const RunOptions& lhs, const RunOptions& rhs) {
  return (lhs.runner() == rhs.runner() &&
          lhs.multiple_windows() == rhs.multiple_windows() &&
          lhs.dark_content() == rhs.dark_content() &&
          lhs.full_size_content() == rhs.full_size_content());
}

inline bool operator!=(const RunOptions& lhs, const RunOptions& rhs) {
  return !(lhs == rhs);
}

}  // namespace solas

#endif  // SOLAS_RUN_OPTIONS_H_
