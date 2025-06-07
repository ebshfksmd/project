#pragma once
#include <cstdlib>

namespace Gacha {
    class Enemy {
    public:
        int x, y;
        Enemy() : x(32), y(8) {}
        void NewEnemy() { y = (rand() % 15) + 1; x = 32; }
        void Move() { x--; }
    };
}