//
//  solas/view.h
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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
#ifndef SOLAS_VIEW_H_
#define SOLAS_VIEW_H_

#include <cassert>
#include <cstdint>
#include <list>
#include <queue>
#include <unordered_map>
#include <utility>

#include <boost/signals2.hpp>
#include <glm/glm.hpp>

#include "solas/app_event.h"
#include "solas/composite.h"
#include "solas/event_holder.h"
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_button.h"
#include "solas/mouse_event.h"
#include "solas/runnable.h"
#include "solas/runner.h"
#include "solas/touch_event.h"

namespace solas {

class Runner;

class View : public Runnable, public Composite {
 public:
  using EventConnection = boost::signals2::connection;
  using EventConnectionList = std::list<boost::signals2::scoped_connection>;

 private:
  template <class Event>
  using EventSignals = std::unordered_map<
      typename Event::Type,
      boost::signals2::signal<void(const Event&)>>;

 private:
  template <class Event, class Type = typename Event::Type>
  struct EventConnector {
    template <class Slot>
    static EventConnection connect(Type type, const Slot& slot, View *view);

    template <class Slot>
    static void disconnect(Type type, const Slot& slot, View *view);
  };

 public:
  View();
  virtual ~View() = 0;

  // Disallow copy semantics
  View(const View&) = delete;
  View& operator=(const View&) = delete;

  // Move semantics
  View(View&&) = default;
  View& operator=(View&&) = default;

  // Environment
  void frameRate(double fps) const override;
  void resize(const glm::vec2& size) const override;
  void resize(double width, double height) const override;
  void fullScreen(bool flag) const override;

  // Structure
  const glm::vec2& size() const override;
  double width() const override;
  double height() const override;
  double scale() const override;

  // Mouse
  const glm::vec2& mouse() const override;
  const glm::vec2& pmouse() const override;
  MouseButton mouse_button() const override;
  bool mouse_pressed() const override;

  // Key
  char key() const override;
  std::uint32_t key_code() const override;
  bool key_pressed() const override;

  // Touches
  const glm::vec2& touch() const override;
  const glm::vec2& ptouch() const override;
  bool touch_pressed() const override;

  // Aggregation
  Composite * parent() const override;

  // Event connection
  template <class Event, class Slot, class Type = typename Event::Type>
  EventConnection connect(Type type, const Slot& slot);
  template <class Event, class Slot, class Type = typename Event::Type>
  void disconnect(Type type, const Slot& slot);

 protected:
  // Lifecycle
  virtual void setup(const AppEvent& event) {}
  virtual void update(const AppEvent& event) {}
  virtual void pre(const AppEvent& event) {}
  virtual void draw(const AppEvent& event) {}
  virtual void post(const AppEvent& event) {}
  virtual void exit(const AppEvent& event) {}
  virtual void setup() {}
  virtual void update() {}
  virtual void pre() {}
  virtual void draw() {}
  virtual void post() {}
  virtual void exit() {}

  // Events
  virtual void mousePressed(const MouseEvent& event) {}
  virtual void mouseDragged(const MouseEvent& event) {}
  virtual void mouseReleased(const MouseEvent& event) {}
  virtual void mouseMoved(const MouseEvent& event) {}
  virtual void mouseEntered(const MouseEvent& event) {}
  virtual void mouseExited(const MouseEvent& event) {}
  virtual void mouseWheel(const MouseEvent& event) {}
  virtual void keyPressed(const KeyEvent& event) {}
  virtual void keyReleased(const KeyEvent& event) {}
  virtual void touchesBegan(const TouchEvent& event) {}
  virtual void touchesMoved(const TouchEvent& event) {}
  virtual void touchesCancelled(const TouchEvent& event) {}
  virtual void touchesEnded(const TouchEvent& event) {}
  virtual void gestureBegan(const GestureEvent& event) {}
  virtual void gestureChanged(const GestureEvent& event) {}
  virtual void gestureCancelled(const GestureEvent& event) {}
  virtual void gestureEnded(const GestureEvent& event) {}
  virtual void motionBegan(const MotionEvent& event) {}
  virtual void motionCancelled(const MotionEvent& event) {}
  virtual void motionEnded(const MotionEvent& event) {}
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
  template <class Event>
  void enqueueEvent(const Event& event);
  void dequeueEvents();
  void handleEvent(const EventHolder& event);
  void handleMouseEvent(const MouseEvent& event);
  void handleKeyEvent(const KeyEvent& event);
  void handleTouchEvent(const TouchEvent& event);
  void handleGestureEvent(const GestureEvent& event);
  void handleMotionEvent(const MotionEvent& event);

  // Lifecycle
  void setup(const AppEvent& event, const Runner& runner) override;
  void update(const AppEvent& event, const Runner& runner) override;
  void pre(const AppEvent& event, const Runner& runner) override;
  void draw(const AppEvent& event, const Runner& runner) override;
  void post(const AppEvent& event, const Runner& runner) override;
  void exit(const AppEvent& event, const Runner& runner) override;

  // Events
  void mousePressed(const MouseEvent& event, const Runner&) override;
  void mouseDragged(const MouseEvent& event, const Runner&) override;
  void mouseReleased(const MouseEvent& event, const Runner&) override;
  void mouseMoved(const MouseEvent& event, const Runner&) override;
  void mouseEntered(const MouseEvent& event, const Runner&) override;
  void mouseExited(const MouseEvent& event, const Runner&) override;
  void mouseWheel(const MouseEvent& event, const Runner&) override;
  void keyPressed(const KeyEvent& event, const Runner&) override;
  void keyReleased(const KeyEvent& event, const Runner&) override;
  void touchesBegan(const TouchEvent& event, const Runner&) override;
  void touchesMoved(const TouchEvent& event, const Runner&) override;
  void touchesCancelled(const TouchEvent& event, const Runner&) override;
  void touchesEnded(const TouchEvent& event, const Runner&) override;
  void gestureBegan(const GestureEvent& event, const Runner&) override;
  void gestureChanged(const GestureEvent& event, const Runner&) override;
  void gestureCancelled(const GestureEvent& event, const Runner&) override;
  void gestureEnded(const GestureEvent& event, const Runner&) override;
  void motionBegan(const MotionEvent& event, const Runner&) override;
  void motionCancelled(const MotionEvent& event, const Runner&) override;
  void motionEnded(const MotionEvent& event, const Runner&) override;

 private:
  std::queue<EventHolder> event_queue_;

  // Environment
  mutable std::pair<bool, double> frame_rate_;
  mutable std::pair<bool, glm::vec2> resize_;
  mutable std::pair<bool, bool> full_screen_;

  // Structure
  glm::vec2 size_;
  double scale_;

  // Mouse
  glm::vec2 mouse_;
  glm::vec2 pmouse_;
  glm::vec2 dmouse_;
  glm::vec2 emouse_;
  MouseButton mouse_button_;
  bool mouse_pressed_;

  // Key
  char key_;
  std::uint32_t key_code_;
  bool key_pressed_;

  // Mouse
  glm::vec2 touch_;
  glm::vec2 ptouch_;
  glm::vec2 dtouch_;
  glm::vec2 etouch_;
  bool touch_pressed_;

  // Event signals
  EventSignals<AppEvent> app_event_signals_;
  EventSignals<MouseEvent> mouse_event_signals_;
  EventSignals<KeyEvent> key_event_signals_;
  EventSignals<TouchEvent> touch_event_signals_;
  EventSignals<GestureEvent> gesture_event_signals_;
  EventSignals<MotionEvent> motion_event_signals_;
};

#pragma mark -

inline View::View()
    : scale_(),
      mouse_button_(MouseButton::UNDEFINED),
      mouse_pressed_(),
      key_(),
      key_code_(),
      key_pressed_(),
      touch_pressed_() {}

inline View::~View() {}

#pragma mark Environment

inline void View::frameRate(double fps) const {
  frame_rate_.first = true;
  frame_rate_.second = fps;
}

inline void View::resize(const glm::vec2& size) const {
  resize_.first = true;
  resize_.second = size;
}

inline void View::resize(double width, double height) const {
  resize(glm::vec2(width, height));
}

inline void View::fullScreen(bool flag) const {
  full_screen_.first = true;
  full_screen_.second = true;
}

#pragma mark Structure

inline double View::width() const {
  return size_.x;
}

inline double View::height() const {
  return size_.y;
}

inline double View::scale() const {
  return scale_;
}

inline const glm::vec2& View::size() const {
  return size_;
}

#pragma mark Mouse

inline const glm::vec2& View::mouse() const {
  return mouse_;
}

inline const glm::vec2& View::pmouse() const {
  return pmouse_;
}

inline MouseButton View::mouse_button() const {
  return mouse_button_;
}

inline bool View::mouse_pressed() const {
  return mouse_pressed_;
}

#pragma mark Key

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

inline const glm::vec2& View::touch() const {
  return touch_;
}

inline const glm::vec2& View::ptouch() const {
  return ptouch_;
}

inline bool View::touch_pressed() const {
  return touch_pressed_;
}

#pragma mark Aggregation

inline Composite * View::parent() const {
  return nullptr;
}

#pragma mark Event connection

template <class Event, class Slot, class Type>
inline View::EventConnection View::connect(Type type, const Slot& slot) {
  return EventConnector<Event>::connect(type, slot, this);
}

template <class Event, class Slot, class Type>
inline void View::disconnect(Type type, const Slot& slot) {
  EventConnector<Event>::disconnect(type, slot, this);
}

#pragma mark Event handlers

template <class Event>
inline void View::enqueueEvent(const Event& event) {
  event_queue_.emplace(event);
}

inline void View::dequeueEvents() {
  while (!event_queue_.empty()) {
    handleEvent(event_queue_.front());
    event_queue_.pop();
  }
}

inline void View::handleEvent(const EventHolder& event) {
  switch (event.type()) {
    case EventHolder::Type::MOUSE:
      handleMouseEvent(event.mouse());
      break;
    case EventHolder::Type::KEY:
      handleKeyEvent(event.key());
      break;
    case EventHolder::Type::TOUCH:
      handleTouchEvent(event.touch());
      break;
    case EventHolder::Type::GESTURE:
      handleGestureEvent(event.gesture());
      break;
    case EventHolder::Type::MOTION:
      handleMotionEvent(event.motion());
      break;
    default:
      assert(false);
      break;
  }
}

#pragma mark Events

inline void View::mousePressed(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseDragged(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseReleased(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseMoved(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseEntered(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseExited(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::mouseWheel(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::keyPressed(const KeyEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::keyReleased(const KeyEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::touchesBegan(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::touchesMoved(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::touchesCancelled(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::touchesEnded(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::gestureBegan(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::gestureChanged(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::gestureCancelled(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::gestureEnded(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::motionBegan(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::motionCancelled(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void View::motionEnded(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

#pragma mark -

template <>
struct View::EventConnector<AppEvent> {
  using Type = AppEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->app_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->app_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<MouseEvent> {
  using Type = MouseEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->mouse_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->mouse_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<KeyEvent> {
  using Type = KeyEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->key_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->key_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<TouchEvent> {
  using Type = TouchEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->touch_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->touch_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<GestureEvent> {
  using Type = GestureEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->gesture_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->gesture_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<MotionEvent> {
  using Type = MotionEvent::Type;

  template <class Slot>
  static EventConnection connect(Type type, const Slot& slot, View *view) {
    assert(view);
    return view->motion_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void disconnect(Type type, const Slot& slot, View *view) {
    assert(view);
    view->motion_event_signals_[type].disconnect(slot);
  }
};

}  // namespace solas

#endif  // SOLAS_VIEW_H_
