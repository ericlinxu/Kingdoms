// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

#include "card.h"
namespace mylibrary {

class Player {
 private:
  int health, max_cards, position;


 public:
  Player(int player_health, int position);
  void ReceiveHand(std::vector<mylibrary::Card>& cards);
  void DrawCards(mylibrary::Card& card);
  int GetPosition();

  std::vector<mylibrary::Card> hand;

};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
