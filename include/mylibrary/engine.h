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
  vector<Card> cards_used;
  vector<Player> players;
  Card played_card;

  const int NUM_PLAYERS = 2;
  const int MAX_HEALTH = 3;
  const int DRAW_CARDS = 1;
  bool start_of_round = true;

 public:
  Engine();
  Player& GetPlayer(int pos);
  Player& GetOpponent(int pos);
  void PlayCard(Card& card);
  void PlayAction();
  void SwitchPlayer();
  void UnableToDodge();
  void EndRound(Card& card);
  void CheckEndGame();

  int current_player = 0;
  bool responding = false;
  bool end_round = false;
  bool too_many_cards = false;
  bool end_game = false;
  bool game_over = false;
  vector<Card> deck;
  Card discard;
};

}

#endif  // FINALPROJECT_ENGINE_H
