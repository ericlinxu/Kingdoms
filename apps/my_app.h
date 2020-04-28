// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Context.h>
#include <mylibrary/engine.h>
#include <cinder/ImageIo.h>
#include <cinder/gl/gl.h>

namespace myapp {

class MyApp : public cinder::app::App {

 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:

  void DrawBackground() const;
  void DrawCurrentPlayer();
  void DrawOpponent();
  void DrawGeneralInfo();

  const int num_players = 2;
  mylibrary::Engine engine;
  cinder::gl::Texture2dRef background = cinder::gl::Texture2d::create(
      loadImage( loadAsset("background.png")));
  cinder::gl::Texture2dRef health = cinder::gl::Texture2d::create(
      loadImage( loadAsset("health.png")));
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
