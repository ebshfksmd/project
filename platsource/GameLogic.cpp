#include "GameLogic.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace defense {

    using namespace std;

    int gold = 30;
    int playerHP = 20;
    bool gameOver = false;
    bool gameClear = false;
    bool bossSpawned = false;
    int spawnTimer = 0;

    vector<vector<Unit*>> unitMap(ROWS, vector<Unit*>(COLS, nullptr));
    vector<Monster> monsters;

    bool isMonsterAt(int row, int col) {
        for (auto& m : monsters)
            if (m.row == row && m.col == col) return true;
        return false;
    }

    void shop() {
        cout << "\n--- 상점 ---\n";
        cout << "1. 기본 유닛(K) 5G\n2. 강화 유닛(H) 10G\n3. 탱커 유닛(T) 10G\n구매할 유닛 번호 (0: 취소): ";
        int choice; cin >> choice;
        Unit* u = nullptr;

        if (choice == 1 && gold >= 5) u = new Unit{ 'K', 10, 3, 3 }, gold -= 5;
        else if (choice == 2 && gold >= 10) u = new Unit{ 'H', 10, 5, 3 }, gold -= 10;
        else if (choice == 3 && gold >= 10) u = new Unit{ 'T', 20, 1, 1 }, gold -= 10;
        else { cout << "구매 불가\n"; return; }

        cout << "배치할 줄 (0~4): ";
        int r; cin >> r;
        for (int j = 0; j < COLS; ++j) {
            if (!unitMap[r][j] && !isMonsterAt(r, j)) {
                unitMap[r][j] = u;
                return;
            }
        }
        cout << "해당 줄에 배치 공간 없음\n";
        delete u;
    }

    void unitAttack() {
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j) {
                Unit* u = unitMap[i][j];
                if (u)
                    for (auto& m : monsters)
                        if (m.row == i && m.col <= j + u->range && m.col > j) {
                            m.hp -= u->atk;
                            break;
                        }
            }
    }

    void monsterMove() {
        for (auto& m : monsters) {
            int nextCol = m.col - 1;
            if (nextCol >= 0 && unitMap[m.row][nextCol]) {
                Unit* u = unitMap[m.row][nextCol];
                u->hp -= m.atk;
                if (u->hp <= 0) {
                    delete unitMap[m.row][nextCol];
                    unitMap[m.row][nextCol] = nullptr;
                }
            }
            else m.col = nextCol;
        }

        for (auto it = monsters.begin(); it != monsters.end();) {
            if (it->col < 0) {
                playerHP -= it->atk;
                it = monsters.erase(it);
            }
            else if (it->hp <= 0) {
                if (it->type == 'B') gameClear = true;
                else gold += 7;
                it = monsters.erase(it);
            }
            else ++it;
        }
    }

    void spawnMonster(int turn) {
        spawnTimer++;
        if (spawnTimer % 3 != 0) return;

        int r = rand() % ROWS;
        char type = 'N';
        int hp = 10, atk = 2;

        if (!bossSpawned && turn >= 40) {
            type = 'B'; hp = 40; atk = 4; bossSpawned = true;
        }
        else {
            int randVal = rand() % 100;
            if (randVal < 60) type = 'N';
            else if (randVal < 85) type = 'M';
            else type = 'D';
        }

        monsters.push_back({ type, r, COLS - 1, hp, atk });
    }

    void cleanupUnits() {
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                if (unitMap[i][j]) {
                    delete unitMap[i][j];
                    unitMap[i][j] = nullptr;
                }
    }

}