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
  vector<mylibrary::Player> players;
  //mylibrary::Card played_card;


  const int NUM_PLAYERS = 2;
  const int MAX_HEALTH = 3;
  const int DRAW_CARDS = 1;

 public:
  Engine();
  mylibrary::Player& GetPlayer(int pos);
  int current_player = 0;
  vector<mylibrary::Card> deck;
};

}

#endif  // FINALPROJECT_ENGINE_H
