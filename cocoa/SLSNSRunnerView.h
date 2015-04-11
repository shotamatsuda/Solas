//
//  SLSNSRunnerView.h
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

#import <AppKit/AppKit.h>

#import "SLSRunEventDelegate.h"
#import "SLSRunnerLayer.h"

#ifdef __cplusplus

#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/touch_event.h"

#endif  // __cplusplus

@interface SLSNSRunnerView : NSView

@property (nonatomic, assign, readonly) CGPoint previousMouseLocation;
@property (nonatomic, strong, readonly) NSSet *previousTouches;
@property (nonatomic, strong) SLSRunnerLayer *runnerLayer;

#pragma mark Controlling Loop

- (void)startLoop;
- (void)stopLoop;

#pragma mark Notifying Events to the Delegate

- (void)notifyMouseDownWithEvent:(id)event;
- (void)notifyMouseDragWithEvent:(id)event;
- (void)notifyMouseUpWithEvent:(id)event;
- (void)notifyMouseMoveWithEvent:(id)event;
- (void)notifyMouseEnterWithEvent:(id)event;
- (void)notifyMouseExitWithEvent:(id)event;
- (void)notifyScrollWheelWithEvent:(id)event;
- (void)notifyKeyDownWithEvent:(id)event;
- (void)notifyKeyUpWithEvent:(id)event;
- (void)notifyTouchesBeginWithEvent:(id)event;
- (void)notifyTouchesMoveWithEvent:(id)event;
- (void)notifyTouchesCancelWithEvent:(id)event;
- (void)notifyTouchesEndWithEvent:(id)event;

#pragma mark Managing the Delegate

@property (atomic, weak) id<SLSRunEventDelegate> eventDelegate;

@end
