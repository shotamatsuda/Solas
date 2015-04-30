//
//  solas/nanovg/context.h
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
#ifndef SOLAS_NANOVG_CONTEXT_H_
#define SOLAS_NANOVG_CONTEXT_H_

#include "nanovg.h"

#include <utility>

namespace solas {
namespace nanovg {

NVGcontext * CreateContext(int flags = int());
void DeleteContext(NVGcontext *context);

#pragma mark -

class Context final {
 public:
  // Constructors
  Context();
  ~Context();

  // Disallow copy and assign
  Context(const Context& other) = delete;
  Context& operator=(const Context& other) = delete;

  // Move
  Context(Context&& other);
  Context& operator=(Context&& other);

  // Managing the context
  void init(int flags = int());
  void destroy();

  // Implicit conversions
  operator bool() const { return context_; }
  operator NVGcontext *() const { return context_; }

  // Shared context
  static NVGcontext * shared() { return shared_context_; }

 private:
  NVGcontext *context_;
  static NVGcontext *shared_context_;
};

#pragma mark -

inline Context::Context() : context_(nullptr) {}

inline Context::~Context() {
  if (shared_context_ == context_) {
    shared_context_ = nullptr;
  }
  destroy();
}

#pragma mark Move

inline Context::Context(Context&& other) : context_(other.context_) {
  other.context_ = nullptr;
}

inline Context& Context::operator=(Context&& other) {
  if (&other != this) {
    std::swap(context_, other.context_);
  }
  return *this;
}

#pragma mark Managing the context

inline void Context::init(int flags) {
  if (!context_) {
    context_ = CreateContext(flags);
  }
}

inline void Context::destroy() {
  if (context_) {
    DeleteContext(context_);
    context_ = nullptr;
  }
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_CONTEXT_H_
