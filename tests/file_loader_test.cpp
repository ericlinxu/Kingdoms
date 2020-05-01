// Created by Eric Xu on 4/30/20.


#include <mylibrary/file_loader.h>
#include <catch2/catch.hpp>

#include <vector>

using mylibrary::LoadCards;

TEST_CASE("Loads a valid file path", "[vector of type card]") {
  REQUIRE(LoadCards("cards/cards.json").size() == 3);
}

TEST_CASE("Loads an invalid file path", "[throw runtime error]") {
  REQUIRE_THROWS_WITH(LoadCards("Get 100 on Finals")
      , "Unable to open file Get 100 on Finals");
}