//
// Created by Eric Xu on 4/19/20.
//

#include "mylibrary/card.h"

namespace mylibrary {

Card::Card(int card_health, string& card_name, string& card_match) {
  health = card_health;
  match = card_match;
  name = card_name;
}

}