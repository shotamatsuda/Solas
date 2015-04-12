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

Boid::Boid(Layer *parent)
    : Layer(parent),
      velocity(Vec2::Random().normalize()) {}

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

void Boid::wraparound() {
  location.x += -width() * int(location.x / width());
  location.y += -height() * int(location.y / height());
}

Vec2 Boid::separate(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2 target;
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
  return Vec2();
}

Vec2 Boid::align(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2 target;
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
  return Vec2();
}

Vec2 Boid::cohere(const std::list<std::unique_ptr<Boid>>& boids) {
  Vec2 target;
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
  return Vec2();
}

Vec2 Boid::seek(const Vec2& target) {
  return steer(target - location);
}

Vec2 Boid::steer(const Vec2& direction) {
  return (direction.normalized() * max_velocity - velocity).limit(max_force);
}

}  // namespace zorozoro
