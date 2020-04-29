// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/player.h>

namespace mylibrary {

Player::Player(int player_health, int pos) {
  position = pos;
  health = player_health;
  max_cards = player_health;
}

void Player::DrawCards(mylibrary::Card& card) {
  hand.push_back(card);
}

bool Player::PlayCard(mylibrary::Card& card, bool responding) {
  if (!responding) {
    if (card.GetName() == "hit") {
      RemoveCard(card);
      return true;
    } else if (card.GetName() == "heal" && health < MAX_HEALTH) {
      RemoveCard(card);
      health += card.GetHealth();
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

void Player::RemoveCard(mylibrary::Card& card) {
  for (auto itr = hand.begin(); itr != hand.end(); ++itr) {
    if (itr->GetName() == card.GetName()) {
      hand.erase(itr);
      break;
    }
  }
}

bool Player::Save(Card& card) {
  if (card.GetName() == "heal") {
    RemoveCard(card);
    SetHealth( 1);
    return true;
  }
  return false;
}

int Player::GetPosition() {
  return position;
}

int Player::GetHealth() {
  return health;
}

int Player::GetMaxCards() {
  return max_cards;
}

void Player::SetHealth(int new_health) {
  max_cards = new_health;
  health = new_health;
}
}  // namespace mylibrary
