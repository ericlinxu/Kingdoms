// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/player.h>

namespace mylibrary {

Player::Player(int player_health, int pos) {
  position = pos;
  health = player_health;
  max_cards = player_health;
}

void Player::ReceiveHand(std::vector<mylibrary::Card>& cards) {
  hand = cards;
}

void Player::DrawCards(mylibrary::Card& card) {
  hand.push_back(card);
}

bool Player::PlayCard(mylibrary::Card& card, bool responding) {
  if (responding) {
    if (card.GetName() == "hit") {
      RemoveCard(card);
      return true;
    } else if (card.GetName() == "heal" && health < MAX_HEALTH) {
      RemoveCard(card);
      health += card.GetHealth();
      return true;
    }
  } else {
    if (card.GetName() == "heal" && health == 0) {
      RemoveCard(card);
      health += card.GetHealth();
      return true;
    } else if (card.GetName() == "dodge") {
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

int Player::GetPosition() {
  return position;
}

int Player::GetHealth() {
  return health;
}
}  // namespace mylibrary
