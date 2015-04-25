//
//  zoro.h
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

#pragma once

#include "solas/app.h"
#include "solas/math.h"

#include "boid.h"
#include "spring.h"

namespace zorozoro {

using solas::math::Vec2d;

class Zoro : public Boid {
 public:
  Zoro(Layer *parent, const Vec2d& location);
  ~Zoro();
  void wraparound(double insets) override;
  void update() override;
  void draw() override;

 public:
  Spring body;
  Spring tail;
  double rotation;
  double eye_shutter;
  int winking_counter;
  int winking_limit;
  static constexpr const double length = 28;
  static constexpr const double thickness = 10;
};

}  // namespace zorozoro
