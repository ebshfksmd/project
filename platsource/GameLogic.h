#pragma once
#include <vector>

namespace defense {

    const int ROWS = 5;
    const int COLS = 20;

    struct Unit {
        char type;
        int hp, atk, range;
    };

    struct Monster {
        char type;
        int row, col, hp, atk;
    };

    extern int gold;
    extern int playerHP;
    extern bool gameOver;
    extern bool gameClear;

    extern std::vector<std::vector<Unit*>> unitMap;
    extern std::vector<Monster> monsters;

    void unitAttack();
    void monsterMove();
    void spawnMonster(int turn);
    void shop();
    void cleanupUnits();

}