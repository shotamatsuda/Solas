//
//  solas/runner.h
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

#pragma once
#ifndef SOLAS_RUNNER_H_
#define SOLAS_RUNNER_H_

#include <atomic>
#include <memory>
#include <utility>

#include "solas/app_event.h"
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_event.h"
#include "solas/runnable.h"
#include "solas/runner_options.h"
#include "solas/touch_event.h"

namespace solas {

class Runner final {
 public:
  explicit Runner(std::unique_ptr<Runnable>&& runnable);
  Runner(std::unique_ptr<Runnable>&& runnable, const RunnerOptions& options);
  ~Runner();

  // Disallow copy semantics
  Runner(const Runner& other) = delete;
  Runner& operator=(const Runner& other) = delete;

  // Move semantics
  Runner(Runner&& other) = default;
  Runner& operator=(Runner&& other) = default;

  // Lifecycle
  void setup(const AppEvent& event);
  void update(const AppEvent& event);
  void draw(const AppEvent& event);
  void exit(const AppEvent& event);

  // Events
  void mousePressed(const MouseEvent& event);
  void mouseDragged(const MouseEvent& event);
  void mouseReleased(const MouseEvent& event);
  void mouseMoved(const MouseEvent& event);
  void mouseEntered(const MouseEvent& event);
  void mouseExited(const MouseEvent& event);
  void mouseWheel(const MouseEvent& event);
  void keyPressed(const KeyEvent& event);
  void keyReleased(const KeyEvent& event);
  void touchesBegan(const TouchEvent& event);
  void touchesMoved(const TouchEvent& event);
  void touchesCancelled(const TouchEvent& event);
  void touchesEnded(const TouchEvent& event);
  void gestureBegan(const GestureEvent& event);
  void gestureChanged(const GestureEvent& event);
  void gestureCancelled(const GestureEvent& event);
  void gestureEnded(const GestureEvent& event);
  void motionBegan(const MotionEvent& event);
  void motionCancelled(const MotionEvent& event);
  void motionEnded(const MotionEvent& event);

  // Options
  const RunnerOptions& options() const { return options_; }

 private:
  std::unique_ptr<Runnable> runnable_;
  std::atomic_bool setup_;
  RunnerOptions options_;
};

#pragma mark -

inline Runner::Runner(std::unique_ptr<Runnable>&& runnable)
    : runnable_(std::move(runnable)),
      setup_(false) {}

inline Runner::Runner(std::unique_ptr<Runnable>&& runnable,
                      const RunnerOptions& options)
    : runnable_(std::move(runnable)),
      options_(options),
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

inline void Runner::mousePressed(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mousePressed(event);
  }
}

inline void Runner::mouseDragged(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseDragged(event);
  }
}

inline void Runner::mouseReleased(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseReleased(event);
  }
}

inline void Runner::mouseMoved(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseMoved(event);
  }
}

inline void Runner::mouseEntered(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseEntered(event);
  }
}

inline void Runner::mouseExited(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseExited(event);
  }
}

inline void Runner::mouseWheel(const MouseEvent& event) {
  if (runnable_) {
    runnable_->mouseWheel(event);
  }
}

inline void Runner::keyPressed(const KeyEvent& event) {
  if (runnable_) {
    runnable_->keyPressed(event);
  }
}

inline void Runner::keyReleased(const KeyEvent& event) {
  if (runnable_) {
    runnable_->keyReleased(event);
  }
}

inline void Runner::touchesBegan(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesBegan(event);
  }
}

inline void Runner::touchesMoved(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesMoved(event);
  }
}

inline void Runner::touchesCancelled(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesCancelled(event);
  }
}

inline void Runner::touchesEnded(const TouchEvent& event) {
  if (runnable_) {
    runnable_->touchesEnded(event);
  }
}

inline void Runner::gestureBegan(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureBegan(event);
  }
}

inline void Runner::gestureChanged(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureChanged(event);
  }
}

inline void Runner::gestureCancelled(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureCancelled(event);
  }
}

inline void Runner::gestureEnded(const GestureEvent& event) {
  if (runnable_) {
    runnable_->gestureEnded(event);
  }
}

inline void Runner::motionBegan(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionBegan(event);
  }
}

inline void Runner::motionCancelled(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionCancelled(event);
  }
}

inline void Runner::motionEnded(const MotionEvent& event) {
  if (runnable_) {
    runnable_->motionEnded(event);
  }
}

}  // namespace solas

#endif  // SOLAS_RUNNER_H_
