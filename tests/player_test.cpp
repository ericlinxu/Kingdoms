// Copyright (c) 2020 [Eric Xu]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <mylibrary/player.h>
#include <catch2/catch.hpp>

using mylibrary::Player;
using mylibrary::Card;

TEST_CASE("Constructor", "[Position][Health][Max Cards][Empty Hand]") {
  Player player(3, 0);
  REQUIRE(player.GetPosition() == 0);
  REQUIRE(player.GetHealth() == 3);
  REQUIRE(player.GetMaxCards() == 3);
  REQUIRE(player.hand.empty());
}

TEST_CASE("DrawCards", "[HandSize]") {
  Player player(3, 0);
  REQUIRE(player.hand.empty());

  Card card;
  player.DrawCards(card);
  REQUIRE(player.hand.size() == 1);
}

TEST_CASE("PlayCard(hit)", "[Card Hit possibilities]") {
  string name = "hit";
  string match = "dodge";
  string file = "cards/hit.jpeg";
  Card hit(-1,name, match, 30, file);
  Player player(3, 0);

  //Hit, not responding -> true
  REQUIRE(player.PlayCard(hit, false));

  //Hit, responding -> false
  REQUIRE_FALSE(player.PlayCard(hit, true));
}

TEST_CASE("PlayCard(dodge)", "[Card Dodge possibilities]") {
  string name = "dodge";
  string match;
  string file = "cards/dodge.png";
  Card dodge(1,name, match, 24, file);
  Player player(3, 0);

  //Dodge, responding -> true
  REQUIRE(player.PlayCard(dodge, true));

  //Dodge, not responding -> false
  REQUIRE_FALSE(player.PlayCard(dodge, false));
}

TEST_CASE("PlayCard(heal)", "[Card Heal possibilities]") {
  string name = "heal";
  string match;
  string file = "cards/heal.png";
  Card heal(1,name, match, 12, file);
  Player player(3, 0);

  //Heal, responding -> false
  REQUIRE_FALSE(player.PlayCard(heal, true));

  //Heal, not responding, full health -> false
  REQUIRE(player.GetHealth() == 3);
  REQUIRE_FALSE(player.PlayCard(heal, false));

  //Heal, not responding, not full health -> true
  player.SetHealth(2);
  REQUIRE(player.GetHealth() == 2);
  REQUIRE(player.PlayCard(heal, false));
}

TEST_CASE("RemoveCard") {
  Player player(3,0);
  Card card;
  player.DrawCards(card);
  REQUIRE(player.hand.size() == 1);

  player.RemoveCard(card);
  REQUIRE(player.hand.empty());
}

TEST_CASE("Save") {
  Player player(0,0);
  string name = "heal";
  string match;
  string file = "cards/heal.png";
  Card heal(1,name, match, 12, file);
  //Passed in Card is "heal" so true
  REQUIRE(player.Save(heal));

  Card card;
  //Passed in card is not "heal" so false
  REQUIRE_FALSE(player.Save(card));
}

TEST_CASE("GetPosition") {
  Player player(0,0);
  REQUIRE(player.GetPosition() == 0);
}

TEST_CASE("GetHealth") {
  Player player(100,0);
  REQUIRE(player.GetHealth() == 100);
}

TEST_CASE("GetMaxCards") {
  Player player(126,0);
  REQUIRE(player.GetMaxCards() == 126);
}

TEST_CASE("SetHealth") {
  Player player(0,0);
  REQUIRE(player.GetHealth() == 0);

  player.SetHealth(126);
  REQUIRE(player.GetHealth() == 126);
}