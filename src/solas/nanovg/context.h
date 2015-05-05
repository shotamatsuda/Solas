//
//  solas/nanovg/context.h
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
#ifndef SOLAS_NANOVG_CONTEXT_H_
#define SOLAS_NANOVG_CONTEXT_H_

#include "nanovg.h"

#include <cassert>
#include <stack>
#include <utility>

#include "solas/utility/singleton.h"

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

  // Controlling frame
  void begin(int width, int height, float scale);
  void cancel();
  void end();

  // Implicit conversions
  operator bool() const { return context_; }
  operator NVGcontext *() const { return context_; }

  // Current context
  static NVGcontext * Current();

 private:
  NVGcontext *context_;
  static utility::Singleton<std::stack<NVGcontext *>> contexts_;
};

#pragma mark -

inline Context::Context() : context_(nullptr) {}

inline Context::~Context() {
  if (!contexts_->empty() && contexts_->top() == context_) {
    contexts_->pop();
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

#pragma mark Controlling frame

inline void Context::begin(int width, int height, float scale) {
  assert(context_);
  nvgBeginFrame(context_, width, height, scale);
  contexts_->push(context_);
}

inline void Context::cancel() {
  assert(context_);
  nvgCancelFrame(context_);
  contexts_->pop();
}

inline void Context::end() {
  assert(context_);
  nvgEndFrame(context_);
  contexts_->pop();
}

#pragma mark Current context

inline NVGcontext * Context::Current() {
  if (contexts_->empty()) {
    return nullptr;
  }
  return contexts_->top();
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_CONTEXT_H_
