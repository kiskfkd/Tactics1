#pragma once
#include "Map.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Thief.h"

class Game {
public:
    enum Phase { MOVE, ACTION };  // �� �����������Ă����̂Œǉ�

    Game();
    ~Game();
    void run();  // �Q�[���̎��s
    void render();
    void update();

private:
    void showStartScreen();
    void showGameOverScreen();

    Map map;
    Character* player1;
    Character* player2;
    Character* selectedCharacter;
    bool player1Turn;
    bool mousePressed;
    Phase phase;  // �C��: `Phase` �^���g�p

    int startScreenImage;  // Game Start��ʂ̉摜
    int gameOverScreenImage;  // Game Over��ʂ̉摜
};