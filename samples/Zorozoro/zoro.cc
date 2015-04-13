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

namespace zorozoro {

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

void Zoro::wraparound() {
  const Vec2 before = location;
  Boid::wraparound();
  const Vec2 delta = location - before;
  body.location += delta;
  tail.location += delta;
}

void Zoro::update() {
  Boid::update();
  const Vec2 gravity = velocity.normalized() * -2;
  body.update(location);
  tail.update(body.location);
  body.gravity = gravity;
  tail.gravity = gravity;
  rotation = (body.location - location).heading();
}

void Zoro::draw() {
  pushMatrix();
  rotate(rotation);
  translate(-length / 3, thickness / 4);
  rotate(-rotation);
  pushStyle();
  stroke(0);
  strokeWeight(thickness);
  strokeJoin(ROUND);
  pushMatrix();
  beginShape();
  vertex(location);
  vertex(body.location);
  vertex(tail.location);
  endShape();
  popStyle();

  float half = thickness / 2;
  float third = thickness / 3;
  float quarter = thickness / 4;
  pushStyle();
  pushMatrix();
  translate(location);
  rotate(rotation);
  translate(-thickness / 2 + half, -thickness / 2 - quarter);
  for (int i = 0; i < 2; ++i) {
    rectMode(CENTER);
    noStroke();
    fill(0);
    rect(0, 0, thickness, thickness);
    fill(0xff);
    rect(0, 0, half, half);
    fill(0);
    rectMode(CORNER);
    rect(-quarter, -quarter, third, third);
    rect(-quarter, -quarter, half, half * eye_shutter);
    translate(thickness + quarter, 0);
  }
  popMatrix();
  popStyle();

  popMatrix();
  popMatrix();
}

}  // namespace zorozoro
