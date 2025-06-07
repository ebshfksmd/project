#include "GameRender.h"
#include <iostream>
#include <string>
#include <windows.h>

namespace defense {

    using namespace std;

    string getAsciiUnit(char type) {
        if (type == 'K') return "[oKo]";
        if (type == 'H') return "[oHo]";
        if (type == 'T') return "[oTo]";
        return "     ";
    }

    string getAsciiMonster(char type) {
        if (type == 'N') return "(NnN)";
        if (type == 'D') return "(DdD)";
        if (type == 'M') return "(MmM)";
        if (type == 'B') return "(BoB)";
        return "     ";
    }

    void drawScreen(const vector<vector<Unit*>>& unitMap, const vector<Monster>& monsters, int gold, int playerHP, bool gameClear, bool gameOver) {
        system("cls");
        cout << "GOLD: " << gold << "   HP: " << playerHP << "\n";
        cout << "================= DEFENSE =================" << endl;

        for (int i = 0; i < ROWS; ++i) {
            cout << "Y" << i << "|";
            for (int j = 0; j < COLS; ++j) {
                bool drawn = false;
                if (unitMap[i][j]) {
                    cout << getAsciiUnit(unitMap[i][j]->type);
                    drawn = true;
                }
                else {
                    for (auto& m : monsters) {
                        if (m.row == i && m.col == j) {
                            cout << getAsciiMonster(m.type);
                            drawn = true;
                            break;
                        }
                    }
                }
                if (!drawn) cout << "     ";
            }
            cout << "|" << endl;
        }

        cout << "================== /_T_\\ ==================\n";
        if (gameClear) cout << "\n[GAME CLEAR]\n";
        if (gameOver) cout << "\n[GAME OVER]\n";
    }

}