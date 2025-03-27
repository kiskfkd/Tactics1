#include "Map.h"
#include <cmath> 
Map::Map() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            tiles[x][y] = (rand() % 100 < 20) ? 1 : 0; // 20%‚ÅáŠQ•¨
        }
    }
}

void Map::render() {
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

void Map::highlightMoveRange(int startX, int startY, int range) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (std::abs(x - startX) + std::abs(y - startY) <= range && tiles[x][y] == 0) {
                DrawBox(x * 20, y * 20, (x + 1) * 20, (y + 1) * 20, GetColor(0, 255, 255), FALSE);
            }
        }
    }
}

