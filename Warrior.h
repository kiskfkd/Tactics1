#pragma once
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character {
public:
    Warrior(int x, int y)
        : Character("Warrior", 100, 20, 20, 2, x, y, 5) {}
};

#endif 
