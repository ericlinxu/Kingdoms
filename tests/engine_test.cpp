// Created by Eric Xu on 4/30/20.

#include <mylibrary/engine.h>
#include <catch2/catch.hpp>

using mylibrary::Engine;
using mylibrary::Card;
using mylibrary::Player;

TEST_CASE("Engine Constructor", "Using getter methods to test") {
  Engine engine;
  REQUIRE(engine.GetCardsUsed().size() == 3);
  REQUIRE(engine.GetDeckSize() == 60);
  REQUIRE(engine.GetPlayer(0).hand.size() == 3);
  REQUIRE(engine.GetOpponent(1).hand.size() == 3);
}

TEST_CASE("Switch Player") {
  Engine engine;
  REQUIRE(engine.current_player == 0);

  engine.SwitchPlayer();
  REQUIRE(engine.current_player == 1);
}

TEST_CASE("CheckEndGame", "Checking game state") {
  Engine engine;
  engine.GetPlayer(engine.current_player).SetHealth(0);
  engine.CheckEndGame();
  REQUIRE(engine.end_game);
  REQUIRE(engine.current_player == 0);
}

TEST_CASE("UnableToDodge") {
  Engine engine;
  //The first element of cards_used is the "hit" card
  engine.discard = engine.GetCardsUsed()[0];
  REQUIRE_FALSE(engine.discard.GetName().empty());

  engine.UnableToDodge();
  REQUIRE(engine.GetOpponent(engine.current_player).GetHealth() == 2);
  REQUIRE(engine.discard.GetName().empty());
}

TEST_CASE("PlayCard") {
  Engine engine;
  std::string dummy;
  Card card(0, dummy, dummy, 126, dummy);
  engine.PlayCard(card);
  REQUIRE(engine.GetPlayedCard().GetNumber() == 126);
}

TEST_CASE("EndRound") {
  Engine engine;
  Player& player = engine.GetPlayer(engine.current_player);
  for (Card card: engine.GetCardsUsed()) {
    player.DrawCards(card);
  }
  engine.too_many_cards = true;
  engine.end_round = true;
  REQUIRE(player.hand.size() == 6);

  engine.EndRound(player.hand[0]);
  REQUIRE(engine.too_many_cards);
  REQUIRE(engine.end_round);
  REQUIRE(player.hand.size() == 5);

  engine.EndRound(player.hand[0]);
  engine.EndRound(player.hand[0]);
  REQUIRE_FALSE(engine.too_many_cards);
  REQUIRE_FALSE(engine.end_round);
  REQUIRE(player.hand.size() == 3);
}

TEST_CASE("Engine Save") {
  Engine engine;
  Player& player = engine.GetPlayer(engine.current_player);
  engine.end_game = true;
  Card heal = engine.GetCardsUsed()[2];
  Card other = engine.GetCardsUsed()[0];
  REQUIRE(engine.current_player == 0);
  REQUIRE(engine.discard.GetName().empty());
  REQUIRE(engine.GetPlayedCard().GetName().empty());

  SECTION("Used heal", "[saved]") {
    engine.PlayCard(heal);
    REQUIRE(engine.GetPlayedCard().GetName() == "heal");

    engine.Save();
    REQUIRE(engine.current_player == 1);
    REQUIRE(engine.discard.GetName() == "heal");
    REQUIRE_FALSE(engine.end_game);
    REQUIRE(engine.GetPlayedCard().GetName().empty());
  }

  SECTION("Did not use heal", "[game over]") {
    engine.PlayCard(other);
    REQUIRE_FALSE(engine.GetPlayedCard().GetName().empty());

    engine.Save();
    REQUIRE(engine.current_player == 0);
    REQUIRE(engine.discard.GetName().empty());
    REQUIRE(engine.end_game);
    REQUIRE_FALSE(engine.GetPlayedCard().GetName().empty());
  }
}