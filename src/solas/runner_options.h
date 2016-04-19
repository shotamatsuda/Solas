//
//  solas/runner_options.h
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
#ifndef SOLAS_RUNNER_OPTIONS_H_
#define SOLAS_RUNNER_OPTIONS_H_

#include "solas/backend.h"

namespace solas {

class RunnerOptions final {
 public:
  RunnerOptions();

  // Copy semantics
  RunnerOptions(const RunnerOptions&) = default;
  RunnerOptions& operator=(const RunnerOptions&) = default;

  // Properties
  Backend backend() const { return backend_; }
  void set_backend(Backend value) { backend_ = value; }
  bool translates_touches() const { return translates_touches_; }
  void set_translates_touches(bool value) { translates_touches_ = value; }
  bool dragging_moves_window() const { return dragging_moves_window_; }
  void set_dragging_moves_window(bool value) { dragging_moves_window_ = value; }

 private:
  Backend backend_;
  bool translates_touches_;
  bool dragging_moves_window_;
};

// Comparison
bool operator==(const RunnerOptions& lhs, const RunnerOptions& rhs);
bool operator!=(const RunnerOptions& lhs, const RunnerOptions& rhs);

#pragma mark -

inline RunnerOptions::RunnerOptions()
    : backend_(Backend::OPENGL2 | Backend::OPENGLES2),
      translates_touches_(true),
      dragging_moves_window_(false) {}

#pragma mark Comparison

inline bool operator==(const RunnerOptions& lhs, const RunnerOptions& rhs) {
  return (lhs.backend() == rhs.backend() &&
          lhs.translates_touches() == rhs.translates_touches() &&
          lhs.dragging_moves_window() == rhs.dragging_moves_window());
}

inline bool operator!=(const RunnerOptions& lhs, const RunnerOptions& rhs) {
  return !(lhs == rhs);
}

}  // namespace solas

#endif  // SOLAS_RUNNER_OPTIONS_H_
