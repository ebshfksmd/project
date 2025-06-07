#pragma once

namespace Gacha {
    class Bullet {
    public:
        int x, y;
        bool active;
        Bullet() : x(0), y(0), active(false) {}
        void Move() { x += 2; if (x > 33) active = false; }
    };
}
