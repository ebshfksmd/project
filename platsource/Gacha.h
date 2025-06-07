#pragma once
#include <string>
#include <vector>
#include <random>

namespace Gacha {
    class Gacha {
    public:
        Gacha(int& jewels);
        void ShowGachaMenu();

        int GetBodyCount() const { return bodyCount; }
        int GetWeaponCount() const { return weaponCount; }
        int GetStar3() const { return star3; }
        int GetStar4() const { return star4; }
        int GetStar5Plane() const { return star5Plane; }
        int GetStar5Weapon() const { return star5Weapon; }
        int GetStar5Fail() const { return star5Fail; }

    private:
        int& jewels;
        int pityBody, guardBody;
        int pityWeapon, guardWeapon;
        int bodyCount, weaponCount;
        int star3, star4;
        int star5Plane, star5Weapon, star5Fail;
        std::mt19937 rng;
        std::vector<std::string> currentResults;

        void RunGacha(int count, bool isBody);
        std::string Roll(int pity, bool isBody, bool guaranteed);
        void PrintResults();
        void PrintSpecialMessage(const std::string& result);
        int GetUserInput(int min, int max);
    };
}