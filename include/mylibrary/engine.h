//
// Created by Eric Xu on 4/20/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>

#include "card.h"
#include "player.h"

using std::vector;

namespace mylibrary {

class Engine {

 private:
  void CreateDeck();
  void DistributeCards();
  void PlayRounds();
  vector<mylibrary::Card> cards_used;
  vector<mylibrary::Card> deck;
  vector<mylibrary::Player> players;
  //mylibrary::Card played_card;

  const int NUM_PLAYERS = 2;
  const int MAX_HEALTH = 3;
  const int DRAW_CARDS = 1;

 public:
  Engine();
};

}

#endif  // FINALPROJECT_ENGINE_H
