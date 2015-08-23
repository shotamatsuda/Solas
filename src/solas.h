//
//  solas.h
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

#ifndef SOLAS_H_
#define SOLAS_H_

#ifdef __cplusplus

namespace solas {

extern const double version_number;
extern const unsigned char version_string[];

}  // namespace solas

#include "solas/app_event.h"
#include "solas/backend.h"
#include "solas/composite.h"
#include "solas/event_holder.h"
#include "solas/gesture_event.h"
#include "solas/gesture_kind.h"
#include "solas/group.h"
#include "solas/key_event.h"
#include "solas/key_modifier.h"
#include "solas/math.h"
#include "solas/motion_event.h"
#include "solas/mouse_button.h"
#include "solas/mouse_event.h"
#include "solas/run.h"
#include "solas/run_options.h"
#include "solas/runnable.h"
#include "solas/runner.h"
#include "solas/runner_options.h"
#include "solas/runner_delegate.h"
#include "solas/screen_edge.h"
#include "solas/swipe_direction.h"
#include "solas/touch_event.h"
#include "solas/view.h"

#endif  // __cplusplus

#ifdef __OBJC__

#include <TargetConditionals.h>

#import "SLSAnimationSource.h"
#import "SLSApplicationMain.h"
#import "SLSDefines.h"
#import "SLSDisplayDelegate.h"
#import "SLSDisplayLink.h"
#import "SLSDisplaySource.h"
#import "SLSEventDelegate.h"
#import "SLSEvents.h"
#import "SLSEventSource.h"
#import "SLSNSBundle+Bundle.h"

#if TARGET_OS_IPHONE

#import "SLSUIApplicationDelegate.h"
#import "SLSUIEventSourceView.h"
#import "SLSUIOpenGLES2View.h"
#import "SLSUIOpenGLES3View.h"
#import "SLSUIOpenGLESView.h"
#import "SLSUIQuartzView.h"
#import "SLSUIView.h"
#import "SLSUIViewController.h"

#endif  // TARGET_OS_IPHONE

#if TARGET_OS_MAC && !TARGET_OS_IPHONE

#import "SLSNSApplicationDelegate.h"
#import "SLSNSEventSourceView.h"
#import "SLSNSOpenGL3View.h"
#import "SLSNSOpenGL4View.h"
#import "SLSNSOpenGLLayer.h"
#import "SLSNSOpenGLView.h"
#import "SLSNSQuartzView.h"
#import "SLSNSView.h"
#import "SLSNSViewController.h"
#import "SLSNSWindowController.h"
#import "SLSScreenSaverView.h"

#endif  // TARGET_OS_MAC && !TARGET_OS_IPHONE

#endif  // __OBJC__

#endif  // SOLAS_H_
