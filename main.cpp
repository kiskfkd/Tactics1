#include "DxLib.h"
#include <vector>
#include <string>
#include <cmath>

// キャラクタークラス
class Character {
public:
    std::string name;
    int hp, maxHp, attack, defense, actionPoints;
    int posX, posY;
    int viewRange;
    bool isHidden;
    bool isSelected;

    Character(std::string name, int maxHp, int attack, int defense, int actionPoints, int posX, int posY, int viewRange)
        : name(name), hp(maxHp), maxHp(maxHp), attack(attack), defense(defense), actionPoints(actionPoints), posX(posX), posY(posY), viewRange(viewRange), isHidden(false), isSelected(false) {}

    virtual void render() {
        // キャラクターごとに色を分ける
        int color;
        if (name == "Warrior") {
            color = GetColor(255, 0, 0);  // 戦士は赤
        }
        else if (name == "Archer") {
            color = GetColor(255, 255, 0);  // 弓使いは黄色
        }
        else if (name == "Mage") {
            color = GetColor(128, 0, 128);  // 魔法使いは紫
        }
        else if (name == "Thief") {
            color = GetColor(0, 0, 0);  // 盗賊は黒
        }
        else {
            color = GetColor(255, 255, 255);  // デフォルトは白
        }

        // キャラクターを色で描画
        DrawCircle(posX * 20 + 10, posY * 20 + 10, 10, color, TRUE);

        // HPバーの描画
        int barWidth = 40;  // HPバーの幅
        int barHeight = 5;  // HPバーの高さ
        int currentBarWidth = static_cast<int>((static_cast<float>(hp) / static_cast<float>(maxHp)) * barWidth);
        DrawBox(posX * 20 + 10 - barWidth / 2, posY * 20 + 10 - 15, posX * 20 + 10 - barWidth / 2 + currentBarWidth, posY * 20 + 10 - 15 + barHeight, GetColor(255, 0, 0), TRUE);
        DrawBox(posX * 20 + 10 - barWidth / 2, posY * 20 + 10 - 15, posX * 20 + 10 - barWidth / 2 + barWidth, posY * 20 + 10 - 15 + barHeight, GetColor(0, 0, 0), FALSE);  // 背景
    }

    virtual void act(int targetX, int targetY) {
        posX = targetX;
        posY = targetY;
    }

    // 攻撃メソッドの追加
    void attackCharacter(Character& target) {
        if (std::abs(target.posX - posX) + std::abs(target.posY - posY) <= 1) {  // 隣接している場合に攻撃
            int damage = attack - target.defense;
            if (damage < 0) damage = 0;
            target.hp -= damage;
            if (target.hp < 0) target.hp = 0;
        }
    }

    // 遠距離攻撃メソッド
    virtual void rangedAttack(Character& target) {
        int distance = std::abs(target.posX - posX) + std::abs(target.posY - posY);
        if (distance <= viewRange) {  // 視野内にターゲットがいれば攻撃
            int damage = attack - target.defense;
            if (damage < 0) damage = 0;
            target.hp -= damage;
            if (target.hp < 0) target.hp = 0;
        }
    }
};

// 各クラスを継承して特徴的なキャラクターを定義
class Warrior : public Character {
public:
    Warrior(int x, int y)
        : Character("Warrior", 100, 20, 20, 2, x, y, 5) {}
};

class Mage : public Character {
public:
    Mage(int x, int y)
        : Character("Mage", 80, 30, 10, 1, x, y, 8) {}

    void rangedAttack(Character& target) override {
        // 魔法使いは視界内のキャラクターを遠距離攻撃
        int distance = std::abs(target.posX - posX) + std::abs(target.posY - posY);
        if (distance <= viewRange) {  // 視野内にターゲットがいれば攻撃
            int damage = attack - target.defense;
            if (damage < 0) damage = 0;
            target.hp -= damage;
            if (target.hp < 0) target.hp = 0;
        }
    }
};

class Archer : public Character {
public:
    Archer(int x, int y)
        : Character("Archer", 70, 25, 15, 2, x, y, 10) {}

    void rangedAttack(Character& target) override {
        // 弓使いは視界内のキャラクターを遠距離攻撃
        int distance = std::abs(target.posX - posX) + std::abs(target.posY - posY);
        if (distance <= viewRange) {  // 視野内にターゲットがいれば攻撃
            int damage = attack - target.defense;
            if (damage < 0) damage = 0;
            target.hp -= damage;
            if (target.hp < 0) target.hp = 0;
        }
    }
};

class Thief : public Character {
public:
    Thief(int x, int y)
        : Character("Thief", 60, 15, 10, 3, x, y, 6) {}
};

// マップクラス
class Map {
public:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    int tiles[WIDTH][HEIGHT];

    Map() {
        // マップの初期化
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                tiles[x][y] = (rand() % 100 < 20) ? 1 : 0; // 20%で障害物
            }
        }
    }

    void render() {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (tiles[x][y] == 1) {
                    DrawBox(x * 20, y * 20, (x + 1) * 20, (y + 1) * 20, GetColor(128, 128, 128), TRUE);
                }
                else {
                    DrawBox(x * 20, y * 20, (x + 1) * 20, (y + 1) * 20, GetColor(0, 128, 0), TRUE);
                }
            }
        }
    }

    void highlightMoveRange(int startX, int startY, int range) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (std::abs(x - startX) + std::abs(y - startY) <= range && tiles[x][y] == 0) {
                    DrawBox(x * 20, y * 20, (x + 1) * 20, (y + 1) * 20, GetColor(0, 255, 255), FALSE);
                }
            }
        }
    }
};

// ゲームクラス
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

    Game() : player1Turn(true), selectedCharacter(nullptr), mousePressed(false), phase(MOVE) {
        player1 = new Archer(5, 5);  // プレイヤー1は弓使い
        player2 = new Mage(15, 15);   // プレイヤー2は魔法使い
    }

    ~Game() {
        delete player1;
        delete player2;
    }

    void render() {
        map.render();
        if (selectedCharacter && phase == MOVE) {
            map.highlightMoveRange(selectedCharacter->posX, selectedCharacter->posY, selectedCharacter->actionPoints);
        }
        player1->render();
        player2->render();
    }

    void update() {
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

        // 遠距離攻撃
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
            phase = MOVE; // ターンを終了させる
        }
    }
};

// main関数
int main() {
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Game game;

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        game.render();
        game.update();
    }

    DxLib_End();
    return 0;
}
