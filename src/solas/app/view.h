//
//  solas/app/view.h
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
#ifndef SOLAS_APP_VIEW_H_
#define SOLAS_APP_VIEW_H_

#include <cstdint>
#include <list>

#include "solas/app/event.h"
#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/layer.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_button.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"
#include "solas/math/vector.h"
#include "solas/tween.h"

namespace solas {
namespace app {

class View : public app::Runnable, public Layer {
 public:
  // Constructors
  View();
  virtual ~View() = 0;

  // Disallow copy and assign
  View(const View& other) = delete;
  View& operator=(const View& other) = delete;

  // Move
  View(View&& other) = default;

  // Structure
  double width() const override;
  double height() const override;

  // Mouse
  const math::Vec2d& mouse() const override;
  const math::Vec2d& pmouse() const override;
  MouseButton mouse_button() const override;
  bool mouse_pressed() const override;

  // Keyboard
  char key() const override;
  std::uint32_t key_code() const override;
  bool key_pressed() const override;

  // Touches
  const math::Vec2d& touch() const override;
  const math::Vec2d& ptouch() const override;
  bool touch_pressed() const override;

  // Aggregation
  Layer& parent() = delete;
  const Layer& parent() const = delete;

 protected:
  // Aggregation
  tween::TimelineHost * timeline_host() override;
  const tween::TimelineHost * timeline_host() const override;

  // Lifecycle intended to be overriden
  void setup() override {}
  void update() override {}
  void pre() override {}
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
  virtual void gestureBegan(const GestureEvent& event);
  virtual void gestureChanged(const GestureEvent& event);
  virtual void gestureCancelled(const GestureEvent& event);
  virtual void gestureEnded(const GestureEvent& event);
  virtual void motionBegan(const MotionEvent& event);
  virtual void motionCancelled(const MotionEvent& event);
  virtual void motionEnded(const MotionEvent& event);

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
  virtual void gestureBegan() {}
  virtual void gestureChanged() {}
  virtual void gestureCancelled() {}
  virtual void gestureEnded() {}
  virtual void motionBegan() {}
  virtual void motionCancelled() {}
  virtual void motionEnded() {}

 private:
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

  // Lifecycle overridden from Runnable
  void setup(const AppEvent& event) override;
  void update(const AppEvent& event) override;
  void pre(const AppEvent& event) override;
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
  void gestureBegin(const GestureEvent& event) override;
  void gestureChange(const GestureEvent& event) override;
  void gestureCancel(const GestureEvent& event) override;
  void gestureEnd(const GestureEvent& event) override;
  void motionBegin(const MotionEvent& event) override;
  void motionCancel(const MotionEvent& event) override;
  void motionEnd(const MotionEvent& event) override;

 private:
  std::list<Event> event_queue_;

  // Structure
  double width_;
  double height_;

  // Mouse
  math::Vec2d mouse_;
  math::Vec2d pmouse_;
  math::Vec2d dmouse_;
  math::Vec2d emouse_;
  MouseButton mouse_button_;
  bool mouse_pressed_;

  // Keyboard
  char key_;
  std::uint32_t key_code_;
  bool key_pressed_;

  // Mouse
  math::Vec2d touch_;
  math::Vec2d ptouch_;
  math::Vec2d dtouch_;
  math::Vec2d etouch_;
  bool touch_pressed_;

  // Tween
  tween::TimelineHost timeline_host_;
};

#pragma mark -

inline View::View()
    : width_(),
      height_(),
      mouse_button_(MouseButton::UNDEFINED),
      mouse_pressed_(),
      key_(),
      key_code_(),
      key_pressed_(),
      touch_pressed_() {}

inline View::~View() {}

#pragma mark Structure

inline double View::width() const {
  return width_;
}

inline double View::height() const {
  return height_;
}

#pragma mark Mouse

inline const math::Vec2d& View::mouse() const {
  return mouse_;
}

inline const math::Vec2d& View::pmouse() const {
  return pmouse_;
}

inline MouseButton View::mouse_button() const {
  return mouse_button_;
}

inline bool View::mouse_pressed() const {
  return mouse_pressed_;
}

#pragma mark Keyboard

inline char View::key() const {
  return key_;
}

inline std::uint32_t View::key_code() const {
  return key_code_;
}

inline bool View::key_pressed() const {
  return key_pressed_;
}

#pragma mark Touches

inline const math::Vec2d& View::touch() const {
  return touch_;
}

inline const math::Vec2d& View::ptouch() const {
  return ptouch_;
}

inline bool View::touch_pressed() const {
  return touch_pressed_;
}

#pragma mark Aggregation

inline tween::TimelineHost * View::timeline_host() {
  return &timeline_host_;
}

inline const tween::TimelineHost * View::timeline_host() const {
  return &timeline_host_;
}

#pragma mark Events

inline void View::mousePressed(const MouseEvent& event) {
  mousePressed();
}

inline void View::mouseDragged(const MouseEvent& event) {
  mouseDragged();
}

inline void View::mouseReleased(const MouseEvent& event) {
  mouseReleased();
}

inline void View::mouseMoved(const MouseEvent& event) {
  mouseMoved();
}

inline void View::mouseEntered(const MouseEvent& event) {
  mouseEntered();
}

inline void View::mouseExited(const MouseEvent& event) {
  mouseExited();
}

inline void View::mouseWheel(const MouseEvent& event) {
  mouseWheel();
}

inline void View::keyPressed(const KeyEvent& event) {
  keyPressed();
}

inline void View::keyReleased(const KeyEvent& event) {
  keyReleased();
}

inline void View::touchesBegan(const TouchEvent& event) {
  touchesBegan();
}

inline void View::touchesMoved(const TouchEvent& event) {
  touchesMoved();
}

inline void View::touchesCancelled(const TouchEvent& event) {
  touchesCancelled();
}

inline void View::touchesEnded(const TouchEvent& event) {
  touchesEnded();
}

inline void View::gestureBegan(const GestureEvent& event) {
  gestureBegan();
}

inline void View::gestureChanged(const GestureEvent& event) {
  gestureChanged();
}

inline void View::gestureCancelled(const GestureEvent& event) {
  gestureCancelled();
}

inline void View::gestureEnded(const GestureEvent& event) {
  gestureEnded();
}

inline void View::motionBegan(const MotionEvent& event) {
  motionBegan();
}

inline void View::motionCancelled(const MotionEvent& event) {
  motionCancelled();
}

inline void View::motionEnded(const MotionEvent& event) {
  motionEnded();
}

#pragma mark Event handlers

template <typename Event>
inline void View::enqueueEvent(const Event& event) {
  event_queue_.emplace_back(event);
}

inline void View::dequeueEvent(const Event& event) {
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

inline void View::dequeueEvents() {
  for (const auto& event : event_queue_) {
    dequeueEvent(event);
  }
  event_queue_.clear();
}

#pragma mark Lifecycle overridden from Runnable

inline void View::setup(const AppEvent& event) {
  width_ = event.size.width;
  height_ = event.size.height;
  Runnable::setup(event);
}

inline void View::update(const AppEvent& event) {
  timeline<tween::Time>().advance();
  timeline<tween::Frame>().advance();
  Runnable::update(event);
}

inline void View::pre(const AppEvent& event) {
  Runnable::pre(event);
}

inline void View::draw(const AppEvent& event) {
  width_ = event.size.width;
  height_ = event.size.height;
  pmouse_ = dmouse_;
  ptouch_ = dtouch_;
  Runnable::draw(event);
  dmouse_ = mouse_;
  dtouch_ = touch_;
  dequeueEvents();
}

inline void View::post(const AppEvent& event) {
  Runnable::post(event);
}

inline void View::exit(const AppEvent& event) {
  Runnable::exit(event);
}

#pragma mark Events overridden from Runnable

inline void View::mouseDown(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::mouseDrag(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::mouseUp(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::mouseMove(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::mouseEnter(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::mouseExit(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::scrollWheel(const MouseEvent& event) {
  enqueueEvent(event);
}

inline void View::keyDown(const KeyEvent& event) {
  enqueueEvent(event);
}

inline void View::keyUp(const KeyEvent& event) {
  enqueueEvent(event);
}

inline void View::touchesBegin(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void View::touchesMove(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void View::touchesCancel(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void View::touchesEnd(const TouchEvent& event) {
  enqueueEvent(event);
}

inline void View::gestureBegin(const GestureEvent& event) {
  enqueueEvent(event);
}

inline void View::gestureChange(const GestureEvent& event) {
  enqueueEvent(event);
}

inline void View::gestureCancel(const GestureEvent& event) {
  enqueueEvent(event);
}

inline void View::gestureEnd(const GestureEvent& event) {
  enqueueEvent(event);
}

inline void View::motionBegin(const MotionEvent& event) {
  enqueueEvent(event);
}

inline void View::motionCancel(const MotionEvent& event) {
  enqueueEvent(event);
}

inline void View::motionEnd(const MotionEvent& event) {
  enqueueEvent(event);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_VIEW_H_
