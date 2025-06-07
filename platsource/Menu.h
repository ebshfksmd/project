#pragma once
#include <string>
#include "Gacha.h"

namespace Gacha {
    class Menu {
    private:
        int jewels = 160;
        Gacha gacha;
        bool selectedPlane = false;
        bool selectedWeapon = false;

        int ReadInt(const std::string& prompt, int min, int max);

    public:
        Menu();
        int Show();
        void ShowDescription();
        void GachaMenu();
        void ChangeFighter();
        void HandleChangeOrStats();
        bool SpendJewels(int amount);
        void ShowGachaStats();

        bool GetSelectedPlane() const { return selectedPlane; }
        bool GetSelectedWeapon() const { return selectedWeapon; }
        int& GetJewelsRef() { return jewels; }

        void CheatMenu();
    };
}