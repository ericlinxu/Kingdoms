// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

#include "card.h"
namespace mylibrary {

class Player {
 private:
  int health, max_cards;
  std::vector<mylibrary::Card> hand;

 public:
  Player(int player_health);
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
