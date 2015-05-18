//
//  SLSRunner.mm
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

#import "SLSRunner.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSEvents.h"

#include <cassert>
#include <memory>
#include <type_traits>
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

- (SLSRunnerBackend)backend {
  NSInteger backend = kSLSRunnerBackendUndefined;
  using solas::app::Backend;
  using Underlying = std::underlying_type<Backend>::type;
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGL2)) {
    backend |= kSLSRunnerBackendOpenGL2;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGL3)) {
    backend |= kSLSRunnerBackendOpenGL3;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGL4)) {
    backend |= kSLSRunnerBackendOpenGL4;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGLES1)) {
    backend |= kSLSRunnerBackendOpenGLES1;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGLES2)) {
    backend |= kSLSRunnerBackendOpenGLES2;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::OPENGLES3)) {
    backend |= kSLSRunnerBackendOpenGLES3;
  }
  if (static_cast<Underlying>(_runner->backend() & Backend::QUARTZ)) {
    backend |= kSLSRunnerBackendCoreGraphics;
  }
  return (SLSRunnerBackend)backend;
}

#pragma mark SLSDisplayDelegate

- (void)sender:(id)sender update:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->update(*SLSAppEventCast(event));
  }
}

- (void)sender:(id)sender draw:(SLSAppEventConstRef)event {
  if (_runner) {
    _runner->draw(*SLSAppEventCast(event));
  }
}

#pragma mark SLSEventDelegate

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

- (void)sender:(id)sender gestureBegin:(SLSGestureEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->gestureBegin(*SLSGestureEventCast(event));
  }
}

- (void)sender:(id)sender gestureChange:(SLSGestureEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->gestureChange(*SLSGestureEventCast(event));
  }
}

- (void)sender:(id)sender gestureCancel:(SLSGestureEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->gestureCancel(*SLSGestureEventCast(event));
  }
}

- (void)sender:(id)sender gestureEnd:(SLSGestureEventConstRef)event {
  if (_runner) {
    assert(event);
    _runner->gestureEnd(*SLSGestureEventCast(event));
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
