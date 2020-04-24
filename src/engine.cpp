//
// Created by Eric Xu on 4/20/20.
//

#include "mylibrary/engine.h"
#include <mylibrary/file_loader.h>

#include <random>

namespace mylibrary {

Engine::Engine() {
  for (int i = 0; i < NUM_PLAYERS; i++) {
    mylibrary::Player player(MAX_HEALTH);
    players.push_back(player);
  }
  cards_used = mylibrary::LoadCards("resources/cards.json");

  //Setup
  CreateDeck();
  DistributeCards();

  //Start Game
  PlayRounds();
}

void Engine::CreateDeck() {
  for (mylibrary::Card card : cards_used) {
    for (int j = 0; j < card.GetNumber(); j++) {
      deck.push_back(card);
    }
  }
  std::shuffle(deck.begin(), deck.end()
      , std::mt19937(std::random_device()()));
}

void Engine::DistributeCards() {
  for (mylibrary::Player player : players) {
    std::vector<mylibrary::Card> hand;
    for (int i = 0; i < MAX_HEALTH; i++) {
      hand.push_back(deck[0]);
      deck.erase(deck.begin());
    }
    player.ReceiveHand(hand);
  }
}

void Engine::PlayRounds() {
  for (mylibrary::Player player : players) {

    //Each player draws specific amount of cards at the beginning of their round
    //Amount of cards drawn can be changed in the header file
    for (int i = 0; i < DRAW_CARDS; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }

  }
}

}