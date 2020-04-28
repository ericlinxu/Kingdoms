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
  void DrawPlayer();

  const int num_players = 2;
  mylibrary::Engine engine;
  cinder::gl::Texture2dRef background = cinder::gl::Texture2d::create(
      loadImage( loadAsset("background.jpeg")));
  cinder::gl::Texture2dRef hit = cinder::gl::Texture2d::create(
      loadImage( loadAsset("hit.png")));
  cinder::gl::Texture2dRef dodge = cinder::gl::Texture2d::create(
      loadImage( loadAsset("dodge.png")));
  cinder::gl::Texture2dRef heal = cinder::gl::Texture2d::create(
      loadImage( loadAsset("heal.png")));
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
