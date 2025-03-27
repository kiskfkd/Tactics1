#include "Character.h"

void Character::render() {
    int color;
    if (name == "Warrior") {
        color = GetColor(255, 0, 0);  // ��m�͐�
    }
    else if (name == "Archer") {
        color = GetColor(255, 255, 0);  // �|�g���͉��F
    }
    else if (name == "Mage") {
        color = GetColor(128, 0, 128);  // ���@�g���͎�
    }
    else if (name == "Thief") {
        color = GetColor(0, 0, 0);  // �����͍�
    }
    else {
        color = GetColor(255, 255, 255);  // �f�t�H���g�͔�
    }

    // �L�����N�^�[��F�ŕ`��
    DrawCircle(posX * 20 + 10, posY * 20 + 10, 10, color, TRUE);

    // HP�o�[�̕`��
    int barWidth = 40;
    int barHeight = 5;
    int currentBarWidth = static_cast<int>((static_cast<float>(hp) / static_cast<float>(maxHp)) * barWidth);
    DrawBox(posX * 20 + 10 - barWidth / 2, posY * 20 + 10 - 15, posX * 20 + 10 - barWidth / 2 + currentBarWidth, posY * 20 + 10 - 15 + barHeight, GetColor(255, 0, 0), TRUE);
    DrawBox(posX * 20 + 10 - barWidth / 2, posY * 20 + 10 - 15, posX * 20 + 10 - barWidth / 2 + barWidth, posY * 20 + 10 - 15 + barHeight, GetColor(0, 0, 0), FALSE);  // �w�i
}

void Character::act(int targetX, int targetY) {
    posX = targetX;
    posY = targetY;
}

void Character::attackCharacter(Character& target) {
    if (std::abs(target.posX - posX) + std::abs(target.posY - posY) <= 1) {
        int damage = attack - target.defense;
        if (damage < 0) damage = 0;
        target.hp -= damage;
        if (target.hp < 0) target.hp = 0;
    }
}

void Character::rangedAttack(Character& target) {
    int distance = std::abs(target.posX - posX) + std::abs(target.posY - posY);
    if (distance <= viewRange) {
        int damage = attack - target.defense;
        if (damage < 0) damage = 0;
        target.hp -= damage;
        if (target.hp < 0) target.hp = 0;
    }
}
