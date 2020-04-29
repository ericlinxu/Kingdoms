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

void Engine::PlayAction() {
  Player& player = GetPlayer(current_player);
  Player& opponent = GetOpponent(current_player);

  //Checks whether player needs to draw cards at the start of the round
  if (start_of_round) {
    start_of_round = false;
    for (int i = 0; i < DRAW_CARDS; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }
  }

  if (responding) {
    if (opponent.PlayCard(played_card, responding)) {
      responding = false;
      discard = played_card;
      played_card.reset();
    }
  } else {
    if (player.PlayCard(played_card, responding)) {
      discard = played_card;
      played_card.reset();
      if (discard.GetName() == "hit") {
        responding = true;
      } else {
        responding = false;
      }
    } else {
      played_card.reset();
    }
  }
}

void Engine::PlayCard(Card& card) {
  played_card = card;
}

void Engine::EndRound(Card& card) {
  Player& player = GetPlayer(current_player);
  player.RemoveCard(card);
  if (player.hand.size() <= player.GetMaxCards()) {
    too_many_cards = false;
    end_round = false;
    SwitchPlayer();
  }
}

void Engine::SwitchPlayer() {
  start_of_round = true;
  discard.reset();
  if (current_player == 0) {
    current_player = 1;
  } else {
    current_player = 0;
  }
}

void Engine::UnableToDodge() {
  Player& opponent = GetOpponent(current_player);
  responding = false;
  opponent.SetHealth(opponent.GetHealth() + discard.GetHealth());
  discard.reset();
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