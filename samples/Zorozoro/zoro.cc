//
//  zoro.cc
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//  Copyright (C) 2015 takram design engineering
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

#include "zoro.h"

#include "nanovg.h"
#include "zorozoro.h"

namespace zorozoro {

using solas::math::Vec2d;

Zoro::Zoro(Layer *parent, const Vec2d& location)
    : Boid(parent, location),
      scale(),
      eye_shutter(),
      winking_counter(),
      winking_limit(random(150)) {
  const auto segment = length / 2;
  body.location = location + velocity * -segment;
  body.mass = 2;
  body.length = segment;
  tail.location = body.location + velocity * -segment;
  tail.mass = 2;
  tail.length = segment;
  tween<Time>(&scale, 1, BounceEasing::Out, 0.5, random(1));
}

Zoro::~Zoro() {
  timeline<Time>().remove(&scale);
  timeline<Time>().remove(&eye_shutter);
}

void Zoro::update() {
  Boid::update();
  const auto gravity = velocity.normalized() * -2;
  body.update(location);
  tail.update(body.location);
  body.gravity = gravity;
  tail.gravity = gravity;
  rotation = (body.location - location).heading();
  if (winking_counter++ == winking_limit) {
    tween<Time>(&eye_shutter, 1, QuadraticEasing::In, 0.05, [this]() {
      tween<Time>(&eye_shutter, 0, QuadraticEasing::In, 0.33);
    });
    winking_counter = 0;
    winking_limit = random(90, 150);
  }
}

void Zoro::draw() {
  const auto& zorozoro = static_cast<Zorozoro&>(parent());
  NVGcontext *context = zorozoro.context;
  drawAll(zorozoro);
  const auto bounds = length * 2;
  const bool top = location.y < bounds;
  const bool left = location.x < bounds;
  const bool bottom = location.y > height() - bounds;
  const bool right = location.x > width() - bounds;
  if (top) {
    nvgSave(context);
    nvgTranslate(context, 0, height());
    drawAll(zorozoro);
    nvgRestore(context);
  } else if (bottom) {
    nvgSave(context);
    nvgTranslate(context, 0, -height());
    drawAll(zorozoro);
    nvgRestore(context);
  }
  if (left) {
    nvgSave(context);
    nvgTranslate(context, width(), 0);
    drawAll(zorozoro);
    nvgRestore(context);
  } else if (right) {
    nvgSave(context);
    nvgTranslate(context, -width(), 0);
    drawAll(zorozoro);
    nvgRestore(context);
  }
  if (top && left) {
    nvgSave(context);
    nvgTranslate(context, width(), height());
    drawAll(zorozoro);
    nvgRestore(context);
  } else if (top && right) {
    nvgSave(context);
    nvgTranslate(context, -width(), height());
    drawAll(zorozoro);
    nvgRestore(context);
  } else if (bottom && left) {
    nvgSave(context);
    nvgTranslate(context, width(), -height());
    drawAll(zorozoro);
    nvgRestore(context);
  } else if (bottom && right) {
    nvgSave(context);
    nvgTranslate(context, -width(), -height());
    drawAll(zorozoro);
    nvgRestore(context);
  }
}

void Zoro::drawAll(const Zorozoro& zorozoro) {
  NVGcontext *context = zorozoro.context;
  nvgSave(context);
  nvgRotate(context, rotation);
  nvgTranslate(context, -length / 3, thickness / 4);
  nvgRotate(context, -rotation);
  nvgTranslate(context, location.x, location.y);
  nvgScale(context, scale, scale);
  drawBody(zorozoro);
  drawEyes(zorozoro);
  nvgRestore(context);
}

void Zoro::drawBody(const Zorozoro& zorozoro) {
  NVGcontext *context = zorozoro.context;
  nvgSave(context);
  const auto p1 = -(body.location - location).normalize() * thickness / 2;
  const auto p2 = body.location - location;
  const auto p3 = tail.location - location +
      (tail.location - body.location).normalize() * thickness / 2;
  nvgBeginPath(context);
  nvgMoveTo(context, p1.x, p1.y);
  nvgLineTo(context, p2.x, p2.y);
  nvgLineTo(context, p3.x, p3.y);
  nvgStrokeColor(context, zorozoro.foreground);
  nvgStrokeWidth(context, thickness);
  nvgLineJoin(context, NVG_ROUND);
  nvgStroke(context);
  nvgRestore(context);
}

void Zoro::drawEyes(const Zorozoro& zorozoro) {
  NVGcontext *context = zorozoro.context;
  const double half = thickness / 2;
  const double third = thickness / 3;
  const double quarter = thickness / 4;
  nvgSave(context);
  nvgRotate(context, rotation);
  nvgTranslate(context, -thickness / 2 + half, -thickness / 2 - quarter);
  for (int i = 0; i < 2; ++i) {
    nvgBeginPath(context);
    nvgRect(context, -half, -half, thickness, thickness);
    nvgFillColor(context, zorozoro.foreground);
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, half, half);
    nvgFillColor(context, zorozoro.background);
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, third, third);
    nvgFillColor(context, zorozoro.foreground);
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, half, half * eye_shutter);
    nvgFillColor(context, zorozoro.foreground);
    nvgFill(context);
    nvgTranslate(context, thickness + quarter, 0);
  }
  nvgRestore(context);
}

void Zoro::wraparound() {
  const auto before = location;
  Boid::wraparound();
  const auto delta = location - before;
  body.location += delta;
  tail.location += delta;
}

void Zoro::kill() {
  zombie = true;
  tween<Time>(&scale, 0, QuinticEasing::Out, 0.25, random(1), [this]() {
    dead = true;
  });
}

}  // namespace zorozoro
