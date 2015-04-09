//
//  SLSRunEventDelegate.h
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

#import <Foundation/Foundation.h>

#import "SLSEvents.h"

@protocol SLSRunEventDelegate <NSObject>

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
- (void)sender:(id)sender motionBegin:(SLSMotionEventConstRef)event;
- (void)sender:(id)sender motionCancel:(SLSMotionEventConstRef)event;
- (void)sender:(id)sender motionEnd:(SLSMotionEventConstRef)event;

@end
