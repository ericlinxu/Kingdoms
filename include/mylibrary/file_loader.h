//
// Created by Eric Xu on 4/19/20.
//

#ifndef FINALPROJECT_FILE_LOADER_H
#define FINALPROJECT_FILE_LOADER_H

#include <nlohmann/json.hpp>
#include <string>

#include "card.h"

namespace mylibrary {

std::vector<mylibrary::Card> LoadCards(const std::string& file_path);

}

#endif  // FINALPROJECT_FILE_LOADER_H
