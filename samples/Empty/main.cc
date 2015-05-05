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

#include "solas/app.h"

#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/Vector.h"

class App : public solas::app::View {
 public:
  void setup() override;
  void update() override;
  void draw() override;
  void mouseMoved() override;
  void mouseDragged() override;

 private:
  ci::CameraPersp camera_;
  ci::Vec2f mouse_;
  bool diffuse_;
  bool ambient_;
  bool specular_;
  bool emissive_;
  float directional_;

  static const GLfloat no_material_[];
  static const GLfloat material_ambient_[];
  static const GLfloat material_diffuse_[];
  static const GLfloat material_specular_[];
  static const GLfloat material_emission_[];
  static const GLfloat material_shininess_[];
  static const GLfloat no_shininess_[];
};

const GLfloat App::no_material_[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat App::material_ambient_[] = { 0.6, 0.3, 0.4, 1.0 };
const GLfloat App::material_diffuse_[] = { 0.3, 0.5, 0.8, 1.0 };
const GLfloat App::material_specular_[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat App::material_emission_[] = { 0.0, 0.1, 0.3, 0.0 };
const GLfloat App::material_shininess_[] = { 128.0 };
const GLfloat App::no_shininess_[] = { 0.0 };

void App::setup() {
  diffuse_ = true;
  ambient_ = false;
  specular_ = false;
  emissive_ = false;
  directional_ = 1.0;
  glClearColor(0.0, 0.0, 0.0, 1.0);
  ci::gl::enableDepthWrite();
  ci::gl::enableDepthRead();
  ci::gl::enableAlphaBlending();
  glDisable(GL_TEXTURE_2D);
}

void App::update() {
  if (mouse_pressed()) {
    directional_ -= (directional_ - 0.00001) * 0.1;
  } else {
    directional_ -= (directional_ - 1.0) * 0.1;
  }
}

void App::draw() {
  camera_.lookAt(ci::Vec3f(0.0, 0.0, 750.0), ci::Vec3f::zero());
  camera_.setPerspective(60.0, width() / height(), 1.0, 1000.0);
  ci::gl::setMatrices(camera_);

  const float sphere_spacing = 75.0;
  const float sphere_radius = 35.0;
  const int sphere_detail = 64;
  const int sphere_columns = 9;
  const int sphere_rows = 5;

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GLfloat light_position[] = { mouse_.x, mouse_.y, 75.0, directional_ };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  for (int x = 0; x < sphere_columns; ++x) {
    const float relative_x = static_cast<float>(x) / (sphere_columns - 1);
    for (int y = 0; y < sphere_rows; ++y) {
      const float relative_y = static_cast<float>(y) / (sphere_rows - 1);

      const float xp = sphere_spacing * (x - (sphere_columns - 1) / 2.0);
      const float yp = sphere_spacing * (y - (sphere_rows - 1) / 2.0);

      glPushMatrix();
      glTranslatef(xp, yp, 0.0);

      if (diffuse_) {
        ci::ColorA color(ci::CM_HSV, relative_x, relative_y, 1.0, 1.0);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
      } else {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_material_);
      }
      if (ambient_) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_);
      } else {
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_material_);
      }
      if (specular_) {
        glMaterialfv( GL_FRONT, GL_SPECULAR, material_specular_ );
        glMaterialfv( GL_FRONT, GL_SHININESS, material_shininess_ );
      } else {
        glMaterialfv( GL_FRONT, GL_SPECULAR, no_material_ );
        glMaterialfv( GL_FRONT, GL_SHININESS, no_shininess_ );
      }
      if (emissive_) {
        glMaterialfv(GL_FRONT, GL_EMISSION, material_emission_);
      } else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material_);
      }

      ci::gl::drawSphere(ci::Vec3f::zero(), sphere_radius, sphere_detail);
      glPopMatrix();
    }
  }
}

void App::mouseMoved() {
  mouse_.x = mouse().x - width() / 2.0;
  mouse_.y = height() / 2.0 - mouse().y;
}

void App::mouseDragged() {
  mouseMoved();
}

int main(int argc, char **argv) {
  return solas::app::Run<App>(argc, argv);
}
