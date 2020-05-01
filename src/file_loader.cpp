// Created by Eric Xu on 4/19/20.

#include <cinder/app/AppBase.h>
#include <mylibrary/card.h>
#include <mylibrary/file_loader.h>

#include <vector>

namespace mylibrary {

/**
 * Loads the JSON file for the cards into a Card vector
 * @param file_path: path of the JSON file
 * @return vector of cards
 */
std::vector<mylibrary::Card> LoadCards(const std::string& file_path) {
  string processed_file_path = cinder::app::getAssetPath(file_path).string();
  std::ifstream load(processed_file_path);

  if(load.fail()) {
    throw std::runtime_error("Unable to open file " + file_path);
  }

  nlohmann::json file;
  load >> file;
  std::vector<mylibrary::Card> cards;

  for (const auto& card : file["cards"]) {
    string name = card.at("name");
    string match = card.at("match");
    string image = card.at("image");
    mylibrary::Card element(card.at("health"), name, match
        , card.at("number"), image);
    cards.push_back(element);
  }

  return cards;
}

}