#pragma once
#ifndef MAP_H
#define MAP_H

#include "DxLib.h"

class Map {
public:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    int tiles[WIDTH][HEIGHT];

    Map();
    void render();
    void highlightMoveRange(int startX, int startY, int range);
};

#endif // MAP_H
