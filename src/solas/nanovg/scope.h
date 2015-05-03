//
//  solas/nanovg/scope.h
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
#ifndef SOLAS_NANOVG_SCOPE_H_
#define SOLAS_NANOVG_SCOPE_H_

#include "nanovg.h"

namespace solas {
namespace nanovg {

class Scope final {
 public:
  // Constructors
  Scope();
  explicit Scope(NVGcontext *context);
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

inline Scope::Scope() : context_(nullptr) {}

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
