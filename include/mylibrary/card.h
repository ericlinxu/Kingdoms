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
  int health, number;
  string name, match, image;

 public:
  Card();
  Card(int heal, string& name, string& match, int number, string& image);
  int GetHealth();
  string GetMatch();
  string GetName();
  int GetNumber();
  string GetImage();
};

}

#endif  // FINALPROJECT_CARD_H
