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
    width_ = 5.0;
    scale_ = 1.0;
    draws_control_ = true;
    draws_outline_ = false;

    path_.moveTo(630, 173);
    path_.cubicTo(630, 173, 630, 105, 630, 105);
    path_.moveTo(605.3, 173);
    path_.cubicTo(605.3, 173, 654.7, 173, 654.7, 173);
    path_.moveTo(-355.5, 53);
    path_.cubicTo(-355.5, 53, -330, -15, -330, -15);
    path_.cubicTo(-330, -15, -304.5, 53, -304.5, 53);
    path_.moveTo(-187.4, 231.2);
    path_.cubicTo(-191.9, 226.9, -197.3, 224.3, -205.4, 224.3);
    path_.cubicTo(-222.8, 224.3, -232.6, 239.8, -232.6, 259);
    path_.cubicTo(-232.6, 278.2, -222.8, 293.7, -205.4, 293.7);
    path_.cubicTo(-197.3, 293.7, -191.9, 291.1, -187.4, 286.8);
    path_.moveTo(-349.5, 173);
    path_.cubicTo(-349.5, 173, -349.5, 105, -349.5, 105);
    path_.cubicTo(-349.5, 105, -310.5, 105, -310.5, 105);
    path_.moveTo(-427.1, 105);
    path_.cubicTo(-427.1, 105, -457.9, 145, -457.9, 145);
    path_.moveTo(-472.9, 173);
    path_.cubicTo(-472.9, 173, -472.9, 105, -472.9, 105);
    path_.moveTo(-472.9, 130.1);
    path_.cubicTo(-472.9, 130.1, -429.8, 173, -429.8, 173);
    path_.moveTo(-312.9, 276.8);
    path_.cubicTo(-312.9, 269.1, -318.4, 260.7, -332, 260.7);
    path_.cubicTo(-332, 260.7, -351.1, 260.7, -351.1, 260.7);
    path_.moveTo(-312.9, 276.8);
    path_.cubicTo(-312.9, 284.6, -318.4, 293, -332, 293);
    path_.cubicTo(-332, 293, -351.1, 293, -351.1, 293);
    path_.moveTo(-308.9, 242.8);
    path_.cubicTo(-308.9, 234.3, -314.9, 225, -330, 225);
    path_.cubicTo(-330, 225, -351.1, 225, -351.1, 225);
    path_.moveTo(-308.9, 242.8);
    path_.cubicTo(-308.9, 251.4, -314.9, 260.7, -330, 260.7);
    path_.cubicTo(-330, 260.7, -351.1, 260.7, -351.1, 260.7);
    path_.moveTo(-351.1, 225);
    path_.cubicTo(-351.1, 225, -351.1, 293, -351.1, 293);
    path_.moveTo(-312.9, 276.8);
    path_.cubicTo(-312.9, 269.1, -318.4, 260.7, -332, 260.7);
    path_.cubicTo(-332, 260.7, -351.1, 260.7, -351.1, 260.7);
    path_.moveTo(-312.9, 276.8);
    path_.cubicTo(-312.9, 284.6, -318.4, 293, -332, 293);
    path_.cubicTo(-332, 293, -351.1, 293, -351.1, 293);
    path_.moveTo(-308.9, 242.8);
    path_.cubicTo(-308.9, 234.3, -314.9, 225, -330, 225);
    path_.cubicTo(-330, 225, -351.1, 225, -351.1, 225);
    path_.moveTo(-308.9, 242.8);
    path_.cubicTo(-308.9, 251.4, -314.9, 260.7, -330, 260.7);
    path_.cubicTo(-330, 260.7, -351.1, 260.7, -351.1, 260.7);
    path_.moveTo(-351.1, 225);
    path_.cubicTo(-351.1, 225, -351.1, 293, -351.1, 293);
    path_.moveTo(296.9, 105);
    path_.cubicTo(296.9, 105, 276.3, 122.2, 276.3, 122.2);
    path_.moveTo(270, 173.7);
    path_.cubicTo(252.5, 173.7, 243.1, 158.2, 243.1, 139);
    path_.cubicTo(243.1, 119.8, 252.5, 104.3, 270, 104.3);
    path_.cubicTo(287.5, 104.3, 296.9, 119.8, 296.9, 139);
    path_.cubicTo(296.9, 158.2, 287.5, 173.7, 270, 173.7);
    path_.moveTo(410.6, 156);
    path_.cubicTo(410.6, 164.2, 404.6, 173, 389.5, 173);
    path_.cubicTo(389.5, 173, 368.5, 173, 368.5, 173);
    path_.moveTo(410.6, 156);
    path_.cubicTo(410.6, 147.8, 404.6, 139, 389.5, 139);
    path_.cubicTo(389.5, 139, 368.5, 139, 368.5, 139);
    path_.moveTo(368.5, 173);
    path_.cubicTo(368.5, 173, 368.5, 105, 368.5, 105);
    path_.moveTo(411.5, 105);
    path_.cubicTo(411.5, 105, 401, 130.8, 401, 130.8);
    path_.cubicTo(398.7, 135.7, 395.8, 139, 387.3, 139);
    path_.moveTo(171.1, 155.1);
    path_.cubicTo(171.1, 163.7, 165.1, 173, 150, 173);
    path_.cubicTo(150, 173, 128.9, 173, 128.9, 173);
    path_.moveTo(171.1, 155.1);
    path_.cubicTo(171.1, 146.6, 165.1, 137.3, 150, 137.3);
    path_.cubicTo(150, 137.3, 128.9, 137.3, 128.9, 137.3);
    path_.moveTo(128.9, 173);
    path_.cubicTo(128.9, 173, 128.9, 105, 128.9, 105);
    path_.moveTo(529, 165.3);
    path_.cubicTo(524.4, 170.8, 517.7, 173.8, 509.4, 173.8);
    path_.cubicTo(498.9, 173.8, 491, 167.8, 491, 158.4);
    path_.cubicTo(491, 148.7, 498.4, 144.3, 509.4, 140.1);
    path_.cubicTo(519.5, 136.3, 530.8, 133.4, 530.8, 120.6);
    path_.cubicTo(530.8, 112.2, 524.9, 104.3, 510.5, 104.3);
    path_.cubicTo(502.1, 104.3, 493.4, 108.5, 489.2, 115.2);
    path_.moveTo(30, 173.7);
    path_.cubicTo(12.5, 173.7, 3.1, 158.2, 3.1, 139);
    path_.cubicTo(3.1, 119.8, 12.5, 104.3, 30, 104.3);
    path_.cubicTo(47.5, 104.3, 56.9, 119.8, 56.9, 139);
    path_.cubicTo(56.9, 158.2, 47.5, 173.7, 30, 173.7);
    path_.moveTo(-67.2, 173);
    path_.cubicTo(-67.2, 173, -67.2, 105, -67.2, 105);
    path_.cubicTo(-67.2, 105, -112.8, 173, -112.8, 173);
    path_.cubicTo(-112.8, 173, -112.8, 105, -112.8, 105);
    path_.moveTo(-183.5, 105);
    path_.cubicTo(-183.5, 105, -183.5, 173, -183.5, 173);
    path_.cubicTo(-183.5, 173, -210, 120.2, -210, 120.2);
    path_.cubicTo(-210, 120.2, -236.5, 173, -236.5, 173);
    path_.cubicTo(-236.5, 173, -236.5, 105, -236.5, 105);
    path_.moveTo(651.2, 293);
    path_.cubicTo(651.2, 293, 651.2, 251.3, 651.2, 251.3);
    path_.cubicTo(651.2, 232, 639.3, 224.3, 628.3, 224.3);
    path_.cubicTo(620.9, 224.3, 613.1, 227.7, 608.8, 235.9);
    path_.moveTo(291.1, 285.7);
    path_.cubicTo(286.2, 290.6, 279.6, 293.7, 271.5, 293.7);
    path_.cubicTo(254, 293.7, 243.7, 278.2, 243.7, 259);
    path_.cubicTo(243.7, 239.8, 253.7, 224.3, 271.2, 224.3);
    path_.cubicTo(288.6, 224.3, 296.7, 237.1, 296.3, 256.7);
    path_.cubicTo(296.3, 256.7, 277.5, 256.7, 277.5, 256.7);
    path_.moveTo(-98.9, 293.7);
    path_.cubicTo(-98.9, 293.7, -113.1, 293.7, -113.1, 293.7);
    path_.cubicTo(-113.1, 293.7, -113.1, 224.3, -113.1, 224.3);
    path_.cubicTo(-113.1, 224.3, -98.9, 224.3, -98.9, 224.3);
    path_.cubicTo(-73.6, 224.3, -66.9, 239.8, -66.9, 259);
    path_.cubicTo(-66.9, 278.2, -73.6, 293.7, -98.9, 293.7);
    path_.moveTo(412.8, 225);
    path_.cubicTo(412.8, 225, 412.8, 293, 412.8, 293);
    path_.moveTo(367.2, 293);
    path_.cubicTo(367.2, 293, 367.2, 225, 367.2, 225);
    path_.moveTo(367.2, 259);
    path_.cubicTo(367.2, 259, 412.8, 259, 412.8, 259);
    path_.moveTo(510, 293);
    path_.cubicTo(510, 293, 510, 225, 510, 225);
    path_.moveTo(49.5, 293);
    path_.cubicTo(49.5, 293, 10.5, 293, 10.5, 293);
    path_.cubicTo(10.5, 293, 10.5, 225, 10.5, 225);
    path_.cubicTo(10.5, 225, 49.5, 225, 49.5, 225);
    path_.moveTo(10.5, 259);
    path_.cubicTo(10.5, 259, 43.4, 259, 43.4, 259);
    path_.moveTo(169.5, 293);
    path_.cubicTo(169.5, 293, 130.5, 293, 130.5, 293);
    path_.cubicTo(130.5, 293, 130.5, 225, 130.5, 225);
    path_.moveTo(130.5, 259);
    path_.cubicTo(130.5, 259, 163.4, 259, 163.4, 259);
    path_.moveTo(-468.5, 245.4);
    path_.cubicTo(-468.5, 245.4, -431.5, 245.4, -431.5, 245.4);
    path_.moveTo(-476.5, 225);
    path_.cubicTo(-476.5, 225, -450, 293, -450, 293);
    path_.cubicTo(-450, 293, -423.5, 225, -423.5, 225);
    path_.moveTo(-450, -15.7);
    path_.cubicTo(-439, -15.7, -427.1, -8, -427.1, 11.3);
    path_.cubicTo(-427.1, 11.3, -427.1, 53, -427.1, 53);
    path_.moveTo(-450, -15.7);
    path_.cubicTo(-461, -15.7, -472.9, -8, -472.9, 11.3);
    path_.cubicTo(-472.9, 11.3, -472.9, 53, -472.9, 53);
    path_.moveTo(129.4, 53);
    path_.cubicTo(129.4, 53, 170.6, 53, 170.6, 53);
    path_.cubicTo(170.6, 53, 128.1, -15, 128.1, -15);
    path_.cubicTo(128.1, -15, 171.9, -15, 171.9, -15);
    path_.moveTo(-177.3, 53);
    path_.cubicTo(-177.3, 53, -192.8, -15, -192.8, -15);
    path_.cubicTo(-192.8, -15, -210, 43.2, -210, 43.2);
    path_.cubicTo(-210, 43.2, -227.2, -15, -227.2, -15);
    path_.cubicTo(-227.2, -15, -242.7, 53, -242.7, 53);
    path_.moveTo(5.3, 53);
    path_.cubicTo(5.3, 53, 30, 17.6, 30, 17.6);
    path_.cubicTo(30, 17.6, 54.7, 53, 54.7, 53);
    path_.moveTo(30, 17.6);
    path_.cubicTo(30, 17.6, 30, -15, 30, -15);
    path_.moveTo(-67.1, 53);
    path_.cubicTo(-67.1, 53, -112.9, -15, -112.9, -15);
    path_.moveTo(-112.9, 53);
    path_.cubicTo(-112.9, 53, -67.1, -15, -67.1, -15);

    for (auto& segment : path_) {
      segment.point().y *= -1.0;
      segment.control1().y *= -1.0;
      segment.control2().y *= -1.0;
    }

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
        stroker.set_tolerance(10.0);
        stroker.set_simplifies(true);
        stroke_ = stroker(path_);
        stroker.set_simplifies(false);
        fill_ = stroker(path_);
        needs_stroking_ = false;
      } else {
        stroke_.reset();
      }
    }
  }

  void draw() override {
    gfx::Path path = path_;
    gfx::Path stroke = stroke_;
    gfx::Path fill = fill_;

    for (auto& segment : path) {
      segment.point() *= scale_;
      segment.control1() *= scale_;
      segment.control2() *= scale_;
    }
    for (auto& segment : stroke) {
      segment.point() *= scale_;
      segment.control1() *= scale_;
      segment.control2() *= scale_;
    }
    for (auto& segment : fill) {
      segment.point() *= scale_;
      segment.control1() *= scale_;
      segment.control2() *= scale_;
    }

    nvg::StateGuard save;
    nvg::Translate(translation_);

    if (!stroke.empty()) {
      if (draws_outline_) {
        nvg::BeginPath();
        nvg::Path(fill);
        nvg::FillColor(gfx::Color4f(0.0, 0.1));
        nvg::Fill();
        nvg::BeginPath();
        nvg::Path(stroke);
        nvg::StrokeWidth(1.0);
        nvg::StrokeColor(gfx::Color4f(0.5));
        nvg::Stroke();
        drawControl(stroke);
      } else {
        nvg::BeginPath();
        nvg::Path(fill);
        nvg::FillColor(gfx::Color4f(0.0));
        nvg::Fill();
      }
    }

    if (draws_control_) {
      nvg::BeginPath();
      nvg::Path(path);
      nvg::StrokeWidth(1.0);
      nvg::StrokeColor(gfx::Color4f(0.5));
      nvg::Stroke();
      drawControl(path);
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
    nvg::StrokeColor(gfx::Color4f(0.5, 0.5));
    nvg::Stroke();

    // Control points
    nvg::FillColor(gfx::Color4f(0.5));
    nvg::StrokeColor(gfx::Color4f(0.5));
    for (const auto& segment : path) {
      switch (segment.type()) {
        case gfx::Segment::Type::MOVE:
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.0);
          nvg::Fill();
          break;
        case gfx::Segment::Type::LINE:
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.0);
          nvg::Fill();
          break;
        case gfx::Segment::Type::QUADRATIC:
          nvg::BeginPath();
          nvg::Circle(segment.control(), 3.0);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.0);
          nvg::Fill();
          break;
        case gfx::Segment::Type::CUBIC:
          nvg::BeginPath();
          nvg::Circle(segment.control1(), 3.0);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.control2(), 3.0);
          nvg::Stroke();
          nvg::BeginPath();
          nvg::Circle(segment.point(), 3.0);
          nvg::Fill();
          break;
        default:
          break;
      }
    }
  }

  void mouseDragged() override {
    translation_ += mouse() - pmouse();
  }

  void mousePressed(const app::MouseEvent& event) override {
    if (event.button() == app::MouseButton::RIGHT) {
      if (draws_control_) {
        draws_control_ = false;
        draws_outline_ = true;
      } else if (draws_outline_) {
        draws_control_ = false;
        draws_outline_ = false;
      } else {
        draws_control_ = true;
        draws_outline_ = false;
      }
    }
  }

  void touchesMoved() override {
    translation_ += touch() - ptouch();
  }

  void mouseWheel(const app::MouseEvent& event) override {
    if (event.modifiers() % app::KeyModifier::ALTERNATE) {
      width_ = std::max(0.0, width_ + event.wheel().y / 2.0);
      needs_stroking_ = true;
    } else {
      const auto scale = scale_;
      scale_ = std::max(1.0, scale_ * (event.wheel().y < 0.0 ? 0.8 : 1.25));
      translation_ += ((mouse() - translation_) * scale - (mouse() - translation_) * scale_) / scale;
    }
  }

 private:
  nvg::Context context_;
  math::Vec2d translation_;
  double width_;
  double scale_;
  gfx::Path path_;
  gfx::Path stroke_;
  gfx::Path fill_;
  bool needs_stroking_;
  bool draws_control_;
  bool draws_outline_;
};

int main(int argc, char **argv) {
  return solas::app::Run<App>(argc, argv);
}
