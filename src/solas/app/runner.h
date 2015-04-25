//
//  solas/app/runner.h
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

#pragma once
#ifndef SOLAS_APP_RUNNER_H_
#define SOLAS_APP_RUNNER_H_

#include <atomic>
#include <memory>
#include <utility>

#include "solas/app/app_event.h"
#include "solas/app/backend.h"
#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"

namespace solas {
namespace app {

class Runner {
 public:
  // Constructors
  explicit Runner(std::unique_ptr<Runnable>&& runnable);
  ~Runner();

  // Disallow copy and assign
  Runner(const Runner& other) = delete;
  Runner& operator=(const Runner& other) = delete;

  // Lifecycle
  void setup(const AppEvent& event);
  void update(const AppEvent& event);
  void draw(const AppEvent& event);
  void post(const AppEvent& event);
  void exit(const AppEvent& event);

  // Events
  void mouseDown(const MouseEvent& event);
  void mouseDrag(const MouseEvent& event);
  void mouseUp(const MouseEvent& event);
  void mouseMove(const MouseEvent& event);
  void mouseEnter(const MouseEvent& event);
  void mouseExit(const MouseEvent& event);
  void scrollWheel(const MouseEvent& event);
  void keyDown(const KeyEvent& event);
  void keyUp(const KeyEvent& event);
  void touchesBegin(const TouchEvent& event);
  void touchesMove(const TouchEvent& event);
  void touchesCancel(const TouchEvent& event);
  void touchesEnd(const TouchEvent& event);
  void motionBegin(const MotionEvent& event);
  void motionCancel(const MotionEvent& event);
  void motionEnd(const MotionEvent& event);

  // Backend
  Backend backend() const;

 private:
  std::unique_ptr<Runnable> runnable_;
  std::atomic_bool setup_;
};

#pragma mark -

inline Runner::Runner(std::unique_ptr<Runnable>&& runnable)
    : runnable_(std::move(runnable)),
      setup_(false) {}

inline Runner::~Runner() {
  exit(AppEvent());
}

#pragma mark Lifecycle

inline void Runner::setup(const AppEvent& event) {
  if (runnable_) {
    runnable_->setup(event);
  }
}

inline void Runner::update(const AppEvent& event) {
  if (runnable_ && setup_) {
    runnable_->update(event);
  }
}

inline void Runner::draw(const AppEvent& event) {
  if (runnable_) {
    if (!setup_.exchange(true)) {
      // Setup and update when it's the first time to draw
      runnable_->setup(event);
      runnable_->update(event);
    }
    runnable_->draw(event);
  }
}

inline void Runner::post(const AppEvent& event) {
  if (runnable_ && setup_) {
    runnable_->post(event);
  }
}

inline void Runner::exit(const AppEvent& event) {
  if (runnable_) {
    runnable_->exit(event);
    // Delete the instance on the call of the exit in order not to perform
    // anything to static variables after their destruction.
    runnable_.reset(nullptr);
  }
}

#pragma mark Events

inline void Runner::mouseDown(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseDown(event);
  }
}

inline void Runner::mouseDrag(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseDrag(event);
  }
}

inline void Runner::mouseUp(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseUp(event);
  }
}

inline void Runner::mouseMove(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseMove(event);
  }
}

inline void Runner::mouseEnter(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseEnter(event);
  }
}

inline void Runner::mouseExit(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseExit(event);
  }
}

inline void Runner::scrollWheel(const MouseEvent& event) {
  if (runnable_) {
    runnable_->scrollWheel(event);
  }
}

inline void Runner::keyDown(const KeyEvent& event) {
  if (runnable_) {
    runnable_->keyDown(event);
  }
}

inline void Runner::keyUp(const KeyEvent& event) {
  if (runnable_) {
    runnable_->keyUp(event);
  }
}

inline void Runner::touchesBegin(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesBegin(event);
  }
}

inline void Runner::touchesMove(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesMove(event);
  }
}

inline void Runner::touchesCancel(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesCancel(event);
  }
}

inline void Runner::touchesEnd(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesEnd(event);
  }
}

inline void Runner::motionBegin(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionBegin(event);
  }
}

inline void Runner::motionCancel(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionCancel(event);
  }
}

inline void Runner::motionEnd(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionEnd(event);
  }
}

#pragma mark Backend

inline Backend Runner::backend() const {
  if (!runnable_) {
    return Backend::UNDEFINED;
  }
  return runnable_->backend();
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUNNER_H_
