//
//  SLSEvents.h
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
