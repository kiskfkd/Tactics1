#pragma once
#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character {
public:
    Mage(int x, int y)
        : Character("Mage", 80, 30, 10, 1, x, y, 8) {}

    void rangedAttack(Character& target) override;
};

#endif // MAGE_H
