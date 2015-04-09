//
//  SLSRunner.mm
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

#import "SLSRunner.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSEvents.h"

#include <cassert>
#include <memory>
#include <utility>

#include "solas/app/app_event.h"
#include "solas/app/runner.h"
#include "solas/app/runnable.h"

@interface SLSRunner () {
 @private
  std::unique_ptr<solas::app::Runner> _runner;
}

@end

@implementation SLSRunner

- (instancetype)initWithRunnable:(std::unique_ptr<solas::app::Runner>&&)runner {
  self = [super init];
  if (self) {
    _runner = std::move(runner);
  }
  return self;
}

- (void)dealloc {
  _runner.reset(nullptr);
}

#pragma mark SLSRunDisplayDelegate

- (void)sender:(id)sender update:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->update(*SLSAppEventCast(event));
  }
}

- (void)sender:(id)sender draw:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->draw(*SLSAppEventCast(event));
    _runner->post(*SLSAppEventCast(event));
  }
}

#pragma mark SLSRunEventDelegate

- (void)sender:(id)sender mouseDown:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseDown(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender mouseDrag:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseDrag(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender mouseUp:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseUp(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender mouseMove:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseMove(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender mouseEnter:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseEnter(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender mouseExit:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->mouseExit(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender scrollWheel:(SLSMouseEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->scrollWheel(*SLSMouseEventCast(event));
  }
}

- (void)sender:(id)sender keyDown:(SLSKeyEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->keyDown(*SLSKeyEventCast(event));
  }
}

- (void)sender:(id)sender keyUp:(SLSKeyEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->keyUp(*SLSKeyEventCast(event));
  }
}

- (void)sender:(id)sender touchesBegin:(SLSTouchEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->touchesBegin(*SLSTouchEventCast(event));
  }
}

- (void)sender:(id)sender touchesMove:(SLSTouchEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->touchesMove(*SLSTouchEventCast(event));
  }
}

- (void)sender:(id)sender touchesCancel:(SLSTouchEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->touchesCancel(*SLSTouchEventCast(event));
  }
}

- (void)sender:(id)sender touchesEnd:(SLSTouchEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->touchesEnd(*SLSTouchEventCast(event));
  }
}

- (void)sender:(id)sender motionBegin:(SLSMotionEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->motionBegin(*SLSMotionEventCast(event));
  }
}

- (void)sender:(id)sender motionCancel:(SLSMotionEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->motionCancel(*SLSMotionEventCast(event));
  }
}

- (void)sender:(id)sender motionEnd:(SLSMotionEventConstRef)event  {
  if (_runner) {
    assert(event);
    _runner->motionEnd(*SLSMotionEventCast(event));
  }
}

@end
