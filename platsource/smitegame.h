#pragma once
#pragma once
#include <vector>
#include "Monster.h"
#include "sPlayer.h"
#include "Scenario.h"


namespace smite {
    class Game {
    private:
        std::vector<Monster> monsters;
        Player player;
        Scenario scenario;

    public:
        Game();
        void start();
    };

}