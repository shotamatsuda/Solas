//
//  zorozoro/zorozoro.cc
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

#include "zorozoro.h"

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <list>
#include <memory>
#include <utility>

#include "nanovg.h"
#include "solas/app.h"

#include "boid.h"
#include "zoro.h"

namespace zorozoro {

Zorozoro::Zorozoro()
    : context(nullptr),
      foreground(nvgRGB(0, 0, 0)),
      background(nvgRGB(0xff, 0xff, 0xff)),
      density(200) {}

void Zorozoro::setup() {
  context = createContext();
}

void Zorozoro::update() {
  const int count = width() * height() / 1000000 * density;
  const int alive = std::count_if(
      boids.begin(), boids.end(), std::mem_fn(&Boid::alive));
  if (count - alive > 0) {
    auto born = std::size_t();
    while (born < count - alive) {
      boids.emplace_back(std::make_unique<Zoro>(
          this, Vec2d(random(width()), random(height()))));
      ++born;
    }
  } else if (count - alive < 0) {
    auto killed = std::size_t();
    while (killed < alive - count) {
      auto itr = boids.begin();
      std::advance(itr, random(boids.size()));
      (*itr)->kill();
      ++killed;
    }
  }
  for (auto itr = boids.begin(); itr != boids.end();) {
    if ((*itr)->dead) {
      boids.erase(itr++);
    } else {
      ++itr;
    }
  }
  if (!context) return;
  for (auto& boid : boids) {
    boid->flock(boids);
    boid->update();
    boid->wraparound(insets);
  }
}

void Zorozoro::draw() {
  clearContext();
  if (!context) return;
  nvgBeginFrame(context, width(), height(), width() / height());
  for (const auto& boid : boids) {
    boid->draw();
  }
  nvgEndFrame(context);
}

}  // namespace zorozoro
