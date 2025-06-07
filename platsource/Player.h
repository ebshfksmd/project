#pragma once
#include <vector>
#include "Bullet.h"

namespace Gacha {
    class Player {
    public:
        int y;
        static const int x = 2;
        Player() : y(8) {}

        void MoveUp() { if (y > 1) y--; }
        void MoveDown() { if (y < 15) y++; }

        void Fire(std::vector<Bullet>& bullets) {
            for (auto& b : bullets) {
                if (!b.active) {
                    b.x = x + 4;
                    b.y = y;
                    b.active = true;
                    break;
                }
            }
        }
    };
}