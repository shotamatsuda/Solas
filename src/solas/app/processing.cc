//
//  solas/app/processing.cc
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

#include "solas/app/processing.h"

#include <chrono>
#include <memory>
#include <utility>

#include "solas/graphics/fill.h"
#include "solas/graphics/renderer.h"
#include "solas/graphics/stroke.h"

namespace solas {
namespace app {

Processing::Processing(std::unique_ptr<graphics::Renderer>&& renderer)
    : mouse_x(),
      mouse_y(),
      pmouse_x(),
      pmouse_y(),
      mouse_button(),
      mouse_pressed(),
      key(),
      key_code(),
      key_pressed(),
      renderer_(std::move(renderer)),
      started_time_(std::chrono::system_clock::now()) {
  style_.fill.type = graphics::FillType::SOLID;
  style_.fill.color = Color::White();
  style_.stroke.type = graphics::StrokeType::SOLID;
  style_.stroke.color = Color::Black();
  style_.stroke.weight = 1;
  style_.stroke.cap = graphics::StrokeCap::SQUARE;
  style_.stroke.join = graphics::StrokeJoin::MITER;
  style_.rect_mode = Constant::CORNER;
  style_.ellipse_mode = Constant::CENTER;
  style_.color_mode = Constant::RGB;
  style_.color_max.set(0xff, 0xff, 0xff, 0xff);
}

}  // namespace app
}  // namespace solas
