// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Context.h>
#include <mylibrary/engine.h>
#include <cinder/ImageIo.h>
#include <cinder/gl/gl.h>

#include <nlohmann/json.hpp>

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
  void DrawCurrentPlayer(mylibrary::Player& current);
  void DrawOpponent();
  void DrawPlayedCard();
  void DrawTurn(int position);
  void DrawTooManyCardsNote(bool run);
  void DrawGeneralInfo();
  void GenerateBounds(std::vector<int>& coords);

  const int num_players = 2;
  mylibrary::Engine engine;
  std::vector<std::vector<int>> bounds;
  cinder::gl::Texture2dRef background = cinder::gl::Texture2d::create(
      loadImage( loadAsset("background.png")));
  cinder::gl::Texture2dRef health = cinder::gl::Texture2d::create(
      loadImage( loadAsset("health.png")));
  cinder::gl::Texture2dRef end = cinder::gl::Texture2d::create(
      loadImage( loadAsset("end.png")));
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
