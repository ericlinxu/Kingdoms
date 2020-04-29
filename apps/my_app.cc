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

void MyApp::update() {
  engine.PlayAction();
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  DrawCurrentPlayer(engine.GetPlayer(engine.current_player));
  DrawOpponent();
  DrawPlayedCard();
  DrawGeneralInfo();
  DrawBackground();
}

void MyApp::keyDown(KeyEvent event) {}

void MyApp::mouseDown(MouseEvent event) {
  mylibrary::Player current_player = engine.GetPlayer(engine.current_player);
  if (event.isLeftDown()) {
    for (int i = 0; i < current_player.hand.size(); i++) {
      if (event.getX() >= bounds[i][0] &&
          event.getY() >= bounds[i][1] &&
          event.getX() <= bounds[i][2] &&
          event.getY() <= bounds[i][3]) {
        engine.PlayCard(current_player.hand[i]);
      }
    }
  } else {
    return;
  }
}

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

void myapp::MyApp::DrawCurrentPlayer(mylibrary::Player& current) {
  //Cards to show
  cinder::vec2 location = {460, 650};
  std::vector<int> coords;
  for (int i = 0; i < current.hand.size(); i++) {
    cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(
      loadImage( loadAsset(current.hand[i].GetImage())));
    cinder::gl::draw(image, location);

    //Get image coordinates
    coords.clear();
    coords.push_back(location.x);
    coords.push_back(location.y);
    coords.push_back(location.x + image->getSize().x);
    coords.push_back(location.y + image->getSize().y);
    GenerateBounds(coords);

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
  mylibrary::Player opponent = engine.GetOpponent(engine.current_player);
  Color color = {1, 1, 1};
  cinder::ivec2 size = {130, 70};
  cinder::vec2 loc = {680, 80};
  PrintText("Opponent\nHealth: " + std::to_string(opponent.GetHealth())
    + "\n# of Cards: " + std::to_string(opponent.hand.size())
    , color, size, loc);
}

void myapp::MyApp::DrawPlayedCard() {
  if (engine.discard.GetName().empty()) {
    Color color = {1, 1, 1};
    cinder::ivec2 size = {190, 24};
    PrintText("No Cards Played", color, size, getWindowCenter());
  } else {
    cinder::ivec2 location = {350, 300};
    cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(
        loadImage( loadAsset(engine.discard.GetImage())));
    cinder::gl::draw(image, location);

    Color color = {1, 1, 1};
    cinder::ivec2 size = {130, 24};
    location = {400, 270};
    PrintText("Played Card", color, size, location);
  }
}

void myapp::MyApp::DrawGeneralInfo() {
  cinder::vec2 location = {350, 30};
  cinder::gl::draw(end, location);
}

/**
 * Gets the bounds of each of the cards the player has on the UI
 * Coords put the bounds of an image into a vector in the form of [a, b, c, d]
 *
 *            (a,b)P++++++++     P stands for Point
 *                 +       +
 *                 +       +
 *                 ++++++++P(c,d)
 *
 * @param coords: vector of coordinates for the current image
 *
 * @note This is mostly used for the MouseDown(Event) method to locate whether
 *       or not the user is pressing on the image
 */
void myapp::MyApp::GenerateBounds(std::vector<int>& coords) {
  bounds.push_back(coords);
}
}