# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)

# Legend of the Two Kingdoms

Author: Eric Xu - [`ericlx2@illinois.edu`](mailto:example@illinois.edu)

##[Introduction]
The project I am attempting to create comes from a chinese card game called
the Legend of the Three Kingdoms. I am attempting to make a more simplified
version of this game since the full version consists of many parts and is
very complex.

I want to do this project because I really like to play this card game. I feel
that this project will also have many challenging parts that I have not tried
to touch before. I feel that this project will be a big learning opportunity
for me and I will also enjoy this process as this is a project that I am very
interested in.

##[How to Play]
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

##[Libraries Used]
1. Cinder Library (https://github.com/cinder/Cinder)
    1. Used for adding images/audio/graphics/opengl
    2. The overall layout of the UI
2. nlohmann/JSON Library (https://github.com/nlohmann/json)
    1. Used for storing data relating to the cards
        1. Abilities
    2. Able to add cards to the json file for more variability
3. Catch Library (https://github.com/catchorg/Catch2)
    1. Used for testing code
  
##[Timeline]  
####[Finished by end of first week]
1. Write up JSON file for the cards to the game
2. Create classes for Cards and Players
3. Do the testing for each class

####[Finished by end of second week]
1. Create classes for the main functionality of the game
2. Start on the UI for the game
3. Do the testing for each class

####[Finished by end of third week]
1. Finish the UI for the game
2. Testing for the UI
2. Brush up on all of the code

##[Stretch Goals]
1. Make UI more pretty
2. Add more cards with different abilities

---
