//
// Created by Eric Xu on 4/30/20.
//

#include <cinder/Rand.h>
#include <mylibrary/file_loader.h>
#include <catch2/catch.hpp>

#include <vector>

using mylibrary::LoadCards;
using mylibrary::Card;
using std::vector;

TEST_CASE("Loads a valid file path", "[vector of type card]") {
  vector<Card> cards = LoadCards("cards/cards.json");
  REQUIRE(cards.size() == 3);
}

TEST_CASE("Loads an invalid file path", "[throw runtime error]") {
  REQUIRE_THROWS_WITH(LoadCards("Get 100 on Finals")
      , "Unable to open file Get 100 on Finals");
}