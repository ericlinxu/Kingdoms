//
// Created by Eric Xu on 4/19/20.
//

#include "mylibrary/file_loader.h"
#include <mylibrary/card.h>

#include <fstream>
#include <vector>

std::vector<mylibrary::Card> LoadCards(const std::string& file_path) {
  std::ifstream load(file_path);
  nlohmann::json file;
  load >> file;
  std::vector<mylibrary::Card> cards;

  for (const auto& card : file["cards"]) {
    string name = card.at("name");
    string match = card.at("match");
    mylibrary::Card element(card.at("health"), name, match);
    cards.push_back(element);
  }

  return cards;
}