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

inline SLSAppEventRef SLSAppEventMake(solas::app::AppEvent *ptr) {
  return reinterpret_cast<SLSAppEventRef>(ptr);
}

inline SLSMouseEventRef SLSMouseEventMake(solas::app::MouseEvent *ptr) {
  return reinterpret_cast<SLSMouseEventRef>(ptr);
}

inline SLSKeyEventRef SLSKeyEventMake(solas::app::KeyEvent *ptr) {
  return reinterpret_cast<SLSKeyEventRef>(ptr);
}

inline SLSTouchEventRef SLSTouchEventMake(solas::app::TouchEvent *ptr) {
  return reinterpret_cast<SLSTouchEventRef>(ptr);
}

inline SLSGestureEventRef SLSGestureEventMake(solas::app::GestureEvent *ptr) {
  return reinterpret_cast<SLSGestureEventRef>(ptr);
}

inline SLSMotionEventRef SLSMotionEventMake(solas::app::MotionEvent *ptr) {
  return reinterpret_cast<SLSMotionEventRef>(ptr);
}

inline solas::app::AppEvent * SLSAppEventCast(SLSAppEventRef ref) {
  return reinterpret_cast<solas::app::AppEvent *>(ref);
}

inline solas::app::MouseEvent * SLSMouseEventCast(SLSMouseEventRef ref) {
  return reinterpret_cast<solas::app::MouseEvent *>(ref);
}

inline solas::app::KeyEvent * SLSKeyEventCast(SLSKeyEventRef ref) {
  return reinterpret_cast<solas::app::KeyEvent *>(ref);
}

inline solas::app::TouchEvent * SLSTouchEventCast(SLSTouchEventRef ref) {
  return reinterpret_cast<solas::app::TouchEvent *>(ref);
}

inline solas::app::GestureEvent * SLSGestureEventCast(SLSGestureEventRef ref) {
  return reinterpret_cast<solas::app::GestureEvent *>(ref);
}

inline solas::app::MotionEvent * SLSMotionEventCast(SLSMotionEventRef ref) {
  return reinterpret_cast<solas::app::MotionEvent *>(ref);
}

inline SLSAppEventConstRef SLSAppEventMake(
    const solas::app::AppEvent *ptr) {
  return reinterpret_cast<SLSAppEventConstRef>(ptr);
}

inline SLSMouseEventConstRef SLSMouseEventMake(
    const solas::app::MouseEvent *ptr) {
  return reinterpret_cast<SLSMouseEventConstRef>(ptr);
}

inline SLSKeyEventConstRef SLSKeyEventMake(
    const solas::app::KeyEvent *ptr) {
  return reinterpret_cast<SLSKeyEventConstRef>(ptr);
}

inline SLSTouchEventConstRef SLSTouchEventMake(
    const solas::app::TouchEvent *ptr) {
  return reinterpret_cast<SLSTouchEventConstRef>(ptr);
}

inline SLSGestureEventConstRef SLSGestureEventMake(
    const solas::app::GestureEvent *ptr) {
  return reinterpret_cast<SLSGestureEventConstRef>(ptr);
}

inline SLSMotionEventConstRef SLSMotionEventMake(
    const solas::app::MotionEvent *ptr) {
  return reinterpret_cast<SLSMotionEventConstRef>(ptr);
}

inline const solas::app::AppEvent * SLSAppEventCast(
    SLSAppEventConstRef ref) {
  return reinterpret_cast<const solas::app::AppEvent *>(ref);
}

inline const solas::app::MouseEvent * SLSMouseEventCast(
    SLSMouseEventConstRef ref) {
  return reinterpret_cast<const solas::app::MouseEvent *>(ref);
}

inline const solas::app::KeyEvent * SLSKeyEventCast
    (SLSKeyEventConstRef ref) {
  return reinterpret_cast<const solas::app::KeyEvent *>(ref);
}

inline const solas::app::TouchEvent * SLSTouchEventCast(
    SLSTouchEventConstRef ref) {
  return reinterpret_cast<const solas::app::TouchEvent *>(ref);
}

inline const solas::app::GestureEvent * SLSGestureEventCast(
    SLSGestureEventConstRef ref) {
  return reinterpret_cast<const solas::app::GestureEvent *>(ref);
}

inline const solas::app::MotionEvent * SLSMotionEventCast(
    SLSMotionEventConstRef ref) {
  return reinterpret_cast<const solas::app::MotionEvent *>(ref);
}

#endif  // __cplusplus
