//
// Created by Eric Xu on 4/19/20.
//

#include "mylibrary/card.h"

namespace mylibrary {

Card::Card(int card_health, string& card_name, string& card_match
    , int card_number, string& image_path) {
  health = card_health;
  match = card_match;
  name = card_name;
  number = card_number;
  image = image_path;
}

Card::Card() {
  health = 0;
  number = 0;
  name = "";
  match = "";
  image = "";
}

void Card::reset() {
  Card();
}

int Card::GetHealth() {
  return health;
}

string Card::GetName() {
  return name;
}

string Card::GetMatch() {
  return match;
}

int Card::GetNumber() {
  return number;
}

string Card::GetImage() {
  return image;
}
}