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

Zoro::Zoro(Layer *parent)
    : Boid(parent),
      eye_shutter() {
  const auto segment = length / 2;
  body.location = location + velocity * -segment;
  body.mass = 2;
  body.length = segment;
  tail.location = body.location + velocity * -segment;
  tail.mass = 2;
  tail.length = segment;
}

void Zoro::wraparound(double insets) {
  const auto before = location;
  Boid::wraparound(insets);
  const auto delta = location - before;
  body.location += delta;
  tail.location += delta;
}

void Zoro::update() {
  Boid::update();
  const auto gravity = velocity.normalized() * -2;
  body.update(location);
  tail.update(body.location);
  body.gravity = gravity;
  tail.gravity = gravity;
  rotation = (body.location - location).heading();
}

void Zoro::draw() {
  NVGcontext *context = static_cast<Zorozoro&>(parent()).context;
  nvgSave(context);
  nvgRotate(context, rotation);
  nvgTranslate(context, -length / 3, thickness / 4);
  nvgRotate(context, -rotation);

  nvgSave(context);
  const auto p1 = location - (body.location - location).normalize() * thickness / 2;
  const auto p2 = body.location;
  const auto p3 = tail.location + (tail.location - body.location).normalize() * thickness / 2;
  nvgBeginPath(context);
  nvgMoveTo(context, p1.x, p1.y);
  nvgLineTo(context, p2.x, p2.y);
  nvgLineTo(context, p3.x, p3.y);
  nvgStrokeColor(context, nvgRGB(0, 0, 0));
  nvgStrokeWidth(context, thickness);
  nvgLineJoin(context, NVG_ROUND);
  nvgStroke(context);
  nvgRestore(context);

  const double half = thickness / 2;
  const double third = thickness / 3;
  const double quarter = thickness / 4;
  nvgSave(context);
  nvgTranslate(context, location.x, location.y);
  nvgRotate(context, rotation);
  nvgTranslate(context, -thickness / 2 + half, -thickness / 2 - quarter);
  for (int i = 0; i < 2; ++i) {
    nvgBeginPath(context);
    nvgRect(context, -half, -half, thickness, thickness);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, half, half);
    nvgFillColor(context, nvgRGB(0xff, 0xff, 0xff));
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, third, third);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgFill(context);
    nvgBeginPath(context);
    nvgRect(context, -quarter, -quarter, half, half * eye_shutter);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgFill(context);
    nvgTranslate(context, thickness + quarter, 0);
  }
  nvgRestore(context);

  nvgRestore(context);
}

}  // namespace zorozoro
