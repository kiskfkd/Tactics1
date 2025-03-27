#pragma once
#ifndef THIEF_H
#define THIEF_H

#include "Character.h"

class Thief : public Character {
public:
    Thief(int x, int y)
        : Character("Thief", 60, 15, 10, 3, x, y, 6) {}
};

#endif // THIEF_H
