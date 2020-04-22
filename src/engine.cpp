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
  Setup();
}

void Engine::Setup() {
  CreateDeck();
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

}