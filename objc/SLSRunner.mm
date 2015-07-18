//
//  SLSRunner.mm
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

#import "SLSRunner.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSEvents.h"

#include <memory>
#include <type_traits>
#include <utility>

#include "solas/app_event.h"
#include "solas/runner.h"
#include "solas/runnable.h"

@interface SLSRunner () {
 @private
  std::unique_ptr<solas::Runner> _runner;
}

@end

@implementation SLSRunner

- (instancetype)init {
  return [self initWithRunnable:nullptr];
}

- (instancetype)initWithRunnable:(std::unique_ptr<solas::Runner>&&)runner {
  self = [super init];
  if (self) {
    _runner = std::move(runner);
  }
  return self;
}

- (void)dealloc {
  _runner.reset(nullptr);
}

- (SLSRunnerBackend)backend {
  NSInteger backend = kSLSRunnerBackendUndefined;
  using solas::Backend;
  using Underlying = std::underlying_type<Backend>::type;
  auto& options = _runner->options();
  if (static_cast<Underlying>(options.backend() & Backend::OPENGL2)) {
    backend |= kSLSRunnerBackendOpenGL2;
  }
  if (static_cast<Underlying>(options.backend() & Backend::OPENGL3)) {
    backend |= kSLSRunnerBackendOpenGL3;
  }
  if (static_cast<Underlying>(options.backend() & Backend::OPENGL4)) {
    backend |= kSLSRunnerBackendOpenGL4;
  }
  if (static_cast<Underlying>(options.backend() & Backend::OPENGLES1)) {
    backend |= kSLSRunnerBackendOpenGLES1;
  }
  if (static_cast<Underlying>(options.backend() & Backend::OPENGLES2)) {
    backend |= kSLSRunnerBackendOpenGLES2;
  }
  if (static_cast<Underlying>(options.backend() & Backend::OPENGLES3)) {
    backend |= kSLSRunnerBackendOpenGLES3;
  }
  if (static_cast<Underlying>(options.backend() & Backend::QUARTZ)) {
    backend |= kSLSRunnerBackendCoreGraphics;
  }
  return (SLSRunnerBackend)backend;
}

#pragma mark SLSDisplayDelegate

- (void)displayDelegate:(id)displayDelegate update:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->update(*SLSAppEventCast(event));
  }
}

- (void)displayDelegate:(id)displayDelegate draw:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->draw(*SLSAppEventCast(event));
  }
}

#pragma mark SLSEventDelegate

- (void)eventDelegate:(id)eventDelegate
            mouseDown:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mousePressed(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
            mouseDrag:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseDragged(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
              mouseUp:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseReleased(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
            mouseMove:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseMoved(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
           mouseEnter:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseEntered(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
            mouseExit:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseExited(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
          scrollWheel:(SLSMouseEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->mouseWheel(*SLSMouseEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
              keyDown:(SLSKeyEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->keyPressed(*SLSKeyEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
                keyUp:(SLSKeyEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->keyReleased(*SLSKeyEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
         touchesBegin:(SLSTouchEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->touchesBegan(*SLSTouchEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
          touchesMove:(SLSTouchEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->touchesMoved(*SLSTouchEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
        touchesCancel:(SLSTouchEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->touchesCancelled(*SLSTouchEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
           touchesEnd:(SLSTouchEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->touchesEnded(*SLSTouchEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
         gestureBegin:(SLSGestureEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->gestureBegan(*SLSGestureEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
        gestureChange:(SLSGestureEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->gestureChanged(*SLSGestureEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
        gestureCancel:(SLSGestureEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->gestureCancelled(*SLSGestureEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
           gestureEnd:(SLSGestureEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->gestureEnded(*SLSGestureEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
          motionBegin:(SLSMotionEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->motionBegan(*SLSMotionEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
         motionCancel:(SLSMotionEventConstRef)event {
  if (_runner) {
    NSAssert(event, @"");
    _runner->motionCancelled(*SLSMotionEventCast(event));
  }
}

- (void)eventDelegate:(id)eventDelegate
            motionEnd:(SLSMotionEventConstRef)event  {
  if (_runner) {
    NSAssert(event, @"");
    _runner->motionEnded(*SLSMotionEventCast(event));
  }
}

@end
