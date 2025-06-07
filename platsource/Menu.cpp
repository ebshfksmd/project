#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

namespace Gacha {
    Menu::Menu()
        : gacha(jewels) {
    }

    int Menu::ReadInt(const std::string& prompt, int min, int max) {
        int val;
        while (true) {
            std::cout << prompt;
            if (!(std::cin >> val) || val < min || val > max) {
                std::cout << "잘못된 입력입니다 (" << min << "~" << max << ").\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        return val;
    }

    int Menu::Show() {
        while (true) {
            system("cls");
            std::cout << "\n===== 슈팅 게임 메뉴 =====\n\n";
            std::cout << "1. 게임 설명\n";
            std::cout << "2. 슈팅 게임 시작\n";
            std::cout << "3. 가챠 (현재 쥬얼: " << jewels << "개)\n";
            std::cout << "4. 전투기 변경 및 가챠 기록 확인\n";
            std::cout << "5. 게임 종료\n";

            std::string input;
            std::cout << "번호를 선택하세요: ";
            std::cin >> input;
            if (input == "치트키") {
                CheatMenu();
                continue;
            }
            int choice;
            try { choice = std::stoi(input); }
            catch (...) { continue; }
            if (choice >= 1 && choice <= 5) return choice;
        }
    }

    void Menu::HandleChangeOrStats() {
        system("cls");
        std::cout << "\n1. 전투기 변경\n2. 가챠 기록 확인\n";
        int sub = ReadInt("선택: ", 1, 2);
        if (sub == 1) ChangeFighter();
        else ShowGachaStats();
        system("pause");
    }

    void Menu::ShowDescription() {
        std::cout << "\n게임 설명:\n";
        std::cout << "W/S 키로 전투기를 위/아래로 이동하세요.\n";
        std::cout << "스페이스바로 총알을 발사해 적을 격추하세요.\n";
        std::cout << "d 키로 5성 전투기 스킬을 사용하여 적을 즉시 제거할 수 있습니다 (쿨다운 10초).\n";
        std::cout << "적과 충돌하면 게임이 종료됩니다.\n\n";
    }

    void Menu::GachaMenu() {
        gacha.ShowGachaMenu();
    }

    void Menu::ChangeFighter() {
        std::cout << "\n=== 전투기/무기 변경 ===\n";
        std::cout << "전투기 선택:\n1. 기본 전투기\n";
        if (gacha.GetStar5Plane() > 0) std::cout << "2. 5성 전투기\n";
        int pChoice = 1;
        if (gacha.GetStar5Plane() > 0) pChoice = ReadInt("선택: ", 1, 2);
        bool prev = selectedPlane;
        selectedPlane = (pChoice == 2);
        if (selectedPlane && !prev) {
            std::cout << "축하합니다. 필살기 d가 활성화 되었습니다. 필살기: 쿨타임 10초, 전장 어떤 곳이든 위치한 적 전투기를 격추합니다.\n";
        }

        std::cout << "무기 선택:\n1. 기본 무기\n";
        if (gacha.GetStar5Weapon() > 0) std::cout << "2. 5성 무기\n";
        int wChoice = 1;
        if (gacha.GetStar5Weapon() > 0) wChoice = ReadInt("선택: ", 1, 2);
        selectedWeapon = (wChoice == 2);
    }

    bool Menu::SpendJewels(int amount) {
        if (jewels >= amount) { jewels -= amount; return true; }
        std::cout << "쥬얼이 부족합니다.\n";
        return false;
    }

    void Menu::ShowGachaStats() {
        std::cout << "\n=== 가챠 기록 ===\n";
        std::cout << "3성: " << gacha.GetStar3() << "개\n";
        std::cout << "4성: " << gacha.GetStar4() << "개\n";
        std::cout << "5성 전투기: " << gacha.GetStar5Plane() << "개\n";
        std::cout << "5성 무기: " << gacha.GetStar5Weapon() << "개\n";
    }

    void Menu::CheatMenu() {
        int delta;
        std::cout << "\n치트키 모드: 쥬얼 갯수를 조정하세요: ";
        while (!(std::cin >> delta)) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        jewels = delta;
        std::cout << "현재 쥬얼: " << jewels << "개\n";
        system("pause");
    }
}