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

#include <list>
#include <memory>
#include <utility>

#include "nanovg.h"
#include "solas/app.h"

#include "boid.h"
#include "zoro.h"

namespace zorozoro {

void Zorozoro::setup() {
  context = createContext();
  boids.resize(width() * height() / 4000);
  for (auto& boid : boids) {
    boid = std::make_unique<Zoro>(this);
    boid->location.x = random(width());
    boid->location.y = random(height());
  }
}

void Zorozoro::update() {
  for (auto& boid : boids) {
    boid->flock(boids);
    boid->update();
    boid->wraparound(insets);
  }
}

void Zorozoro::draw() {
  clearContext();
  nvgBeginFrame(context, width(), height(), width() / height());
  for (const auto& boid : boids) {
    boid->draw();
  }
  nvgEndFrame(context);
}

}  // namespace zorozoro
