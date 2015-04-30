//
//  SLSEvents.h
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
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

#ifdef __cplusplus

#include "solas/app/app_event.h"
#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/touch_event.h"

#endif  // __cplusplus

#import "SLSDefines.h"

typedef struct SLSAppEvent * SLSAppEventRef;
typedef struct SLSMouseEvent * SLSMouseEventRef;
typedef struct SLSKeyEvent * SLSKeyEventRef;
typedef struct SLSTouchEvent * SLSTouchEventRef;
typedef struct SLSGestureEvent * SLSGestureEventRef;
typedef struct SLSMotionEvent * SLSMotionEventRef;

typedef const struct SLSAppEvent * SLSAppEventConstRef;
typedef const struct SLSMouseEvent * SLSMouseEventConstRef;
typedef const struct SLSKeyEvent * SLSKeyEventConstRef;
typedef const struct SLSTouchEvent * SLSTouchEventConstRef;
typedef const struct SLSGestureEvent * SLSGestureEventConstRef;
typedef const struct SLSMotionEvent * SLSMotionEventConstRef;

#ifdef __cplusplus

SLS_DEFINE_REFERENCE_MAKE_CAST(SLSAppEvent, solas::app::AppEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSMouseEvent, solas::app::MouseEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSKeyEvent, solas::app::KeyEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSTouchEvent, solas::app::TouchEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSGestureEvent, solas::app::GestureEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSMotionEvent, solas::app::MotionEvent)

#endif  // __cplusplus
