#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>

namespace Gacha {
    using namespace std;

    Game::Game(bool use5Plane, bool use5Weapon, int& jewelsRef)
        : fireCooldown(0), fireRate(7), speed(75), input('\0'),
        lives(use5Plane ? 5 : 3), gameOver(false), kills(0),
        has5Plane(use5Plane), has5Weapon(use5Weapon),
        jewels(jewelsRef),
        lastDUse(chrono::steady_clock::now() - chrono::seconds(10)) {
        bullets.resize(100);
    }

    void Game::Init() {
        system("cls");
        srand((unsigned int)time(nullptr));
        enemy.NewEnemy();
        CONSOLE_CURSOR_INFO cci;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
        cci.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    }

    void Game::SpawnBulletLine(int yPos) {
        for (auto& b : bullets) {
            if (!b.active) {
                b.x = Player::x + 4;
                b.y = max(1, min(17, yPos));
                b.active = true;
                break;
            }
        }
    }

    void Game::Input() {
        if (_kbhit()) input = _getch(); else input = '\0';
    }

    void Game::Update() {
        enemy.Move();
        for (auto& b : bullets) if (b.active) b.Move();
        if (fireCooldown > 0) fireCooldown--;
        switch (tolower(input)) {
        case 'w': player.MoveUp(); break;
        case 's': player.MoveDown(); break;
        case ' ':
            if (fireCooldown == 0) {
                if (has5Weapon) {
                    SpawnBulletLine(player.y);
                    SpawnBulletLine(player.y - 1);
                    SpawnBulletLine(player.y + 1);
                }
                else {
                    SpawnBulletLine(player.y);
                }
                fireCooldown = fireRate;
            }
            break;
        case 'd':
            if (has5Plane) {
                auto now = chrono::steady_clock::now();
                if (now - lastDUse >= chrono::seconds(10)) {
                    kills++;       jewels++;
                    enemy.NewEnemy();
                    lastDUse = now;
                }
            }
            break;
        case 'q': exit(0);
        }
        input = '\0';
        CheckHit();
    }

    void Game::CheckHit() {
        if (enemy.x == -1 || PlayerHit()) {
            lives--;
            if (lives <= 0) { gameOver = true; return; }
            enemy.NewEnemy();
            player = Player();
        }
        for (auto& b : bullets) if (b.active) {
            if (b.y == enemy.y && b.x >= enemy.x && b.x <= enemy.x + 2) {
                kills++;   jewels++;
                enemy.NewEnemy();
                b.active = false;
            }
        }
    }

    bool Game::PlayerHit() {
        if (enemy.x == Player::x + 2 && enemy.y == player.y + 1) return true;
        if (enemy.x == Player::x + 1 && (enemy.y == player.y || enemy.y == player.y + 2)) return true;
        if (enemy.x == Player::x - 1 && (enemy.y == player.y + 3 || enemy.y == player.y - 1)) return true;
        return false;
    }

    bool Game::IsBulletAt(int x, int y) {
        for (auto& b : bullets) if (b.active && b.x == x && b.y == y) return true;
        return false;
    }

    void Game::RenderLives() {
        cout << "목숨: ";
        for (int i = 0; i < (has5Plane ? 5 : 3); ++i) cout << (i < lives ? "O " : "X ");
        cout << "    처치: " << kills << "\n";
    }

    void Game::Render() {
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        string buff;
        for (int y = 0; y < 19; ++y) {
            for (int x = 0; x < 34; ++x) {
                if (y == 0 || y == 18) buff += "__";
                else if (y == player.y && (x == Player::x || x == Player::x + 1)) buff += (x == Player::x ? "ㅁ" : ">");
                else if (IsBulletAt(x, y)) buff += "==";
                else if (x >= enemy.x && x <= enemy.x + 2 && y == enemy.y) buff += (x == enemy.x ? "<" : "x");
                else buff += "  ";
            }
            buff += "\n";
        }
        buff += "\n";
        cout << buff;
        RenderLives();
        if (has5Plane) {
            auto now = chrono::steady_clock::now();
            int elapsed = (int)chrono::duration_cast<chrono::seconds>(now - lastDUse).count();
            int remain = 10 - elapsed;
            if (remain > 0)
                std::cout << "필살기 대기시간: " << remain << "초\n";
            else
                std::cout << "필살기 사용 가능 (d)\n";
        }
    }

    void Game::Run() {
        Init();
        while (!gameOver) {
            Input(); Update(); Render();
            this_thread::sleep_for(chrono::milliseconds(speed));
        }
    }

    bool Game::IsGameOver() { return gameOver; }

    void Game::Reset() {
        player = Player();
        enemy.NewEnemy();
        bullets.clear(); bullets.resize(100);
        lives = has5Plane ? 5 : 3;
        gameOver = false;
        kills = 0;
        lastDUse = chrono::steady_clock::now() - chrono::seconds(10);
    }

}