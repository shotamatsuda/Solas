//
//  solas/nanovg/gles2.cc
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

#include "solas/nanovg/gles2.h"

#include <OpenGLES/ES2/gl.h>

#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg.h"
#include "nanovg_gl.h"

#include "solas/nanovg/context.h"

namespace solas {
namespace nanovg {

NVGcontext * CreateContext(int flags) {
  return nvgCreateGLES2(flags);
}

void DeleteContext(NVGcontext *context) {
  return nvgDeleteGLES2(context);
}

}  // namespace nanovg
}  // namespace solas
