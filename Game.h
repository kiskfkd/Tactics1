#pragma once
#include "Map.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Thief.h"

class Game {
public:
    enum Phase { MOVE, ACTION };  // ← ここが抜けていたので追加

    Game();
    ~Game();
    void run();  // ゲームの実行
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
    Phase phase;  // 修正: `Phase` 型を使用

    int startScreenImage;  // Game Start画面の画像
    int gameOverScreenImage;  // Game Over画面の画像
};