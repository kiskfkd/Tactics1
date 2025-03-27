#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <cmath>
#include "DxLib.h"


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

    virtual void render();
    virtual void act(int targetX, int targetY);
    void attackCharacter(Character& target);
    virtual void rangedAttack(Character& target);
};

#endif 