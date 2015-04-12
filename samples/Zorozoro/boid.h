//
//  boid.h
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

#include <list>
#include <memory>

#include "solas/processing.h"

namespace zorozoro {

using namespace solas::processing;

class Boid : public solas::processing::Layer {
 public:
  explicit Boid(Layer *parent);
  void flock(const std::list<std::unique_ptr<Boid>>& boids);
  virtual void update();
  virtual void draw() = 0;
  virtual void wraparound();
  Vec2 separate(const std::list<std::unique_ptr<Boid>>& boids);
  Vec2 align(const std::list<std::unique_ptr<Boid>>& boids);
  Vec2 cohere(const std::list<std::unique_ptr<Boid>>& boids);
  Vec2 seek(const Vec2& target);
  Vec2 steer(const Vec2& direction);

 public:
  Vec2 location;
  Vec2 velocity;
  Vec2 acceleration;
  static constexpr double max_force = 0.03;
  static constexpr double max_velocity = 2.0;
  static constexpr double separation_distance = 45.0;
  static constexpr double alignment_distance = 70.0;
  static constexpr double cohesion_distance = 80.0;
};

}  // namespace zorozoro
