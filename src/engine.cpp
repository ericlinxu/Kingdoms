//
// Created by Eric Xu on 4/20/20.
//

#include "mylibrary/engine.h"

#include <cinder/app/AppBase.h>
#include <mylibrary/file_loader.h>

#include <random>

namespace mylibrary {

Engine::Engine() {
  for (int i = 0; i < NUM_PLAYERS; i++) {
    mylibrary::Player player(MAX_HEALTH, i);
    players.push_back(player);
  }
  cards_used = mylibrary::LoadCards(
      cinder::app::getAssetPath("cards/cards.json").string());

  //Setup
  CreateDeck();
  DistributeCards();

  //Start Game
  //PlayRounds();
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
  for (mylibrary::Player& player : players) {
    for (int i = 0; i < MAX_HEALTH; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }
  }
}

void Engine::PlayRounds() {
  for (mylibrary::Player& player : players) {
    current_player = player.GetPosition();
    //Each player draws specific amount of cards at the beginning of their round
    //Amount of cards drawn can be changed in the header file
    for (int i = 0; i < DRAW_CARDS; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }

  }
}

mylibrary::Player& Engine::GetPlayer(int pos) {
  return players[pos];
}

}