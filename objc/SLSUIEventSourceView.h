//
//  SLSUIEventSourceView.h
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

#import <UIKit/UIKit.h>

#import "SLSEventDelegate.h"
#import "SLSEventSource.h"

@interface SLSUIEventSourceView : UIView <SLSEventSource>

#pragma mark Notifying Events to the Delegate

- (void)notifyTouchesBeginWithEvent:(UIEvent *)event;
- (void)notifyTouchesMoveWithEvent:(UIEvent *)event;
- (void)notifyTouchesCancelWithEvent:(UIEvent *)event;
- (void)notifyTouchesEndWithEvent:(UIEvent *)event;
- (void)notifyMotionBeginWithEvent:(UIEvent *)event;
- (void)notifyMotionCancelWithEvent:(UIEvent *)event;
- (void)notifyMotionEndWithEvent:(UIEvent *)event;

#ifdef __cplusplus

- (void)notifyGestureEventWithRecognizer:(UIGestureRecognizer *)recognizer
                                    kind:(solas::app::GestureKind)kind
                                    data:(const boost::any&)data;

#endif  // __cplusplus

#pragma mark Managing the Delegate

@property (atomic, weak) id<SLSEventDelegate> eventDelegate;

@end
