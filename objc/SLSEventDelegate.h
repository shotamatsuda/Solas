//
//  SLSEventDelegate.h
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

#import <Foundation/Foundation.h>

#import "SLSEvents.h"

@protocol SLSEventDelegate <NSObject>

@optional
- (void)eventDelegate:(nullable id)eventDelegate
         mousePressed:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         mouseDragged:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
        mouseReleased:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           mouseMoved:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         mouseEntered:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          mouseExited:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           mouseWheel:(nonnull SLSMouseEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
           keyPressed:(nonnull SLSKeyEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          keyReleased:(nonnull SLSKeyEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         touchesBegan:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         touchesMoved:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
     touchesCancelled:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         touchesEnded:(nonnull SLSTouchEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         gestureBegan:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
       gestureChanged:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
     gestureCancelled:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
         gestureEnded:(nonnull SLSGestureEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          motionBegan:(nonnull SLSMotionEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
      motionCancelled:(nonnull SLSMotionEventConstRef)event;
- (void)eventDelegate:(nullable id)eventDelegate
          motionEnded:(nonnull SLSMotionEventConstRef)event;

@end
