#pragma once
#include "Map.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Thief.h"

class Game {
public:
    enum Phase { MOVE, ACTION };  // © ‚±‚±‚ª”²‚¯‚Ä‚¢‚½‚Ì‚Å’Ç‰Á

    Game();
    ~Game();
    void run();  // ƒQ[ƒ€‚ÌÀs
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
    Phase phase;  // C³: `Phase` Œ^‚ğg—p

    int startScreenImage;  // Game Start‰æ–Ê‚Ì‰æ‘œ
    int gameOverScreenImage;  // Game Over‰æ–Ê‚Ì‰æ‘œ
};