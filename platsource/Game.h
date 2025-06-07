#pragma once
#include <vector>
#include <chrono>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

namespace Gacha {
    class Game {
    private:
        Player player;
        Enemy enemy;
        std::vector<Bullet> bullets;
        int fireCooldown;
        const int fireRate;
        const int speed;
        char input;
        int lives;
        bool gameOver;
        int kills;
        bool has5Plane;
        bool has5Weapon;
        int& jewels;
        std::chrono::steady_clock::time_point lastDUse;

        void SpawnBulletLine(int yPos);
        void CheckHit();
        bool PlayerHit();
        bool IsBulletAt(int x, int y);
        void RenderLives();

    public:
        Game(bool use5Plane, bool use5Weapon, int& jewelsRef);
        void Init();
        void Input();
        void Update();
        void Render();
        void Run();
        bool IsGameOver();
        void Reset();
    };
}