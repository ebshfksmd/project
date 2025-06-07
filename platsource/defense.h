#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GameLogic.h"
#include "GameRender.h"
#include "GameBase.h"

namespace defense {
    using namespace std;

    class defense : public GameBase {
    public:

        int turn = 1;


        bool isPaused;
        int gameSpeed;
        bool firstPauseDraw;

        void Init() {
            unitMap[2][0] = new Unit{ 'K', 10, 3, 3 };
            srand((unsigned)time(0));
            isPaused = false;
            gameSpeed = 1;
            firstPauseDraw = true;
        }

        void Play() {
            while (!gameOver && !gameClear) {
                if (!isPaused) {
                    drawScreen(unitMap, monsters, gold, playerHP, gameClear, gameOver);
                    string speedText = (gameSpeed == 1 ? "> 1배속" : ">> 2배속");
                    cout << "[턴 " << turn << "] s: 상점 | p: 속도 설정 (" << speedText << " | q: 나가기)\n";

                    unitAttack();
                    monsterMove();
                    spawnMonster(turn);
                    if (playerHP <= 0) gameOver = true;
                    ++turn;

                    firstPauseDraw = true;
                }
                else if (firstPauseDraw) {
                    drawScreen(unitMap, monsters, gold, playerHP, gameClear, gameOver);
                    cout << "[일시정지 상태] s: 상점 | p: 속도 설정 ( [II] 일시정지)\n";
                    cout << "게임이 멈췄습니다... \n";
                    firstPauseDraw = false;
                }

                if (_kbhit()) {
                    char c = _getch();
                    if (c == 's') {
                        shop();
                        firstPauseDraw = true;
                        continue;
                    }
                    else if (c == 'p') {
                        drawScreen(unitMap, monsters, gold, playerHP, gameClear, gameOver);
                        cout << "속도 설정 메뉴\n";
                        cout << " q: [II] 일시정지\n w: > 1배속\n e: >> 2배속\n";
                        while (true) {
                            char speedKey = _getch();
                            if (speedKey == 'q') {
                                isPaused = true;
                                break;
                            }
                            else if (speedKey == 'w') {
                                isPaused = false;
                                gameSpeed = 1;
                                break;
                            }
                            else if (speedKey == 'e') {
                                isPaused = false;
                                gameSpeed = 2;
                                break;
                            }
                        }
                        firstPauseDraw = true;
                        continue;
                    }
                    else if (c == 'q') {
                        return;
                    }
                }

                if (isPaused) Sleep(100);
                else if (gameSpeed == 1) Sleep(700);
                else if (gameSpeed == 2) Sleep(300);
            }

            drawScreen(unitMap, monsters, gold, playerHP, gameClear, gameOver);
            cleanupUnits();
        }
        void End() {};
    };
};
