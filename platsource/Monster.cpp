#include "Monster.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

namespace smite {
#include "Monster.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

    using namespace std;

    Monster::Monster(const string& name, int hp) : Entity(name), maxHp(hp), hp(hp), alive(true) {}

    void Monster::decreaseHp(int amount) {
        if (!alive) return;
        hp -= amount;
        if (hp <= 0) {
            hp = 0;
            alive = false;
        }
    }
    void Monster::increaseHp(int amount) {
        if (!alive) return;
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

#include <windows.h>
#include <iostream>
    using namespace std;

    void Monster::printBar() const {
        int width = 50;
        int filled = static_cast<int>((double)hp / maxHp * width);
        double ratio = (double)hp / maxHp;

        // 콘솔 정보 가져오기
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // 이름 출력 (중앙 정렬)
        int namePad = (consoleWidth - name.size()) / 2;
        COORD namePos = { static_cast<SHORT>(namePad), csbi.dwCursorPosition.Y };
        SetConsoleCursorPosition(hConsole, namePos);
        cout << name << endl;

        // 체력 수치 출력 (중앙 정렬)
        string hpText = to_string(hp) + "/" + to_string(maxHp);
        int hpTextLen = hpText.length();
        int hpLineLen = width + 2; // [ + bar + ]
        int hpPad = (consoleWidth - hpLineLen) / 2;

        COORD hpPos = { static_cast<SHORT>(hpPad), static_cast<SHORT>(namePos.Y + 1) };
        SetConsoleCursorPosition(hConsole, hpPos);

        cout << "[";
        int hpStart = (width - hpTextLen) / 2;
        for (int i = 0; i < width; ++i) {
            if (i == hpStart) {
                SetConsoleTextAttribute(hConsole, 12); // 빨간색
                cout << hpText;
                i += hpTextLen - 1;
                SetConsoleTextAttribute(hConsole, 7);  // 복원
            }
            else {
                cout << " ";
            }
        }
        cout << "]" << endl;

        // 체력바 출력 (중앙 정렬)
        COORD barPos = { static_cast<SHORT>(hpPad), static_cast<SHORT>(hpPos.Y + 1) };
        SetConsoleCursorPosition(hConsole, barPos);
        cout << "[";

        for (int i = 0; i < width; ++i) {
            if (i < filled) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "■";
            }
            else {
                SetConsoleTextAttribute(hConsole, 8);
                cout << "·";
            }
        }

        SetConsoleTextAttribute(hConsole, 7); // 복원
        cout << "]" << endl;
    }



    bool Monster::isAlive() const { return alive; }
    int Monster::getHp() const { return hp; }
    void Monster::kill() { alive = false; }
    void Monster::info() const { printBar(); }
    string Monster::getName() const { return name; }

}