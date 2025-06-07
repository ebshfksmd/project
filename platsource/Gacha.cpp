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
            std::cout << "��ȣ�� �����ϼ���: ";
            if (!(std::cin >> choice)) {
                std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (choice < min || choice > max) {
                std::cout << "���� �� ���ڸ� �Է����ּ���.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }

    void Gacha::ShowGachaMenu() {
        while (true) {
            system("cls");
            std::cout << "\n===== ��í �޴� =====\n";
            std::cout << "���: " << jewels << "��\n";
            if (!currentResults.empty()) {
                std::cout << "\n--- ���� ��í ��� ---\n";
                PrintResults();
                std::cout << "\n�� �̱� Ƚ��: "
                    << (bodyCount + weaponCount)
                    << "ȸ\n";
            }
            std::cout << "\n1. ������ �ٵ� ��í\n2. ���� ���� ��í\n3. ���ư���\n";
            int choice = GetUserInput(1, 3);
            if (choice == 3) { currentResults.clear(); system("cls"); return; }

            while (true) {
                system("cls");
                std::cout << (choice == 1 ? "\n=== ������ �ٵ� ��í ===\n" : "\n=== ���� ���� ��í ===\n");
                std::cout << "���: " << jewels << "��\n";
                if (!currentResults.empty()) {
                    std::cout << "\n--- ���� ��í ��� ---\n";
                    PrintResults();
                    std::cout << "\n�� �̱� Ƚ��: "
                        << (bodyCount + weaponCount)
                        << "ȸ\n";
                }
                std::cout << "\n1. 1ȸ ��í (1 ���)\n2. 10ȸ ��í (10 ���)\n3. ���ư���\n";
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
            if (raw.find("5��") != std::string::npos)
                PrintSpecialMessage(raw);

            if (raw == "��� ���� 4��")   ++star4;
            else if (raw == "���� ���� 3��")    ++star3;
            else if (raw == "�ְ�� 5�� ������") ++star5Plane;
            else if (raw == "5�� ����")         ++star5Weapon;
            else if (raw == "�� 5��")           ++star5Fail;

            currentResults.push_back(raw);
            if (raw == "�ְ�� 5�� ������" || raw == "5�� ����") {
                guarantee = 0; pity = 0;
            }
            else if (raw == "�� 5��") {
                guarantee = 1; pity = 0;
            }
        }
        if (count == 10) {
            bool ok = false;
            for (int i = start; i < (int)currentResults.size(); ++i) {
                auto& r = currentResults[i];
                if (r == "��� ���� 4��" || r.find("5��") != std::string::npos) { ok = true; break; }
            }
            if (!ok && !currentResults.empty()) {
                auto& last = currentResults.back();
                last = "��� ���� 4��";
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
                if (guaranteed) return "�ְ�� 5�� ������";
                std::uniform_int_distribution<int> f(0, 1);
                return f(rng) ? "�� 5��" : "�ְ�� 5�� ������";
            }
            return "5�� ����";
        }
        else if (r < p + b4) return "��� ���� 4��";
        return "���� ���� 3��";
    }

    void Gacha::PrintResults() {
        for (auto& i : currentResults) std::cout << "- " << i << "\n";
    }

    void Gacha::PrintSpecialMessage(const std::string& r) {
        if (r.find("5��") != std::string::npos)
            std::cout << "\n***** " << (r == "�� 5��" ? "�ФФФФФ� ���̰� ���һ� �ƽ��� �Ʊ����!!!!!! �� 5���̳׿�~~~ �׷��� 5���ε� �����Ѵٳ� �ФФФФФФ�" : "�����մϴ�! " + r + " ��÷!") << " *****\n";
        system("pause");
    }
}