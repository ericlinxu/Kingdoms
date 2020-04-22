//
// Created by Eric Xu on 4/19/20.
//

#include "mylibrary/card.h"

namespace mylibrary {

Card::Card(int card_health, string& card_name, string& card_match
    , int card_number) {
  health = card_health;
  match = card_match;
  name = card_name;
  number = card_number;
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

string Card::GetNumber() {
  return number;
}
}