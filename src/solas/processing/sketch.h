//
//  solas/processing/sketch.h
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
#ifndef SOLAS_PROCESSING_SKETCH_H_
#define SOLAS_PROCESSING_SKETCH_H_

#include <chrono>
#include <cstdint>
#include <functional>
#include <list>

#include "solas/app/runnable.h"
#include "solas/graphics/context_holder.h"
#include "solas/processing/event.h"
#include "solas/processing/layer.h"
#include "solas/processing/types.h"

namespace solas {
namespace processing {

class Sketch : public app::Runnable, public Layer {
 public:
  // Constructors
  Sketch();

  // Disallow copy and assign
  Sketch(const Sketch& other) = delete;
  Sketch& operator=(const Sketch& other) = delete;

  // Move
  Sketch(Sketch&& other) = default;

  // Structure
  Real width() const override;
  Real height() const override;

  // Mouse
  const Vec2& mouse() const override;
  Real mouse_x() const override;
  Real mouse_y() const override;
  const Vec2& pmouse() const override;
  Real pmouse_x() const override;
  Real pmouse_y() const override;
  Constant mouse_button() const override;
  bool mouse_pressed() const override;

  // Keyboard
  char key() const override;
  std::uint32_t key_code() const override;
  bool key_pressed() const override;

  // Time and date
  std::chrono::milliseconds::rep millis() const override;

 protected:
  // Lifecycle intended to be overriden
  void setup() override {}
  void update() override {}
  void draw() override {}
  void post() override {}
  void exit() override {}

  // Events
  virtual void mousePressed(const MouseEvent& event);
  virtual void mouseDragged(const MouseEvent& event);
  virtual void mouseReleased(const MouseEvent& event);
  virtual void mouseMoved(const MouseEvent& event);
  virtual void mouseEntered(const MouseEvent& event);
  virtual void mouseExited(const MouseEvent& event);
  virtual void mouseWheel(const MouseEvent& event);
  virtual void keyPressed(const KeyEvent& event);
  virtual void keyReleased(const KeyEvent& event);
  virtual void touchesBegan(const TouchEvent& event);
  virtual void touchesMoved(const TouchEvent& event);
  virtual void touchesCancelled(const TouchEvent& event);
  virtual void touchesEnded(const TouchEvent& event);
  virtual void motionBegan(const MotionEvent& event);
  virtual void motionCancelled(const MotionEvent& event);
  virtual void motionEnded(const MotionEvent& event);

  // Event handlers
  template <typename Event>
  void enqueueEvent(const Event& event);
  void dequeueEvent(const Event& event);
  void dequeueEvents();
  void handleMouseEvent(const MouseEvent& event);
  void handleKeyEvent(const KeyEvent& event);
  void handleTouchEvent(const TouchEvent& event);
  void handleGestureEvent(const GestureEvent& event);
  void handleMotionEvent(const MotionEvent& event);

  // Events intended to be overriden
  virtual void mousePressed() {}
  virtual void mouseDragged() {}
  virtual void mouseReleased() {}
  virtual void mouseMoved() {}
  virtual void mouseEntered() {}
  virtual void mouseExited() {}
  virtual void mouseWheel() {}
  virtual void keyPressed() {}
  virtual void keyReleased() {}
  virtual void touchesBegan() {}
  virtual void touchesMoved() {}
  virtual void touchesCancelled() {}
  virtual void touchesEnded() {}
  virtual void motionBegan() {}
  virtual void motionCancelled() {}
  virtual void motionEnded() {}

 private:
  // Lifecycle overridden from Runnable
  void setup(const AppEvent& event) override;
  void update(const AppEvent& event) override;
  void draw(const AppEvent& event) override;
  void post(const AppEvent& event) override;
  void exit(const AppEvent& event) override;

  // Events overridden from Runnable
  void mouseDown(const MouseEvent& event) override;
  void mouseDrag(const MouseEvent& event) override;
  void mouseUp(const MouseEvent& event) override;
  void mouseMove(const MouseEvent& event) override;
  void mouseEnter(const MouseEvent& event) override;
  void mouseExit(const MouseEvent& event) override;
  void scrollWheel(const MouseEvent& event) override;
  void keyDown(const KeyEvent& event) override;
  void keyUp(const KeyEvent& event) override;
  void touchesBegin(const TouchEvent& event) override;
  void touchesMove(const TouchEvent& event) override;
  void touchesCancel(const TouchEvent& event) override;
  void touchesEnd(const TouchEvent& event) override;
  void motionBegin(const MotionEvent& event) override;
  void motionCancel(const MotionEvent& event) override;
  void motionEnd(const MotionEvent& event) override;

  // Context
  const graphics::ContextHolder& context() const override;

 private:
  std::chrono::system_clock::time_point setup_time_;
  std::list<Event> event_queue_;

  // Structure
  Real width_;
  Real height_;

  // Mouse
  Vec2 dmouse_;
  Vec2 emouse_;
  union {
    Vec2 mouse_;
    struct { Real mouse_x_; Real mouse_y_; };
  };
  union {
    Vec2 pmouse_;
    struct { Real pmouse_x_; Real pmouse_y_; };
  };
  Constant mouse_button_;
  bool mouse_pressed_;

  // Keyboard
  char key_;
  std::uint32_t key_code_;
  bool key_pressed_;
};

#pragma mark -

inline Sketch::Sketch()
    : setup_time_(),
      width_(),
      height_(),
      mouse_(),
      pmouse_(),
      mouse_button_(NONE),
      mouse_pressed_(),
      key_(),
      key_code_(),
      key_pressed_() {}

#pragma mark Structure

inline Real Sketch::width() const {
  return width_;
}

inline Real Sketch::height() const {
  return height_;
}

#pragma mark Mouse

inline const Vec2& Sketch::mouse() const {
  return mouse_;
}

inline Real Sketch::mouse_x() const {
  return mouse_x_;
}

inline Real Sketch::mouse_y() const {
  return mouse_y_;
}

inline const Vec2& Sketch::pmouse() const {
  return pmouse_;
}

inline Real Sketch::pmouse_x() const {
  return pmouse_x_;
}

inline Real Sketch::pmouse_y() const {
  return pmouse_y_;
}

inline Constant Sketch::mouse_button() const {
  return mouse_button_;
}

inline bool Sketch::mouse_pressed() const {
  return mouse_pressed_;
}

#pragma mark Keyboard

inline char Sketch::key() const {
  return key_;
}

inline std::uint32_t Sketch::key_code() const {
  return key_code_;
}

inline bool Sketch::key_pressed() const {
  return key_pressed_;
}

#pragma mark Time and date

inline std::chrono::milliseconds::rep Sketch::millis() const {
  using clock = std::chrono::system_clock;
  using unit = std::chrono::milliseconds;
  return std::chrono::duration_cast<unit>(clock::now() - setup_time_).count();
}

#pragma mark Events

inline void Sketch::mousePressed(const MouseEvent& event) {
  mousePressed();
}

inline void Sketch::mouseDragged(const MouseEvent& event) {
  mouseDragged();
}

inline void Sketch::mouseReleased(const MouseEvent& event) {
  mouseReleased();
}

inline void Sketch::mouseMoved(const MouseEvent& event) {
  mouseMoved();
}

inline void Sketch::mouseEntered(const MouseEvent& event) {
  mouseEntered();
}

inline void Sketch::mouseExited(const MouseEvent& event) {
  mouseExited();
}

inline void Sketch::mouseWheel(const MouseEvent& event) {
  mouseWheel();
}

inline void Sketch::keyPressed(const KeyEvent& event) {
  keyPressed();
}

inline void Sketch::keyReleased(const KeyEvent& event) {
  keyReleased();
}

inline void Sketch::touchesBegan(const TouchEvent& event) {
  touchesBegan();
}

inline void Sketch::touchesMoved(const TouchEvent& event) {
  touchesMoved();
}

inline void Sketch::touchesCancelled(const TouchEvent& event) {
  touchesCancelled();
}

inline void Sketch::touchesEnded(const TouchEvent& event) {
  touchesEnded();
}

inline void Sketch::motionBegan(const MotionEvent& event) {
  motionBegan();
}

inline void Sketch::motionCancelled(const MotionEvent& event) {
  motionCancelled();
}

inline void Sketch::motionEnded(const MotionEvent& event) {
  motionEnded();
}

#pragma mark Event handlers

template <typename Event>
inline void Sketch::enqueueEvent(const Event& event) {
  event_queue_.emplace_back(event);
}

inline void Sketch::dequeueEvent(const Event& event) {
  switch (event.type) {
    case Event::Type::MOUSE:
      handleMouseEvent(event.mouse());
      break;
    case Event::Type::KEY:
      handleKeyEvent(event.key());
      break;
    case Event::Type::TOUCH:
      handleTouchEvent(event.touch());
      break;
    case Event::Type::GESTURE:
      handleGestureEvent(event.gesture());
      break;
    case Event::Type::MOTION:
      handleMotionEvent(event.motion());
      break;
    default:
      assert(false);
      break;
  }
}

inline void Sketch::dequeueEvents() {
  for (const auto& event : event_queue_) {
    dequeueEvent(event);
  }
  event_queue_.clear();
}

#pragma mark Lifecycle overridden from Runnable

inline void Sketch::setup(const AppEvent& event) {
  setup_time_ = std::chrono::system_clock::now();
  width_ = event.size.width;
  height_ = event.size.height;
  Runnable::setup(event);
}

inline void Sketch::update(const AppEvent& event) {
  Runnable::update(event);
}

inline void Sketch::draw(const AppEvent& event) {
  width_ = event.size.width;
  height_ = event.size.height;
  pmouse_ = dmouse_;
  Runnable::draw(event);
  dmouse_ = mouse_;
  dequeueEvents();
}

inline void Sketch::post(const AppEvent& event) {
  Runnable::post(event);
}

inline void Sketch::exit(const AppEvent& event) {
  Runnable::exit(event);
}

#pragma mark Events overridden from Runnable

inline void Sketch::mouseDown(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::mouseDrag(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::mouseUp(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::mouseMove(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::mouseEnter(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::mouseExit(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::scrollWheel(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::keyDown(const KeyEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::keyUp(const KeyEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::touchesBegin(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::touchesMove(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::touchesCancel(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::touchesEnd(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::motionBegin(const MotionEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::motionCancel(const MotionEvent& event) {
  enqueueEvent(event);
}

inline void Sketch::motionEnd(const MotionEvent& event) {
  enqueueEvent(event);
}

#pragma mark Context

inline const graphics::ContextHolder& Sketch::context() const {
  return Runnable::context();
}

}  // namespace processing
}  // namespace solas

#endif  // SOLAS_PROCESSING_SKETCH_H_
