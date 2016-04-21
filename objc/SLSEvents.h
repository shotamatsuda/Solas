//
//  SLSEvents.h
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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

#include "solas/app_event.h"
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_event.h"
#include "solas/touch_event.h"

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

SLS_DEFINE_REFERENCE_MAKE_CAST(SLSAppEvent, solas::AppEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSMouseEvent, solas::MouseEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSKeyEvent, solas::KeyEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSTouchEvent, solas::TouchEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSGestureEvent, solas::GestureEvent)
SLS_DEFINE_REFERENCE_MAKE_CAST(SLSMotionEvent, solas::MotionEvent)

#endif  // __cplusplus
