// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/player.h>

namespace mylibrary {

Player::Player(int player_health) {
  health = player_health;
  max_cards = player_health;
}

void Player::ReceiveHand(std::vector<mylibrary::Card>& cards) {
  hand = cards;
}
}  // namespace mylibrary
