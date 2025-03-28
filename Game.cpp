#include "Game.h"
#include "DxLib.h"

Game::Game() : player1Turn(true), selectedCharacter(nullptr), mousePressed(false), phase(MOVE) {
    player1 = new Archer(5, 5);
    player2 = new Mage(15, 15);

    // �摜��ǂݍ���
    startScreenImage = LoadGraph("Assets/Tactics.png");
    gameOverScreenImage = LoadGraph("Assets/Tactics.png");
}

Game::~Game() {
    delete player1;
    delete player2;

    // �摜���폜
    DeleteGraph(startScreenImage);
    DeleteGraph(gameOverScreenImage);
}

void Game::run() {
    showStartScreen();  // �Q�[���X�^�[�g��ʂ�\��
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
       
        DrawGraph(0, 0, startScreenImage, TRUE);  // �摜��`��
        DrawString(230, 390, "Start", GetColor(255, 255, 255));
        DrawString(160, 410, "Press ENTER to start", GetColor(255, 255, 255));
        ScreenFlip();

        if (CheckHitKey(KEY_INPUT_RETURN)) {
            break;  // ENTER�L�[�������ꂽ��Q�[���J�n
        }
    }
}

void Game::showGameOverScreen() {
    ClearDrawScreen();
 
    DrawGraph(0, 0, gameOverScreenImage, TRUE);  // �摜��`��
    DrawString(235, 390, "Over", GetColor(255, 0, 0));
    DrawString(160, 410, "Press ENTER to exit", GetColor(255, 255, 255));
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
        if (!mousePressed) { // �N���b�N�����߂Č��o���ꂽ�ꍇ�̂ݏ���
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
        mousePressed = false; // �N���b�N�������ꂽ�烊�Z�b�g
    }

    if (CheckHitKey(KEY_INPUT_SPACE) && phase == ACTION) {
        if (selectedCharacter) {
            selectedCharacter->isSelected = false;
            selectedCharacter = nullptr;
        }
        player1Turn = !player1Turn;
        phase = MOVE;
    }

    if (CheckHitKey(KEY_INPUT_A) && selectedCharacter != nullptr && phase == ACTION) {
        if (player1Turn) {
            selectedCharacter->rangedAttack(*player2); // �v���C���[1�̃^�[���ŉ������U��
        }
        else {
            selectedCharacter->rangedAttack(*player1); // �v���C���[2�̃^�[���ŉ������U��
        }

        if (selectedCharacter) {
            selectedCharacter->isSelected = false;
            selectedCharacter = nullptr;
        }
        player1Turn = !player1Turn;
        phase = MOVE;
    }

    if (player1->hp <= 0 || player2->hp <= 0) {
        showGameOverScreen();
    }
}