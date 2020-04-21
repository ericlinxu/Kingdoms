//
// Created by Eric Xu on 4/19/20.
//

#ifndef FINALPROJECT_CARD_H
#define FINALPROJECT_CARD_H

#include <string>
using std::string;

namespace mylibrary {

class Card {
 private:
  int health;
  string name, match;

 public:
  Card(int heal, string& name, string& match);
};

}

#endif  // FINALPROJECT_CARD_H
