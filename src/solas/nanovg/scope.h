//
//  solas/nanovg/scope.h
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
#ifndef SOLAS_NANOVG_SCOPE_H_
#define SOLAS_NANOVG_SCOPE_H_

#include "nanovg.h"

namespace solas {
namespace nanovg {

class Scope final {
 public:
  // Constructors
  explicit Scope(NVGcontext *context = nullptr);
  ~Scope();

  // Disallow copy and assign
  Scope(const Scope& other) = delete;
  Scope& operator=(const Scope& other) = delete;

  // Exiting the scope
  void exit();

 private:
  NVGcontext *context_;
};

#pragma mark -

inline Scope::Scope(NVGcontext *context) : context_(context) {
  if (context_) {
    nvgSave(context_);
  }
}

inline Scope::~Scope() {
  if (context_) {
    nvgRestore(context_);
  }
}

#pragma mark Exiting the scope

inline void Scope::exit() {
  if (context_) {
    nvgRestore(context_);
    context_ = nullptr;
  }
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_SCOPE_H_