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
                std::cout << "�߸��� �Է��Դϴ� (" << min << "~" << max << ").\n";
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
            std::cout << "\n===== ���� ���� �޴� =====\n\n";
            std::cout << "1. ���� ����\n";
            std::cout << "2. ���� ���� ����\n";
            std::cout << "3. ��í (���� ���: " << jewels << "��)\n";
            std::cout << "4. ������ ���� �� ��í ��� Ȯ��\n";
            std::cout << "5. ���� ����\n";

            std::string input;
            std::cout << "��ȣ�� �����ϼ���: ";
            std::cin >> input;
            if (input == "ġƮŰ") {
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
        std::cout << "\n1. ������ ����\n2. ��í ��� Ȯ��\n";
        int sub = ReadInt("����: ", 1, 2);
        if (sub == 1) ChangeFighter();
        else ShowGachaStats();
        system("pause");
    }

    void Menu::ShowDescription() {
        std::cout << "\n���� ����:\n";
        std::cout << "W/S Ű�� �����⸦ ��/�Ʒ��� �̵��ϼ���.\n";
        std::cout << "�����̽��ٷ� �Ѿ��� �߻��� ���� �����ϼ���.\n";
        std::cout << "d Ű�� 5�� ������ ��ų�� ����Ͽ� ���� ��� ������ �� �ֽ��ϴ� (��ٿ� 10��).\n";
        std::cout << "���� �浹�ϸ� ������ ����˴ϴ�.\n\n";
    }

    void Menu::GachaMenu() {
        gacha.ShowGachaMenu();
    }

    void Menu::ChangeFighter() {
        std::cout << "\n=== ������/���� ���� ===\n";
        std::cout << "������ ����:\n1. �⺻ ������\n";
        if (gacha.GetStar5Plane() > 0) std::cout << "2. 5�� ������\n";
        int pChoice = 1;
        if (gacha.GetStar5Plane() > 0) pChoice = ReadInt("����: ", 1, 2);
        bool prev = selectedPlane;
        selectedPlane = (pChoice == 2);
        if (selectedPlane && !prev) {
            std::cout << "�����մϴ�. �ʻ�� d�� Ȱ��ȭ �Ǿ����ϴ�. �ʻ��: ��Ÿ�� 10��, ���� � ���̵� ��ġ�� �� �����⸦ �����մϴ�.\n";
        }

        std::cout << "���� ����:\n1. �⺻ ����\n";
        if (gacha.GetStar5Weapon() > 0) std::cout << "2. 5�� ����\n";
        int wChoice = 1;
        if (gacha.GetStar5Weapon() > 0) wChoice = ReadInt("����: ", 1, 2);
        selectedWeapon = (wChoice == 2);
    }

    bool Menu::SpendJewels(int amount) {
        if (jewels >= amount) { jewels -= amount; return true; }
        std::cout << "����� �����մϴ�.\n";
        return false;
    }

    void Menu::ShowGachaStats() {
        std::cout << "\n=== ��í ��� ===\n";
        std::cout << "3��: " << gacha.GetStar3() << "��\n";
        std::cout << "4��: " << gacha.GetStar4() << "��\n";
        std::cout << "5�� ������: " << gacha.GetStar5Plane() << "��\n";
        std::cout << "5�� ����: " << gacha.GetStar5Weapon() << "��\n";
    }

    void Menu::CheatMenu() {
        int delta;
        std::cout << "\nġƮŰ ���: ��� ������ �����ϼ���: ";
        while (!(std::cin >> delta)) {
            std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        jewels = delta;
        std::cout << "���� ���: " << jewels << "��\n";
        system("pause");
    }
}