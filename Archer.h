#pragma once
#ifndef ARCHER_H
#define ARCHER_H

#include "Character.h"

class Archer : public Character {
public:
    Archer(int x, int y)
        : Character("Archer", 70, 25, 15, 2, x, y, 10) {}

    void rangedAttack(Character& target) override;
};

#endif 
