// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

#include "card.h"
namespace mylibrary {

class Player {
 private:
  int health, max_cards, position;
  int MAX_HEALTH = 3;

 public:
  Player(int player_health, int position);
  void DrawCards(mylibrary::Card& card);
  bool PlayCard(mylibrary::Card& card, bool responding);
  void RemoveCard(mylibrary::Card& card);
  bool Save(Card& card);

  int GetPosition();
  int GetHealth();
  int GetMaxCards();
  void SetHealth(int new_health);


  std::vector<mylibrary::Card> hand;
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
