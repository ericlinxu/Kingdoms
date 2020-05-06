# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)

## Legend of the Two Kingdoms

Author: Eric Xu - [`ericlx2@illinois.edu`](mailto:example@illinois.edu)

### Dependencies
1. Cinder
2. Nlohmann/JSON
3. CMake
4. Catch2

### How to Play
1. Use the left mouse key to control your decisions
1. There are 2 players with 3 health each
2. Each player has an x amount of cards with different abilities at the start 
of each round
3. Each round, 1 player will be in attack mode and the other will be in
defense mode
4. The player in attack mode can use the cards:
    1. "Hit" - Possibility of making the opponent lose 1 health
    2. "Heal" - Add 1 health back for yourself if you have less than 3 health
5. The player in defense mode can use the cards:
    1. "Dodge" - Used to dodge "Hit", prevents you from losing 1 health
    2. "Heal" - Only can be used if you are at 0 health after being damaged
    by "hit". This is your last chance to save yourself
5. Press the red End Round button to end your turn
6. At the end of each round, if the attacking player has more cards than
health, the attacking player will have to discard x amount of cards until
he/she has number of cards equal to health
7. The goal of this game is to get your opponent to 0 health

---
