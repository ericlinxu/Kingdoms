// Copyright (c) 2020 [Eric Xu]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

#include "card.h"
namespace mylibrary {

class Player {
 private:
  //Current health
  int health;
  //Maximum amount of cards player can currently have
  int max_cards;
  //Player's position in the game
  int position;
  //Player's maximum allowed health
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

  //Player's current hand
  std::vector<mylibrary::Card> hand;
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
