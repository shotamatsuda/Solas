//
//  main.cc
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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

#include <vector>

#include "solas/app.h"
#include "solas/graphics.h"
#include "solas/math.h"
#include "solas/nanovg.h"
#include "solas/utility.h"

namespace app = solas::app;
namespace gfx = solas::graphics;
namespace math = solas::math;
namespace nvg = solas::nanovg;

class App : public solas::app::View {
 public:
  void setup() override {
    context_.init();
    width_ = 40;
    path_.moveTo(300, 300);
    path_.cubicTo(500, 100, 100, 100, 300, 300);
    path_.cubicTo(500, 500, 100, 500, 300, 300);
    needs_stroking_ = true;
  }

  void pre() override {
    context_.begin(width(), height(), scale());
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  }

  void post() override {
    context_.end();
  }

  void update() override {
    if (needs_stroking_) {
      if (width_) {
        gfx::QuadraticStroker stroker;
        stroker.set_width(width_);
        stroker.set_cap(gfx::Stroke::Cap::ROUND);
        stroker.set_join(gfx::Stroke::Join::ROUND);
        stroke_ = stroker(path_);
        needs_stroking_ = false;
      } else {
        stroke_.reset();
      }
    }
  }

  void draw() override {
    nvg::StateGuard save;
    nvg::Translate(translation_);

    nvg::BeginPath();
    nvg::Path(path_);
    nvg::StrokeWidth(1.0);
    nvg::StrokeColor(gfx::Color4f(0.0));
    nvg::Stroke();

    drawControl(path_);

    nvg::FillColor(gfx::Color4f::Black());
    for (const auto& segment : path_) {
      nvg::BeginPath();
      switch (segment.type()) {
        case gfx::Segment::Type::MOVE:
        case gfx::Segment::Type::LINE:
          if (selected_segment_ == &segment) {
            nvg::Circle(segment.point(), 4.0);
          }
          break;
        case gfx::Segment::Type::QUADRATIC:
          if (selected_segment_ == &segment) {
            if (selected_point_ == &segment.point()) {
              nvg::Circle(segment.point(), 4.0);
            } else if (selected_point_ == &segment.control()) {
              nvg::Circle(segment.control(), 4.0);
            }
          }
          break;
        case gfx::Segment::Type::CUBIC:
          if (selected_segment_ == &segment) {
            if (selected_point_ == &segment.point()) {
              nvg::Circle(segment.point(), 4.0);
            } else if (selected_point_ == &segment.control1()) {
              nvg::Circle(segment.control1(), 4.0);
            } else if (selected_point_ == &segment.control2()) {
              nvg::Circle(segment.control2(), 4.0);
            }
          }
          break;
        default:
          break;
      }
      nvg::Fill();
    }

    if (!stroke_.empty()) {
      nvg::BeginPath();
      nvg::Path(stroke_);
      nvg::FillColor(gfx::Color4f(0.0, 0.1));
      nvg::Fill();
      nvg::StrokeWidth(1.0);
      nvg::StrokeColor(gfx::Color4f(0.0, 0.5));
      nvg::Stroke();
    }
  }

  void drawControl(const gfx::Path& path) {
    nvg::StateGuard save;

    // Control lines
    nvg::BeginPath();
    for (const auto& segment : path) {
      switch (segment.type()) {
        case gfx::Segment::Type::MOVE:
          nvg::MoveTo(segment.point());
          break;
        case gfx::Segment::Type::LINE:
          nvg::LineTo(segment.point());
          break;
        case gfx::Segment::Type::QUADRATIC:
          nvg::LineTo(segment.control());
          nvg::LineTo(segment.point());
          break;
        case gfx::Segment::Type::CUBIC:
          nvg::LineTo(segment.control1());
          nvg::LineTo(segment.control2());
          nvg::LineTo(segment.point());
          break;
        case gfx::Segment::Type::CLOSE:
          nvg::ClosePath();
          break;
        default:
          break;
      }
    }
    nvg::StrokeWidth(1.0);
    nvg::StrokeColor(gfx::Color4f(0.0, 0.25));
    nvg::Stroke();

    // Control points
    nvg::StrokeWidth(1.0);
    nvg::StrokeColor(gfx::Color4f(0.0));
    for (const auto& segment : path) {
      switch (segment.type()) {
        case gfx::Segment::Type::MOVE:
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.5);
          nvg::Stroke();
          break;
        case gfx::Segment::Type::LINE:
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.5);
          nvg::Stroke();
          break;
        case gfx::Segment::Type::QUADRATIC:
          nvg::BeginPath();
          nvg::Circle(segment.control(), 3.5);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.5);
          nvg::Stroke();
          break;
        case gfx::Segment::Type::CUBIC:
          nvg::BeginPath();
          nvg::Circle(segment.control1(), 3.5);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.control2(), 3.5);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.5);
          nvg::Stroke();
          break;
        default:
          break;
      }
    }
  }

  void mouseMoved() override {
    const auto point = mouse() - translation_;
    gfx::Segment *selected_segment = nullptr;
    gfx::Segment::Point *selected_point = nullptr;
    for (auto& segment : path_) {
      switch (segment.type()) {
        case gfx::Segment::Type::MOVE:
        case gfx::Segment::Type::LINE:
          if (point.distance(segment.point()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.point();
            break;
          }
          break;
        case gfx::Segment::Type::QUADRATIC:
          if (point.distance(segment.point()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.point();
            break;
          } else if (point.distance(segment.control()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.control();
            break;
          }
          break;
        case gfx::Segment::Type::CUBIC:
          if (point.distance(segment.point()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.point();
            break;
          } else if (point.distance(segment.control1()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.control1();
            break;
          } else if (point.distance(segment.control2()) < 10.0) {
            selected_segment = &segment;
            selected_point = &segment.control2();
            break;
          }
          break;
        default:
          break;
      }
    }
    selected_segment_ = selected_segment;
    selected_point_ = selected_point;
  }

  void mouseDragged() override {
    if (selected_point_) {
      *selected_point_ = mouse() - translation_;
      needs_stroking_ = true;
    } else {
      translation_ += mouse() - pmouse();
    }
  }

  void touchesMoved() override {
    if (selected_point_) {
      *selected_point_ = touch() - translation_;
      needs_stroking_ = true;
    } else {
      translation_ += touch() - ptouch();
    }
  }

  void mouseWheel(const app::MouseEvent& event) override {
    width_ = std::max(0.0, width_ + event.wheel().y);
    needs_stroking_ = true;
  }

 private:
  nvg::Context context_;
  math::Vec2d translation_;
  double width_;
  gfx::Path path_;
  gfx::Path stroke_;
  gfx::Segment *selected_segment_;
  gfx::Segment::Point *selected_point_;
  bool needs_stroking_;
};

int main(int argc, char **argv) {
  return solas::app::Run<App>(argc, argv);
}
