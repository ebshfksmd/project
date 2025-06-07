#include "Gacha.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <random>

namespace Gacha {

    Gacha::Gacha(int& jewelsRef)
        : jewels(jewelsRef),
        pityBody(0), guardBody(0),
        pityWeapon(0), guardWeapon(0),
        bodyCount(0), weaponCount(0),
        star3(0), star4(0),
        star5Plane(0), star5Weapon(0), star5Fail(0),
        rng(static_cast<unsigned>(time(nullptr))) {
    }

    int Gacha::GetUserInput(int min, int max) {
        int choice;
        while (true) {
            std::cout << "번호를 선택하세요: ";
            if (!(std::cin >> choice)) {
                std::cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (choice < min || choice > max) {
                std::cout << "범위 내 숫자를 입력해주세요.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }

    void Gacha::ShowGachaMenu() {
        while (true) {
            system("cls");
            std::cout << "\n===== 가챠 메뉴 =====\n";
            std::cout << "쥬얼: " << jewels << "개\n";
            if (!currentResults.empty()) {
                std::cout << "\n--- 이전 가챠 결과 ---\n";
                PrintResults();
                std::cout << "\n총 뽑기 횟수: "
                    << (bodyCount + weaponCount)
                    << "회\n";
            }
            std::cout << "\n1. 전투기 바디 가챠\n2. 전용 무기 가챠\n3. 돌아가기\n";
            int choice = GetUserInput(1, 3);
            if (choice == 3) { currentResults.clear(); system("cls"); return; }

            while (true) {
                system("cls");
                std::cout << (choice == 1 ? "\n=== 전투기 바디 가챠 ===\n" : "\n=== 전용 무기 가챠 ===\n");
                std::cout << "쥬얼: " << jewels << "개\n";
                if (!currentResults.empty()) {
                    std::cout << "\n--- 누적 가챠 결과 ---\n";
                    PrintResults();
                    std::cout << "\n총 뽑기 횟수: "
                        << (bodyCount + weaponCount)
                        << "회\n";
                }
                std::cout << "\n1. 1회 가챠 (1 쥬얼)\n2. 10회 가챠 (10 쥬얼)\n3. 돌아가기\n";
                int sub = GetUserInput(1, 3);
                if (sub == 3) { currentResults.clear(); system("cls"); break; }
                RunGacha(sub == 1 ? 1 : 10, choice == 1);
            }
        }
    }

    void Gacha::RunGacha(int count, bool isBody) {
        int start = currentResults.size();
        int& pity = isBody ? pityBody : pityWeapon;
        int& guarantee = isBody ? guardBody : guardWeapon;
        int& gCount = isBody ? bodyCount : weaponCount;

        for (int i = 0; i < count && jewels > 0; ++i) {
            --jewels; ++pity; ++gCount;
            bool wasG = (guarantee == 1);
            auto raw = Roll(pity, isBody, wasG);
            if (raw.find("5성") != std::string::npos)
                PrintSpecialMessage(raw);

            if (raw == "기분 좋은 4성")   ++star4;
            else if (raw == "쓸모 없는 3성")    ++star3;
            else if (raw == "최고급 5성 전투기") ++star5Plane;
            else if (raw == "5성 무기")         ++star5Weapon;
            else if (raw == "꽝 5성")           ++star5Fail;

            currentResults.push_back(raw);
            if (raw == "최고급 5성 전투기" || raw == "5성 무기") {
                guarantee = 0; pity = 0;
            }
            else if (raw == "꽝 5성") {
                guarantee = 1; pity = 0;
            }
        }
        if (count == 10) {
            bool ok = false;
            for (int i = start; i < (int)currentResults.size(); ++i) {
                auto& r = currentResults[i];
                if (r == "기분 좋은 4성" || r.find("5성") != std::string::npos) { ok = true; break; }
            }
            if (!ok && !currentResults.empty()) {
                auto& last = currentResults.back();
                last = "기분 좋은 4성";
                --star3; ++star4;
            }
        }
    }

    std::string Gacha::Roll(int pity, bool isBody, bool guaranteed) {
        const double b5 = 0.008, b4 = 0.06;
        double p = pity <= 55 ? b5 : pity < 80 ? b5 + (pity - 55) * (1 - b4 - b5) / 25 : 1;
        std::uniform_real_distribution<double> d(0, 1);
        double r = d(rng);
        if (r < p) {
            if (isBody) {
                if (guaranteed) return "최고급 5성 전투기";
                std::uniform_int_distribution<int> f(0, 1);
                return f(rng) ? "꽝 5성" : "최고급 5성 전투기";
            }
            return "5성 무기";
        }
        else if (r < p + b4) return "기분 좋은 4성";
        return "쓸모 없는 3성";
    }

    void Gacha::PrintResults() {
        for (auto& i : currentResults) std::cout << "- " << i << "\n";
    }

    void Gacha::PrintSpecialMessage(const std::string& r) {
        if (r.find("5성") != std::string::npos)
            std::cout << "\n***** " << (r == "꽝 5성" ? "ㅠㅠㅠㅠㅠㅠ 아이고 맙소사 아쉽다 아까워라!!!!!! 꽝 5성이네요~~~ 그래도 5성인데 축하한다네 ㅠㅠㅠㅠㅠㅠㅋ" : "축하합니다! " + r + " 당첨!") << " *****\n";
        system("pause");
    }
}