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
    Player player(MAX_HEALTH, i);
    players.push_back(player);
  }
  cards_used = LoadCards(
      cinder::app::getAssetPath("cards/cards.json").string());

  //Setup
  CreateDeck();
  DistributeCards();

  //Start Game
  //PlayRounds();
}

void Engine::CreateDeck() {
  for (Card card : cards_used) {
    for (int j = 0; j < card.GetNumber(); j++) {
      deck.push_back(card);
    }
  }
  std::shuffle(deck.begin(), deck.end()
      , std::mt19937(std::random_device()()));
}

void Engine::DistributeCards() {
  for (Player& player : players) {
    for (int i = 0; i < MAX_HEALTH; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }
  }
}

void Engine::PlayRounds() {
  if (deck.empty()) {
    CreateDeck();
  }

  for (Player& player : players) {
    current_player = player.GetPosition();
    //Each player draws specific amount of cards at the beginning of their round
    //Amount of cards drawn can be changed in the header file
    for (int i = 0; i < DRAW_CARDS; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }

    responding = false;
  }
  //PlayRounds();
}

void Engine::PlayAction() {
  Player player = GetPlayer(previous_player);
  if (player.PlayCard(played_card, responding)) {
    discard = played_card;
    if (discard.GetName() == "hit") {
      Dodge();
      responding = false;
    }
  } else {
    played_card.reset();
  }
}

void Engine::Dodge() {
  responding = true;
  current_player = GetOpponent(previous_player).GetPosition();
  Player player = GetPlayer(current_player);
  if (player.PlayCard(played_card, responding)) {
    discard = played_card;
    played_card.reset();
  }
}

void Engine::PlayCard(Card& card) {
  played_card = card;
}

void Engine::CheckEndGame() {

}

Player& Engine::GetPlayer(int pos) {
  return players[pos];
}

Player& Engine::GetOpponent(int pos) {
  if (pos == 0) {
    return players[1];
  }
  return players[0];
}


}