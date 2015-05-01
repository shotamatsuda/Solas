//
//  SLSNSEventSourceView.h
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

#import <AppKit/AppKit.h>

#import "SLSEventDelegate.h"
#import "SLSEventSource.h"

@interface SLSNSEventSourceView : NSView <SLSEventSource>

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

@property (atomic, weak) id<SLSEventDelegate> eventDelegate;

@end
