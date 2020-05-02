// Created by Eric Xu on 4/30/20.

#include <mylibrary/card.h>
#include <catch2/catch.hpp>

using mylibrary::Card;

TEST_CASE("5-arg Constructor") {
  string name = "hit";
  string match = "dodge";
  string file = "cards/hit.jpeg";
  Card hit(-1,name, match, 30, file);

  REQUIRE(hit.GetHealth() == -1);
  REQUIRE(hit.GetName() == "hit");
  REQUIRE(hit.GetImage() == "cards/hit.jpeg");
  REQUIRE(hit.GetNumber() == 30);
  REQUIRE(hit.GetMatch() == "dodge");
}

TEST_CASE("Default Constructor") {
  Card card;

  REQUIRE(card.GetHealth() == 0);
  REQUIRE(card.GetName().empty());
  REQUIRE(card.GetImage().empty());
  REQUIRE(card.GetNumber() == 0);
  REQUIRE(card.GetMatch().empty());
}

TEST_CASE("Reset") {
  string name = "CS126";
  string match = "Woodley";
  string file = "siebel.png";
  Card card(126,name, match, 1, file);
  REQUIRE(card.GetHealth() == 126);
  REQUIRE(card.GetName() == "CS126");
  REQUIRE(card.GetImage() == "siebel.png");
  REQUIRE(card.GetNumber() == 1);
  REQUIRE(card.GetMatch() == "Woodley");

  card.reset();
  REQUIRE(card.GetHealth() == 0);
  REQUIRE(card.GetName().empty());
  REQUIRE(card.GetImage().empty());
  REQUIRE(card.GetNumber() == 0);
  REQUIRE(card.GetMatch().empty());
}

TEST_CASE("All Getter Methods") {
  string name = "Get 100 on Final";
  string match = "No Excuses";
  string file = "victory.jpeg";
  Card hit(1000000000,name, match, 126, file);

  REQUIRE(hit.GetHealth() == 1000000000);
  REQUIRE(hit.GetName() == "Get 100 on Final");
  REQUIRE(hit.GetImage() == "victory.jpeg");
  REQUIRE(hit.GetNumber() == 126);
  REQUIRE(hit.GetMatch() == "No Excuses");
}