// Created by Eric Xu on 4/20/20.

#include <mylibrary/engine.h>
#include <cinder/app/AppBase.h>
#include <mylibrary/file_loader.h>

#include <random>

namespace mylibrary {

/**
 * Constructor
 * Initializes
 *    1. Players in the game
 *    2. The cards that are allowed to be used in the game
 *    3. Creates the deck
 *    4. Starting hand for each player
 */
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

/**
 * Generates the deck with the cards given from the json file
 */
void Engine::CreateDeck() {
  for (Card card : cards_used) {
    for (int j = 0; j < card.GetNumber(); j++) {
      deck.push_back(card);
    }
  }
  std::shuffle(deck.begin(), deck.end()
      , std::mt19937(std::random_device()()));
}

/**
 * Gives each player their starting hand
 */
void Engine::DistributeCards() {
  for (Player& player : players) {
    for (int i = 0; i < MAX_HEALTH; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }
  }
}

/**
 * Main Gameplay function
 * Reacts to player actions that are sent in from the my_app
 * Called constantly by Update() in my_app.cc
 */
void Engine::PlayAction() {
  Player& player = GetPlayer(current_player);
  Player& opponent = GetOpponent(current_player);

  //Checks if deck needs to be re-created
  if (deck.empty()) {
    CreateDeck();
  }

  //Checks whether player needs to draw cards at the start of the round
  if (start_of_round) {
    start_of_round = false;
    for (int i = 0; i < DRAW_CARDS; i++) {
      player.DrawCards(deck[0]);
      deck.erase(deck.begin());
    }
  }

  //Main functionality for when players choose cards to play
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

/**
 * Gets the played card from the my_app when user clicks on a card
 * @param card: card played
 */
void Engine::PlayCard(Card& card) {
  played_card = card;
}

/**
 * Checks whether current player has too many cards
 * in hand when ending their round
 * If the player has more card than current health, then they are required to
 * discard x amount of cards
 * @param card: card being discarded
 */
void Engine::EndRound(Card& card) {
  Player& player = GetPlayer(current_player);
  player.RemoveCard(card);
  if (player.hand.size() <= player.GetMaxCards()) {
    too_many_cards = false;
    end_round = false;
    SwitchPlayer();
  }
}

/**
 * Switches player turns when current player decides to end their round
 */
void Engine::SwitchPlayer() {
  start_of_round = true;
  discard.reset();
  if (current_player == 0) {
    current_player = 1;
  } else {
    current_player = 0;
  }
}

/**
 * Called when a player tries to "hit" their opponent and their opponent does
 * not have "dodge"
 */
void Engine::UnableToDodge() {
  Player& opponent = GetOpponent(current_player);
  responding = false;
  opponent.SetHealth(opponent.GetHealth() + discard.GetHealth());
  discard.reset();
}

/**
 * Checks whether the whole game is about to end
 * The only way for a game to end is:
 *        1. The player has 0 health
 *        2. The player does not have a "heal" card to heal back up
 */
void Engine::CheckEndGame() {
  for (Player& player : players) {
    if (player.GetHealth() == 0) {
      end_game = true;
      current_player = player.GetPosition();
      return;
    }
  }
}

/**
 * Called when a player has 0 health
 * This is the player's last chance to not lose
 * The player is allowed to play only the "heal" card
 * If not, then game over
 */
void Engine::Save() {
  if (GetPlayer(current_player).Save(played_card)) {
    discard = played_card;
    played_card.reset();
    current_player = GetOpponent(current_player).GetPosition();
    end_game = false;
  }
}

/**
 * Gets reference to the current player
 */
Player& Engine::GetPlayer(int pos) {
  return players[pos];
}

/**
 * Gets reference to the opposing player
 */
Player& Engine::GetOpponent(int pos) {
  if (pos == 0) {
    return players[1];
  }
  return players[0];
}

/**
 * Gets the deck's current size
 */
int Engine::GetDeckSize() {
  return deck.size();
}

}