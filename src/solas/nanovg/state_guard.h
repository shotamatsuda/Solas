//
//  solas/nanovg/state_guard.h
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
#ifndef SOLAS_NANOVG_STATE_GUARD_H_
#define SOLAS_NANOVG_STATE_GUARD_H_

#include "nanovg.h"

#include "solas/nanovg/context.h"

namespace solas {
namespace nanovg {

class StateGuard final {
 public:
  // Constructors
  StateGuard();
  explicit StateGuard(NVGcontext *context);
  ~StateGuard();

  // Disallow copy and assign
  StateGuard(const StateGuard& other) = delete;
  StateGuard& operator=(const StateGuard& other) = delete;

 private:
  NVGcontext *context_;
};

#pragma mark -

inline StateGuard::StateGuard() : context_(Context::Current()) {
  if (context_) {
    nvgSave(context_);
  }
}

inline StateGuard::StateGuard(NVGcontext *context) : context_(context) {
  if (context_) {
    nvgSave(context_);
  }
}

inline StateGuard::~StateGuard() {
  if (context_) {
    nvgRestore(context_);
  }
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STATE_GUARD_H_
