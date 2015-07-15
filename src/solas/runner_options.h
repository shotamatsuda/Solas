//
//  solas/runner_options.h
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
#ifndef SOLAS_RUNNER_OPTIONS_H_
#define SOLAS_RUNNER_OPTIONS_H_

#include "solas/backend.h"

namespace solas {

class RunnerOptions final {
 public:
  RunnerOptions();

  // Copy semantics
  RunnerOptions(const RunnerOptions& other) = default;
  RunnerOptions& operator=(const RunnerOptions& other) = default;

  // Comparison
  bool operator==(const RunnerOptions& other) const;
  bool operator!=(const RunnerOptions& other) const;

  // Properties
  Backend backend() const { return backend_; }
  void set_backend(Backend value) { backend_ = value; }
  bool multiple_windows() const { return multiple_windows_; }
  void set_multiple_windows(bool value) { multiple_windows_ = value; }
  bool dark_content() const { return dark_content_; }
  void set_dark_content(bool value) { dark_content_ = value; }

 private:
  Backend backend_;
  bool multiple_windows_;
  bool dark_content_;
};

#pragma mark -

inline RunnerOptions::RunnerOptions()
    : backend_(Backend::OPENGL2 | Backend::OPENGLES2),
      multiple_windows_(true),
      dark_content_(true) {}

#pragma mark Comparison

inline bool RunnerOptions::operator==(const RunnerOptions& other) const {
  return (backend_ == other.backend_ &&
          multiple_windows_ == other.multiple_windows_ &&
          dark_content_ == other.dark_content_);
}

inline bool RunnerOptions::operator!=(const RunnerOptions& other) const {
  return !operator==(other);
}

}  // namespace solas

#endif  // SOLAS_RUNNER_OPTIONS_H_
