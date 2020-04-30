// Copyright (c) 2020 [Eric Xu]. All rights reserved.

#include <mylibrary/player.h>

namespace mylibrary {

/**
 * Constructor
 * Initializes the player's position in the game, their health, and the
 * maximum amount of cards they can have in their hand at the end of the round
 * @param player_health: amount of health the player has
 * @param pos: position in game
 */
Player::Player(int player_health, int pos) {
  position = pos;
  health = player_health;
  max_cards = player_health;
}

/**
 * Adds a card to the player's hand when the player draws a card
 * @param card: card drawn
 */
void Player::DrawCards(mylibrary::Card& card) {
  hand.push_back(card);
}

/**
 * Checks whether the card that the player wants to play is valid
 * If true:
 *      Card will be played and will be shown in the center of the UI
 *      Card will be removed from the player's hand
 *      Card ability will go through
 * If false:
 *      Nothing will happen
 * @param card: Card that the player wants to play
 * @param responding: Whether or not the game state is in responding
 * @return true/false
 */
bool Player::PlayCard(mylibrary::Card& card, bool responding) {
  if (!responding) {
    if (card.GetName() == "hit") {
      RemoveCard(card);
      return true;
    } else if (card.GetName() == "heal" && health < MAX_HEALTH) {
      RemoveCard(card);
      SetHealth(health + card.GetHealth());
      return true;
    }
  } else {
    if (card.GetName() == "dodge") {
      RemoveCard(card);
      return true;
    }
  }
  return false;
}

/**
 * Removes the card from the player's hand
 * @param card: Card to be removed
 */
void Player::RemoveCard(mylibrary::Card& card) {
  for (auto itr = hand.begin(); itr != hand.end(); ++itr) {
    if (itr->GetName() == card.GetName()) {
      hand.erase(itr);
      break;
    }
  }
}

/**
 * The last hope for the player to continue the game
 * This is called when the player has 0 health
 * If the player plays a "heal" card, the method will return true and the game
 * could continue
 * If not, then game over
 * @param card: Card that the player wants to play
 * @return true/false
 */
bool Player::Save(Card& card) {
  if (card.GetName() == "heal") {
    RemoveCard(card);
    SetHealth( 1);
    return true;
  }
  return false;
}

/**
 * Gets the player's position
 */
int Player::GetPosition() {
  return position;
}

/**
 * Gets player's current health
 */
int Player::GetHealth() {
  return health;
}

/**
 * Gets the maximum amount of cards the player can currently have
 */
int Player::GetMaxCards() {
  return max_cards;
}

/**
 * Sets the player's health to a new value
 * The maximum amount of cards the player can have is the same as the player's
 * health
 * The max cards a player can have at the end of the round is always the same
 * as their health
 * @param new_health: new health to be set to
 */
void Player::SetHealth(int new_health) {
  max_cards = new_health;
  health = new_health;
}

}  // namespace mylibrary
