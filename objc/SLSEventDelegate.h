//
//  SLSEventDelegate.h
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

#import <Foundation/Foundation.h>

#import "SLSEvents.h"

@protocol SLSEventDelegate <NSObject>

@optional
- (void)sender:(id)sender mouseDown:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender mouseDrag:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender mouseUp:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender mouseMove:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender mouseEnter:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender mouseExit:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender scrollWheel:(SLSMouseEventConstRef)event;
- (void)sender:(id)sender keyDown:(SLSKeyEventConstRef)event;
- (void)sender:(id)sender keyUp:(SLSKeyEventConstRef)event;
- (void)sender:(id)sender touchesBegin:(SLSTouchEventConstRef)event;
- (void)sender:(id)sender touchesMove:(SLSTouchEventConstRef)event;
- (void)sender:(id)sender touchesCancel:(SLSTouchEventConstRef)event;
- (void)sender:(id)sender touchesEnd:(SLSTouchEventConstRef)event;
- (void)sender:(id)sender gestureBegin:(SLSGestureEventConstRef)event;
- (void)sender:(id)sender gestureChange:(SLSGestureEventConstRef)event;
- (void)sender:(id)sender gestureCancel:(SLSGestureEventConstRef)event;
- (void)sender:(id)sender gestureEnd:(SLSGestureEventConstRef)event;
- (void)sender:(id)sender motionBegin:(SLSMotionEventConstRef)event;
- (void)sender:(id)sender motionCancel:(SLSMotionEventConstRef)event;
- (void)sender:(id)sender motionEnd:(SLSMotionEventConstRef)event;

@end
