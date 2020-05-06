// Created by Eric Xu on 4/20/20.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "card.h"
#include "player.h"

#include <vector>

using std::vector;

namespace mylibrary {

class Engine {

 private:
  void CreateDeck();
  void DistributeCards();

  //Cards that are allowed to be used in the game
  vector<Card> cards_used;
  //Players in the game
  vector<Player> players;
  //Card that is currently being played
  Card played_card;
  //Deck of cards
  vector<Card> deck;

  //Total number of players in the game
  const int NUM_PLAYERS = 2;
  //Highest amount of health each player can have
  const int MAX_HEALTH = 3;
  //Number of cards each player draws at the beginning of their rounds
  const int DRAW_CARDS = 1;
  //Indicates whether it is the start of the player's round
  bool start_of_round = true;

 public:
  Engine();
  void PlayCard(Card& card);
  void PlayAction();
  void SwitchPlayer();
  void UnableToDodge();
  void EndRound(Card& card);
  void CheckEndGame();
  void Save();

  Player& GetPlayer(int pos);
  Player& GetOpponent(int pos);
  int GetDeckSize();
  vector<Card> GetCardsUsed();
  Card GetPlayedCard();

  //Indicates whether the current state of game is for the opponent to respond
  //to the current player
  bool responding = false;
  //Position of the current player
  int current_player = 0;
  //Indicates whether the current player wants to end their round
  bool end_round = false;
  //Indicates if the player has to discard some of their cards
  bool too_many_cards = false;
  //Indicates whether the game is about to end
  bool end_game = false;

  //The Card that has been played previously
  Card discard;
};

}

#endif  // FINALPROJECT_ENGINE_H
