#include "Game.h"
#include "DxLib.h"

Game::Game() : player1Turn(true), selectedCharacter(nullptr), mousePressed(false), phase(MOVE) {
    player1 = new Archer(5, 5);
    player2 = new Mage(15, 15);
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::run() {
    showStartScreen();  // ゲームスタート画面を表示
    while (ProcessMessage() == 0) {
        ClearDrawScreen();
        update();
        render();
        ScreenFlip();
    }
}

void Game::showStartScreen() {
    while (ProcessMessage() == 0) {
        ClearDrawScreen();
        DrawString(100, 100, "Game Start", GetColor(255, 255, 255));
        DrawString(100, 150, "Press ENTER to start", GetColor(255, 255, 255));
        ScreenFlip();

        if (CheckHitKey(KEY_INPUT_RETURN)) {
            break;  // ENTERキーが押されたらゲーム開始
        }
    }
}

void Game::showGameOverScreen() {
    ClearDrawScreen();
    DrawString(100, 100, "Game Over", GetColor(255, 0, 0));
    DrawString(100, 150, "Press ENTER to exit", GetColor(255, 255, 255));
    ScreenFlip();

    while (ProcessMessage() == 0) {
        if (CheckHitKey(KEY_INPUT_RETURN)) {
            DxLib_End();
            exit(0);
        }
    }
}

void Game::render() {
    map.render();
    if (selectedCharacter && phase == MOVE) {
        map.highlightMoveRange(selectedCharacter->posX, selectedCharacter->posY, selectedCharacter->actionPoints);
    }
    player1->render();
    player2->render();
}

void Game::update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    int gridX = mouseX / 20;
    int gridY = mouseY / 20;

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
        if (!mousePressed) { // クリックが初めて検出された場合のみ処理
            mousePressed = true;
            if (phase == MOVE) {
                if (selectedCharacter == nullptr) {
                    if (player1Turn && gridX == player1->posX && gridY == player1->posY) {
                        selectedCharacter = player1;
                        player1->isSelected = true;
                    }
                    else if (!player1Turn && gridX == player2->posX && gridY == player2->posY) {
                        selectedCharacter = player2;
                        player2->isSelected = true;
                    }
                }
                else {
                    if (std::abs(gridX - selectedCharacter->posX) + std::abs(gridY - selectedCharacter->posY) <= selectedCharacter->actionPoints && map.tiles[gridX][gridY] == 0) {
                        selectedCharacter->act(gridX, gridY);
                        phase = ACTION;
                    }
                }
            }
        }
    }
    else {
        mousePressed = false; // クリックが離されたらリセット
    }

    if (CheckHitKey(KEY_INPUT_SPACE) && phase == ACTION) {
        // スペースキーでターンを終了
        if (selectedCharacter) {
            selectedCharacter->isSelected = false;
            selectedCharacter = nullptr;
        }
        player1Turn = !player1Turn;
        phase = MOVE;
    }

    if (CheckHitKey(KEY_INPUT_A) && selectedCharacter != nullptr && phase == ACTION) {
        if (player1Turn) {
            selectedCharacter->rangedAttack(*player2); // プレイヤー1のターンで遠距離攻撃
        }
        else {
            selectedCharacter->rangedAttack(*player1); // プレイヤー2のターンで遠距離攻撃
        }

        // 攻撃後、ターン終了
        if (selectedCharacter) {
            selectedCharacter->isSelected = false;
            selectedCharacter = nullptr;
        }
        player1Turn = !player1Turn;
        phase = MOVE;
    }

    // HPが0になったらゲームオーバー
    if (player1->hp <= 0 || player2->hp <= 0) {
        showGameOverScreen();
    }
}