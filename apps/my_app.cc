// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;

MyApp::MyApp() : engine{} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  DrawBackground();
}

void MyApp::keyDown(KeyEvent event) {}

void MyApp::mouseDown(MouseEvent event) {}

void myapp::MyApp::DrawBackground() const {
  cinder::gl::color(cinder::Colorf::white());
  cinder::gl::draw(background);
}

void myapp::MyApp::DrawPlayer() {
  mylibrary::Player current = engine.GetCurrPlayer();
  for (int i = 0; i < current.hand.size(); i++) {

  }
}

}