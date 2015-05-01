//
//  solas/nanovg/gl2.cc
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

#include "solas/nanovg/gl2.h"

#include <OpenGL/gl.h>

#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg.h"
#include "nanovg_gl.h"

#include "solas/nanovg/context.h"

namespace solas {
namespace nanovg {

NVGcontext * CreateContext(int flags) {
  return nvgCreateGL2(flags);
}

void DeleteContext(NVGcontext *context) {
  return nvgDeleteGL2(context);
}

}  // namespace nanovg
}  // namespace solas
