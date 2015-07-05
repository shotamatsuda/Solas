//
//  SLSEventDelegate.h
//
//  MIT License
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

#import <Foundation/Foundation.h>

#import "SLSEvents.h"

@protocol SLSEventDelegate <NSObject>

@optional
- (void)eventDelegate:(nullable id)eventDelegate
            mouseDown:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
            mouseDrag:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
              mouseUp:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
            mouseMove:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           mouseEnter:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
            mouseExit:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          scrollWheel:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
              keyDown:(nonnull SLSKeyEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
                keyUp:(nonnull SLSKeyEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         touchesBegin:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          touchesMove:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
        touchesCancel:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           touchesEnd:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         gestureBegin:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
        gestureChange:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
        gestureCancel:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           gestureEnd:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          motionBegin:(nonnull SLSMotionEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         motionCancel:(nonnull SLSMotionEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
            motionEnd:(nonnull SLSMotionEventConstRef)event;

@end
