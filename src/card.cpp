// Created by Eric Xu on 4/19/20.

#include "mylibrary/card.h"

namespace mylibrary {

/**
 * Constructor
 * @param card_health: Initializes Card health
 * @param card_name: Initializes Card name
 * @param card_match: Initializes Card match
 * @param card_number: Initializes the number of cards of its type in the game
 * @param image_path: Initializes the image file path of the card
 */
Card::Card(int card_health, string& card_name, string& card_match
    , int card_number, string& image_path) {
  health = card_health;
  match = card_match;
  name = card_name;
  number = card_number;
  image = image_path;
}

/**
 * Default Constructor
 * Initializes everything to 0 or empty
 */
Card::Card() {
  health = 0;
  number = 0;
  name = "";
  match = "";
  image = "";
}

/**
 * Functions similarly to the default constructor
 * Empty's the card that calls this method
 */
void Card::reset() {
  health = 0;
  number = 0;
  name = "";
  match = "";
  image = "";
}

/**
 * Gets the health of the card
 */
int Card::GetHealth() {
  return health;
}

/**
 * Gets the name of the card
 */
string Card::GetName() {
  return name;
}

string Card::GetMatch() {
  return match;
}

/**
 * Gets the number of cards that need to be created in the deck
 */
int Card::GetNumber() {
  return number;
}

/**
 * Gets the image file path of the card
 */
string Card::GetImage() {
  return image;
}
}