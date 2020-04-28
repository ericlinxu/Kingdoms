// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include <cinder/Font.h>
#include <cinder/Text.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;
using cinder::TextBox;
using cinder::ColorA;
using cinder::Color;


MyApp::MyApp() : engine{} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  DrawCurrentPlayer();
  DrawOpponent();
  DrawBackground();
}

void MyApp::keyDown(KeyEvent event) {}

void MyApp::mouseDown(MouseEvent event) {}

//Taken from Snake
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Arial", 20))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0.502, 0.502, 0.502, 1))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void myapp::MyApp::DrawBackground() const {
  cinder::gl::color(cinder::Colorf::white());
  cinder::gl::draw(background);
}

void myapp::MyApp::DrawCurrentPlayer() {
  mylibrary::Player current = engine.GetPlayer(engine.current_player);

  //Cards to show
  cinder::vec2 location = {460, 650};
  for (mylibrary::Card card : current.hand) {
    cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(
      loadImage( loadAsset(card.GetImage())));
    cinder::gl::draw(image, location);
    location = {location.x - 110, location.y};
  }

  Color color = {1, 1, 1};
  cinder::ivec2 size = {100, 24};
  cinder::vec2 loc = {400, 630};
  PrintText("My Cards", color, size, loc);

  //Health to show
  location = {450, 560};
  for (int i = 0; i < current.GetHealth(); i++) {
    cinder::gl::draw(health, location);
    location = {location.x - 70, location.y};
  }

  color = {1, 1, 1};
  size = {100, 24};
  loc = {400, 530};
  PrintText("My Health", color, size, loc);
}

void myapp::MyApp::DrawOpponent() {
  mylibrary::Player opponent = engine.GetPlayer(0);
  if (engine.current_player == 0) {
    opponent = engine.GetPlayer(1);
  }

  Color color = {1, 1, 1};
  cinder::ivec2 size = {130, 70};
  cinder::vec2 loc = {680, 80};
  PrintText("Opponent\nHealth: " + std::to_string(opponent.GetHealth())
    + "\n# of Cards: " + std::to_string(opponent.hand.size())
    , color, size, loc);
}

void myapp::MyApp::DrawGeneralInfo() {

}
}