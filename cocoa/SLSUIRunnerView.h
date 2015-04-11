//
//  SLSUIRunnerView.h
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

#import <UIKit/UIKit.h>

#import "SLSRunEventDelegate.h"
#import "SLSRunnerLayer.h"

#ifdef __cplusplus

#include "solas/app/gesture_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/touch_event.h"

#endif  // __cplusplus

@interface SLSUIRunnerView : UIView

@property (nonatomic, strong, readonly) NSSet *previousTouches;
@property (nonatomic, strong) SLSRunnerLayer *runnerLayer;

#pragma mark Notifying Events to the Delegate

- (void)notifyTouchesBeginWithEvent:(id)event;
- (void)notifyTouchesMoveWithEvent:(id)event;
- (void)notifyTouchesCancelWithEvent:(id)event;
- (void)notifyTouchesEndWithEvent:(id)event;
- (void)notifyMotionBeginWithEvent:(id)event;
- (void)notifyMotionCancelWithEvent:(id)event;
- (void)notifyMotionEndWithEvent:(id)event;

#pragma mark Managing the Delegate

@property (atomic, weak) id<SLSRunEventDelegate> eventDelegate;

@end
