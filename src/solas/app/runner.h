//
//  solas/app/runner.h
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

class Runner final {
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
  void gestureBegin(const GestureEvent& event);
  void gestureChange(const GestureEvent& event);
  void gestureCancel(const GestureEvent& event);
  void gestureEnd(const GestureEvent& event);
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
    runnable_->pre(event);
    runnable_->draw(event);
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

inline void Runner::gestureBegin(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureBegin(event);
  }
}

inline void Runner::gestureChange(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureChange(event);
  }
}

inline void Runner::gestureCancel(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureCancel(event);
  }
}

inline void Runner::gestureEnd(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureEnd(event);
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
