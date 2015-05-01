//
//  solas/nanovg/gl.h
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
#ifndef SOLAS_NANOVG_GL_H_
#define SOLAS_NANOVG_GL_H_

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#include "solas/nanovg/gles2.h"
#elif TARGET_OS_MAC
#include "solas/nanovg/gl2.h"
#endif

#endif  // SOLAS_NANOVG_GL_H_
