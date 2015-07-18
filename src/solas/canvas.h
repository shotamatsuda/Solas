//
//  solas/canvas.h
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
#ifndef SOLAS_CANVAS_H_
#define SOLAS_CANVAS_H_

#include <cstdint>
#include <list>
#include <queue>
#include <unordered_map>

#include <boost/signals2.hpp>

#include "solas/app_event.h"
#include "solas/composite.h"
#include "solas/event_holder.h"
#include "solas/gesture_event.h"
#include "solas/key_event.h"
#include "solas/motion_event.h"
#include "solas/mouse_button.h"
#include "solas/mouse_event.h"
#include "solas/runnable.h"
#include "solas/touch_event.h"
#include "solas/math.h"

namespace solas {

class Runner;

class Canvas : public Runnable, public Composite {
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
    static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas);

    template <class Slot>
    static void Disconnect(Type type, const Slot& slot, Canvas *canvas);
  };

 public:
  Canvas();
  virtual ~Canvas() = 0;

  // Disallow copy semantics
  Canvas(const Canvas& other) = delete;
  Canvas& operator=(const Canvas& other) = delete;

  // Move semantics
  Canvas(Canvas&& other) = default;
  Canvas& operator=(Canvas&& other) = default;

  // Structure
  double width() const override;
  double height() const override;
  double scale() const override;

  // Mouse
  const Vec2d& mouse() const override;
  const Vec2d& pmouse() const override;
  MouseButton mouse_button() const override;
  bool mouse_pressed() const override;

  // Keyboard
  char key() const override;
  std::uint32_t key_code() const override;
  bool key_pressed() const override;

  // Touches
  const Vec2d& touch() const override;
  const Vec2d& ptouch() const override;
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
  void setup(const AppEvent& event, const Runner&) override;
  void update(const AppEvent& event, const Runner&) override;
  void pre(const AppEvent& event, const Runner&) override;
  void draw(const AppEvent& event, const Runner&) override;
  void post(const AppEvent& event, const Runner&) override;
  void exit(const AppEvent& event, const Runner&) override;

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

  // Structure
  double width_;
  double height_;
  double scale_;

  // Mouse
  Vec2d mouse_;
  Vec2d pmouse_;
  Vec2d dmouse_;
  Vec2d emouse_;
  MouseButton mouse_button_;
  bool mouse_pressed_;

  // Keyboard
  char key_;
  std::uint32_t key_code_;
  bool key_pressed_;

  // Mouse
  Vec2d touch_;
  Vec2d ptouch_;
  Vec2d dtouch_;
  Vec2d etouch_;
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

inline Canvas::Canvas()
    : width_(),
      height_(),
      scale_(),
      mouse_button_(MouseButton::UNDEFINED),
      mouse_pressed_(),
      key_(),
      key_code_(),
      key_pressed_(),
      touch_pressed_() {}

inline Canvas::~Canvas() {}

#pragma mark Structure

inline double Canvas::width() const {
  return width_;
}

inline double Canvas::height() const {
  return height_;
}

inline double Canvas::scale() const {
  return scale_;
}

#pragma mark Mouse

inline const Vec2d& Canvas::mouse() const {
  return mouse_;
}

inline const Vec2d& Canvas::pmouse() const {
  return pmouse_;
}

inline MouseButton Canvas::mouse_button() const {
  return mouse_button_;
}

inline bool Canvas::mouse_pressed() const {
  return mouse_pressed_;
}

#pragma mark Keyboard

inline char Canvas::key() const {
  return key_;
}

inline std::uint32_t Canvas::key_code() const {
  return key_code_;
}

inline bool Canvas::key_pressed() const {
  return key_pressed_;
}

#pragma mark Touches

inline const Vec2d& Canvas::touch() const {
  return touch_;
}

inline const Vec2d& Canvas::ptouch() const {
  return ptouch_;
}

inline bool Canvas::touch_pressed() const {
  return touch_pressed_;
}

#pragma mark Aggregation

inline Composite * Canvas::parent() const {
  return nullptr;
}

#pragma mark Event connection

template <class Event, class Slot, class Type>
inline Canvas::EventConnection Canvas::connect(Type type, const Slot& slot) {
  return EventConnector<Event>::Connect(type, slot, this);
}

template <class Event, class Slot, class Type>
inline void Canvas::disconnect(Type type, const Slot& slot) {
  EventConnector<Event>::Disconnect(type, slot, this);
}

#pragma mark Event handlers

template <class Event>
inline void Canvas::enqueueEvent(const Event& event) {
  event_queue_.emplace(event);
}

inline void Canvas::dequeueEvents() {
  while (!event_queue_.empty()) {
    handleEvent(event_queue_.front());
    event_queue_.pop();
  }
}

inline void Canvas::handleEvent(const EventHolder& event) {
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

#pragma mark Lifecycle

inline void Canvas::setup(const AppEvent& event, const Runner&) {
  width_ = event.size().width;
  height_ = event.size().height;
  scale_ = event.scale();
  setup(event);
  setup();
  app_event_signals_[AppEvent::Type::SETUP](event);
}

inline void Canvas::update(const AppEvent& event, const Runner&) {
  update(event);
  update();
  app_event_signals_[AppEvent::Type::UPDATE](event);
}

inline void Canvas::pre(const AppEvent& event, const Runner&) {
  pre(event);
  pre();
  app_event_signals_[AppEvent::Type::PRE](event);
}

inline void Canvas::draw(const AppEvent& event, const Runner&) {
  width_ = event.size().width;
  height_ = event.size().height;
  scale_ = event.scale();
  pmouse_ = dmouse_;
  ptouch_ = dtouch_;
  draw(event);
  draw();
  app_event_signals_[AppEvent::Type::DRAW](event);
  dmouse_ = mouse_;
  dtouch_ = touch_;
  dequeueEvents();
}

inline void Canvas::post(const AppEvent& event, const Runner&) {
  app_event_signals_[AppEvent::Type::POST](event);
  post(event);
  post();
}

inline void Canvas::exit(const AppEvent& event, const Runner&) {
  app_event_signals_[AppEvent::Type::EXITED](event);
  exit(event);
  exit();
}

#pragma mark Events

inline void Canvas::mousePressed(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseDragged(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseReleased(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseMoved(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseEntered(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseExited(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::mouseWheel(const MouseEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::keyPressed(const KeyEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::keyReleased(const KeyEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::touchesBegan(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::touchesMoved(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::touchesCancelled(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::touchesEnded(const TouchEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::gestureBegan(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::gestureChanged(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::gestureCancelled(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::gestureEnded(const GestureEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::motionBegan(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::motionCancelled(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

inline void Canvas::motionEnded(const MotionEvent& event, const Runner&) {
  enqueueEvent(event);
}

#pragma mark -

template <>
struct Canvas::EventConnector<AppEvent> {
  using Type = AppEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->app_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->app_event_signals_[type].disconnect(slot);
  }
};

template <>
struct Canvas::EventConnector<MouseEvent> {
  using Type = MouseEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->mouse_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->mouse_event_signals_[type].disconnect(slot);
  }
};

template <>
struct Canvas::EventConnector<KeyEvent> {
  using Type = KeyEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->key_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->key_event_signals_[type].disconnect(slot);
  }
};

template <>
struct Canvas::EventConnector<TouchEvent> {
  using Type = TouchEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->touch_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->touch_event_signals_[type].disconnect(slot);
  }
};

template <>
struct Canvas::EventConnector<GestureEvent> {
  using Type = GestureEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->gesture_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->gesture_event_signals_[type].disconnect(slot);
  }
};

template <>
struct Canvas::EventConnector<MotionEvent> {
  using Type = MotionEvent::Type;

  template <class Slot>
  static EventConnection Connect(Type type, const Slot& slot, Canvas *canvas) {
    return canvas->motion_event_signals_[type].connect(slot);
  }

  template <class Slot>
  static void Disconnect(Type type, const Slot& slot, Canvas *canvas) {
    canvas->motion_event_signals_[type].disconnect(slot);
  }
};

}  // namespace solas

#endif  // SOLAS_CANVAS_H_
