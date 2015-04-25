//
//  boid.cc
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

#include "boid.h"

#include <list>
#include <memory>

namespace zorozoro {

using solas::math::Vec2d;

Boid::Boid(Layer *parent, const Vec2d& location)
    : Layer(parent),
      location(location),
      velocity(Vec2d::Random(-1, 1).normalize()),
      zombie(false),
      dead(false) {}

void Boid::flock(const std::list<std::unique_ptr<Boid>>& boids) {
  acceleration.reset();
  acceleration += separate(boids) * 1.8;
  acceleration += align(boids);
  acceleration += cohere(boids);
}

void Boid::update() {
  velocity += acceleration;
  velocity.limit(max_velocity);
  location += velocity;
}

void Boid::wraparound(double insets) {
  const Vec2d span(width() + insets * 2, height() + insets * 2);
  location.x += -span.x * std::floor((location.x + insets) / span.x);
  location.y += -span.y * std::floor((location.y + insets) / span.y);
}

void Boid::kill() {
  dead = true;
}

Vec2d Boid::separate(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2d target;
  auto count = int();
  for (const auto& other : boids) {
    const auto distance = location.distance(other->location);
    if (distance && distance < separation_distance) {
      target += (location - other->location).normalize() / distance;
      ++count;
    }
  }
  if (count) {
    return steer(target / count);
  }
  return Vec2d();
}

Vec2d Boid::align(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2d target;
  auto count = int();
  for (const auto& other : boids) {
    const auto distance = location.distance(other->location);
    if (distance && distance < alignment_distance) {
      target += other->velocity;
      ++count;
    }
  }
  if (count) {
    return steer(target);
  }
  return Vec2d();
}

Vec2d Boid::cohere(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2d target;
  auto count = int();
  for (const auto& other : boids) {
    const auto distance = location.distance(other->location);
    if (distance && distance < cohesion_distance) {
      target += other->location;
      ++count;
    }
  }
  if (count) {
    return seek(target / count);
  }
  return Vec2d();
}

Vec2d Boid::seek(const Vec2d& target) {
  return steer(target - location);
}

Vec2d Boid::steer(const Vec2d& direction) {
  return (direction.normalized() * max_velocity - velocity).limit(max_force);
}

}  // namespace zorozoro
