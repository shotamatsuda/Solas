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

#include "solas/processing.h"

#include "boid.h"
#include "spring.h"

namespace zorozoro {

using namespace solas::processing;

class Zoro : public Boid {
 public:
  explicit Zoro(Layer *parent);
  void wraparound(double insets) override;
  void update() override;
  void draw() override;

 public:
  Spring body;
  Spring tail;
  double rotation;
  double eye_shutter;
  static constexpr double length = 28;
  static constexpr double thickness = 10;
};

}  // namespace zorozoro
