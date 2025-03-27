#pragma once
#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Thief.h"

class Game {
public:
    enum Phase { MOVE, ACTION };

    Map map;
    Character* player1;
    Character* player2;
    Character* selectedCharacter;
    bool player1Turn;
    bool mousePressed;
    Phase phase;

    Game();
    ~Game();
    void render();
    void update();
    void run();
    void showStartScreen();
    void showGameOverScreen();
};

#endif // GAME_H