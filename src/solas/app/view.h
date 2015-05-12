//
//  solas/app/view.h
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
#ifndef SOLAS_APP_VIEW_H_
#define SOLAS_APP_VIEW_H_

#include <cstdint>
#include <list>
#include <queue>
#include <unordered_map>

#include <boost/signals2.hpp>

#include "solas/app/composite.h"
#include "solas/app/event_holder.h"
#include "solas/app/gesture_event.h"
#include "solas/app/key_event.h"
#include "solas/app/motion_event.h"
#include "solas/app/mouse_button.h"
#include "solas/app/mouse_event.h"
#include "solas/app/runnable.h"
#include "solas/app/touch_event.h"
#include "solas/math/vector.h"
#include "solas/tween/timeline_host.h"

namespace solas {
namespace app {

class View : public app::Runnable, public Composite {
 public:
  using EventConnection = boost::signals2::connection;
  using EventConnectionList = std::list<boost::signals2::scoped_connection>;

 private:
  template <typename Event>
  using EventSignals = std::unordered_map<
      typename Event::Type,
      boost::signals2::signal<void(const Event&)>>;

 private:
  template <typename Event, typename Type = typename Event::Type>
  struct EventConnector {
    template <typename Slot>
    static EventConnection Connect(Type type, const Slot& slot, View *view);

    template <typename Slot>
    static void Disconnect(Type type, const Slot& slot, View *view);
  };

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
  double scale() const override;

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
  Composite * parent() const override;

  // Event connection
  template <typename Event, typename Slot, typename Type = typename Event::Type>
  EventConnection connectEvent(Type type, const Slot& slot);
  template <typename Event, typename Slot, typename Type = typename Event::Type>
  void disconnectEvent(Type type, const Slot& slot);

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

  // Events intended to be overriden
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
  template <typename Event>
  void enqueueEvent(const Event& event);
  void dequeueEvents();
  void handleEvent(const EventHolder& event);
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
  std::queue<EventHolder> event_queue_;

  // Structure
  double width_;
  double height_;
  double scale_;

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
    : width_(),
      height_(),
      scale_(),
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

inline double View::scale() const {
  return scale_;
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

inline Composite * View::parent() const {
  return nullptr;
}

inline tween::TimelineHost * View::timeline_host() {
  return &timeline_host_;
}

inline const tween::TimelineHost * View::timeline_host() const {
  return &timeline_host_;
}

#pragma mark Event connection

template <typename Event, typename Slot, typename Type>
inline View::EventConnection View::connectEvent(Type type, const Slot& slot) {
  return EventConnector<Event>::Connect(type, slot, this);
}

template <typename Event, typename Slot, typename Type>
inline void View::disconnectEvent(Type type, const Slot& slot) {
  EventConnector<Event>::Disconnect(type, slot, this);
}

#pragma mark Event handlers

template <typename Event>
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

#pragma mark Lifecycle overridden from Runnable

inline void View::setup(const AppEvent& event) {
  width_ = event.size().width;
  height_ = event.size().height;
  scale_ = event.scale();
  Runnable::setup(event);
  app_event_signals_[AppEvent::Type::SETUP](event);
}

inline void View::update(const AppEvent& event) {
  timeline<tween::Time>().advance();
  timeline<tween::Frame>().advance();
  Runnable::update(event);
  app_event_signals_[AppEvent::Type::UPDATE](event);
}

inline void View::pre(const AppEvent& event) {
  Runnable::pre(event);
  app_event_signals_[AppEvent::Type::PRE](event);
}

inline void View::draw(const AppEvent& event) {
  width_ = event.size().width;
  height_ = event.size().height;
  scale_ = event.scale();
  pmouse_ = dmouse_;
  ptouch_ = dtouch_;
  Runnable::draw(event);
  app_event_signals_[AppEvent::Type::DRAW](event);
  dmouse_ = mouse_;
  dtouch_ = touch_;
  dequeueEvents();
}

inline void View::post(const AppEvent& event) {
  app_event_signals_[AppEvent::Type::POST](event);
  Runnable::post(event);
}

inline void View::exit(const AppEvent& event) {
  app_event_signals_[AppEvent::Type::EXIT](event);
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

#pragma mark -

template <>
struct View::EventConnector<AppEvent> final {
  using Type = AppEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->app_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->app_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<MouseEvent> final {
  using Type = MouseEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->mouse_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->mouse_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<KeyEvent> final {
  using Type = KeyEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->key_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->key_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<TouchEvent> final {
  using Type = TouchEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->touch_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->touch_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<GestureEvent> final {
  using Type = GestureEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->gesture_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->gesture_event_signals_[type].disconnect(slot);
  }
};

template <>
struct View::EventConnector<MotionEvent> final {
  using Type = MotionEvent::Type;

  template <typename Slot>
  static EventConnection Connect(Type type, const Slot& slot, View *view) {
    return view->motion_event_signals_[type].connect(slot);
  }

  template <typename Slot>
  static void Disconnect(Type type, const Slot& slot, View *view) {
    view->motion_event_signals_[type].disconnect(slot);
  }
};

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_VIEW_H_
