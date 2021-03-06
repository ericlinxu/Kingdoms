// Copyright (c) 2020 [Eric Xu]. All rights reserved.

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
  if (engine.end_game) {
    engine.Save();
  } else {
    engine.PlayAction();
    engine.CheckEndGame();
  }
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();

  if (game_over) {
    DrawGameOver();
    return;
  }

  if (engine.responding) {
    mylibrary::Player opponent = engine.GetOpponent(engine.current_player);
    DrawCurrentPlayer(opponent);
    DrawTurn(opponent.GetPosition() + 1);
  } else {
    DrawCurrentPlayer(engine.GetPlayer(engine.current_player));
    DrawTurn(engine.current_player + 1);
  }
  DrawOpponent();

  if (!engine.end_game) {
    DrawTooManyCardsNote(engine.too_many_cards);
  }

  DrawPlayedCard();
  DrawGeneralInfo();
  DrawBackground();
}

/**
 * Detects when the mouse key is pressed
 * For my method, only the left mouse key will be used to detect actions for
 * pressing the cards and end round button
 * @param event
 */
void MyApp::mouseDown(MouseEvent event) {
  mylibrary::Player current_player = engine.GetPlayer(engine.current_player);
  if (engine.responding) {
    current_player = engine.GetOpponent(engine.current_player);
  }
  if (event.isLeftDown()) {
    for (int i = 0; i < current_player.hand.size(); i++) {
      if (event.getX() >= bounds[i][0] && event.getY() >= bounds[i][1] &&
          event.getX() <= bounds[i][2] && event.getY() <= bounds[i][3]) {
        if (engine.end_round) {
          engine.EndRound(current_player.hand[i]);
        } else if (engine.discard.GetName() == "hit" &&
                   current_player.hand[i].GetName() != "dodge") {
          return;
        } else {
          engine.PlayCard(current_player.hand[i]);
        }
      }
    }

    //Coordinates for the End button
    if (event.getX() >= 340 && event.getY() >= 30 && event.getY() <= 130
        && event.getX() <= 440) {
      if (engine.end_game) {
        game_over = true;
      } else if (engine.discard.GetName() != "hit") {
        if (current_player.hand.size() > current_player.GetMaxCards()) {
          engine.end_round = true;
          engine.too_many_cards = true;
        } else {
          engine.SwitchPlayer();
        }
      } else {
        engine.UnableToDodge();
      }
    }
  }
}

/**
 * Taken from Snake
 * Prints Text out in a standard from
 * @param text: Text to draw out
 * @param color: Color of text
 * @param size: size of the text box
 * @param loc: location of the text
 */
template <typename C>
void PrintText(const string& text, const C& text_color, const cinder::ivec2& size,
               const cinder::vec2& loc, const C& background_color) {
  cinder::gl::color(cinder::Colorf::white());

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Arial", 20))
      .size(size)
      .color(text_color)
      .backgroundColor(background_color)
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

/**
 * Draws the background while playing game
 */
void myapp::MyApp::DrawBackground() const {
  cinder::gl::color(cinder::Colorf::white());
  cinder::gl::draw(background);
}

/**
 * Draws the information for the current player
 * @param current: Current Player
 */
void myapp::MyApp::DrawCurrentPlayer(mylibrary::Player& current) {
  //Cards to show
  cinder::vec2 location = {450, 650};
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

  Color text_color = {1, 1, 1};
  cinder::ivec2 size = {100, 24};
  cinder::vec2 loc = {390, 630};
  Color background_color = {0.54,0.25,0.16};
  PrintText("My Cards", text_color, size, loc, background_color);

  //Health to show
  location = {440, 560};
  for (int i = 0; i < current.GetHealth(); i++) {
    cinder::gl::draw(health, location);
    location = {location.x - 70, location.y};
  }

  text_color = {1, 1, 1};
  background_color = {0.29,0.14,0.10};
  size = {100, 24};
  loc = {390, 530};
  PrintText("My Health", text_color, size, loc, background_color);
}

/**
 * Draws the text for which player's turn it is
 * @param position: either player 1 or 2
 */
void myapp::MyApp::DrawTurn(int position) {
  Color text_color = {1, 1, 1};
  Color background_color = {0.29,0.14,0.10};
  cinder::vec2 size = {150, 24};
  cinder::vec2 loc = {100, 580};
  PrintText("Player " + std::to_string(position) + "'s Turn"
      , text_color, size, loc, background_color);
}

/**
 * Draws the information for the opponent of the current player
 */
void myapp::MyApp::DrawOpponent() {
  mylibrary::Player opponent = engine.GetOpponent(engine.current_player);
  Color text_color = {1, 1, 1};
  Color background_color = {0.84,0.69,0.44};
  cinder::ivec2 size = {130, 70};
  cinder::vec2 loc = {670, 80};
  PrintText("Opponent\nHealth: " + std::to_string(opponent.GetHealth())
    + "\n# of Cards: " + std::to_string(opponent.hand.size())
    , text_color, size, loc, background_color);
}

/**
 * Draws the card that was played by the current player in the center of the UI
 */
void myapp::MyApp::DrawPlayedCard() {
  Color text_color = {0, 0, 0};
  Color background_color = {0.94,0.91,0.83};

  if (engine.discard.GetName().empty()) {
    cinder::ivec2 size = {170, 24};
    cinder::ivec2 location = {390, 350};
    PrintText("No Cards Played", text_color, size
        , location, background_color);
  } else {
    cinder::ivec2 location = {340, 300};
    cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(
        loadImage( loadAsset(engine.discard.GetImage())));
    cinder::gl::draw(image, location);

    cinder::ivec2 size = {130, 24};
    location = {390, 270};
    PrintText("Played Card", text_color, size, location, background_color);
  }
}

/**
 * Draws the text for the amount of cards the player needs to discard at the
 * end of the round
 * @param run: bool stating whether or not the player has too many cards
 */
void myapp::MyApp::DrawTooManyCardsNote(bool run) {
  if (run) {
    mylibrary::Player& player = engine.GetPlayer(engine.current_player);
    Color text_color = {1, 0, 0};
    Color background_color = {0.47,0,0};
    cinder::ivec2 size = {230, 24};
    cinder::ivec2 location = {390, 400};
    PrintText("Please discard " + std::to_string(player.hand.size()
              - player.GetMaxCards()) + " card(s)", text_color, size, location
                  , background_color);
  }
}

/**
 * Draws general information for the whole game
 */
void myapp::MyApp::DrawGeneralInfo() {
  cinder::vec2 location = {340, 30};
  cinder::gl::draw(end, location);

  Color text_color = {1, 1, 1};
  Color background_color = {0.72,0.51,0.32};
  cinder::ivec2 size = {170, 24};
  location = {120, 80};
  PrintText("Cards in Deck: " + std::to_string(engine.GetDeckSize())
            , text_color, size, location, background_color);
}

/**
 * Draws the Game Over screen after a player wins the game
 */
void myapp::MyApp::DrawGameOver() {
  Color text_color = {1, 1, 1};
  Color background_color = {0.76,0.62,0.52};
  cinder::ivec2 size = {160, 48};
  PrintText("Player " + std::to_string(engine.current_player)
            + " Won!!!!\nGame Over!!!!", text_color, size
            , getWindowCenter(), background_color);

  cinder::gl::color(cinder::Colorf::white());
  cinder::gl::draw(ending_screen);
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