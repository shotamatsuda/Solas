//
//  solas/nanovg/state.h
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
#ifndef SOLAS_NANOVG_STATE_H_
#define SOLAS_NANOVG_STATE_H_

#include "nanovg.h"

#include "solas/nanovg/context.h"

namespace solas {
namespace nanovg {

void Save();
void Reset();
void Restore();

#pragma mark -

inline void Save() {
  nvgSave(Context::Current());
}

inline void Reset() {
  nvgReset(Context::Current());
}

inline void Restore() {
  nvgRestore(Context::Current());
}

}  // namespace nanovg

namespace nvg = nanovg;

}  // namespace solas

#endif  // SOLAS_NANOVG_STATE_H_
