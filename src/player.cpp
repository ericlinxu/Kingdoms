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

int Player::GetPosition() {
  return position;
}
}  // namespace mylibrary
