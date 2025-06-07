#include "smitegame.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <numeric>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "Sm.h"

#ifdef _WIN32
#include <conio.h>
#define getch _getch
#else
#endif
namespace smite {

    using namespace std;
    using namespace chrono;

    Game::Game() : player("소환사") {
        monsters.emplace_back("전령", 3000);
        monsters.emplace_back("드래곤", 3500);
        monsters.emplace_back("내셔 남작", 4000);
    }

    void Game::start() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        default_random_engine rng(static_cast<unsigned int>(time(nullptr)));

        // ⭐ 치트키 변수 선언
        bool cheatMode = false;
        int customDamageMin = 150, customDamageMax = 250;
        int customSmiteMin = 850, customSmiteMax = 1100;

        uniform_int_distribution<int> healDist(200, 400);

        vector<int> reactionTimes;
        int totalAttempts = 0, successCount = 0;

        while (true) {
            cout << "\n========== 강타 반응속도 미니게임 ==========\n";
            Smiteimg();
            cout << "강타를 이용하여 몬스터를 처치해보세요!\n";
            cout << "빠르게 처치할수록 강한 능력치를 얻습니다!\n";
            cout << "강타의 데미지는 랜덤이며 타이밍에 맞게 Space Bar를 누르면 됩니다.\n";
            cout << "=====================================\n";
            cout << "1. 전령 처치하기(HP : 3000)\n";
            cout << "2. 드래곤 처치하기(HP : 4000)\n";
            cout << "3. 내셔 남작 처치하기(HP : 5000)\n";
            cout << "0. 종료\n";
            cout << "=====================================\n";

            // ⭐ 문자열 입력으로 변경
            cout << "번호를 입력하세요: ";
            string input;
            cin >> input;

            // ⭐ 치트키 감지
            if (input == "치트키") {
                cheatMode = true;
                cout << "[치트 모드 진입]\n";
                cout << "몬스터 피해량 최소값 입력: ";
                cin >> customDamageMin;
                cout << "몬스터 피해량 최대값 입력: ";
                cin >> customDamageMax;
                cout << "스마이트 최소 데미지 입력: ";
                cin >> customSmiteMin;
                cout << "스마이트 최대 데미지 입력: ";
                cin >> customSmiteMax;
                cin.ignore();
                cout << "[치트 설정 완료]\n";
                continue;
            }

            int choice = stoi(input);  // 문자열 숫자로 변환

            if (choice == 0) {
                cout << "게임을 종료합니다.\n";
                break;
            }

            if (choice < 1 || choice > 3) {
                cout << "잘못된 선택입니다. 다시 입력해주세요.\n";
                continue;
            }

            Monster monster = monsters[choice - 1];
            PlaySound(TEXT("전투.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            bool smiteUsed = false;
            bool smiteWindowOpened = false;
            steady_clock::time_point smiteReadyTime;

            // ⭐ 스마이트 범위에 치트 반영
            uniform_int_distribution<int> smiteRange(
                cheatMode ? customSmiteMin : 850,
                cheatMode ? customSmiteMax : 1100
            );
            int smiteDamage = smiteRange(rng);

            // 랜덤 데미지
            thread damageThread([&]() {
                // ⭐ 데미지 범위에 치트 반영
                uniform_int_distribution<int> damageDist(
                    cheatMode ? customDamageMin : 150,
                    cheatMode ? customDamageMax : 250
                );
                while (monster.isAlive()) {
                    this_thread::sleep_for(seconds(1));
                    int dmg = damageDist(rng);
                    monster.decreaseHp(dmg);
                    if (!smiteWindowOpened && monster.getHp() <= smiteDamage) {
                        smiteReadyTime = steady_clock::now();
                        smiteWindowOpened = true;
                    }
                }
                });

            // 랜덤 회복
            thread healThread([&]() {
                while (monster.isAlive()) {
                    this_thread::sleep_for(seconds(4));
                    int heal = healDist(rng);
                    monster.increaseHp(heal);
                }
                });

            while (monster.isAlive() && !smiteUsed) {
                system("cls");

                monster.printBar();
                if (monster.getName() == "드래곤") Dragonimg();
                else if (monster.getName() == "전령") Heraldimg();
                else if (monster.getName() == "내셔 남작") nasherimg();

                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n예상 강타 데미지: " << smiteDamage << "\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout << "[스페이스바 = 강타, I = 정보 확인]\n";

                for (int i = 0; i < 10; ++i) {
                    this_thread::sleep_for(milliseconds(50));
                    if (_kbhit()) break;
                }

                if (_kbhit()) {
                    char key = getch();
                    if (key == ' ') {
                        PlaySound(TEXT("강타.wav"), NULL, SND_FILENAME | SND_ASYNC);

                        auto smiteTime = steady_clock::now();
                        bool success = monster.getHp() <= smiteDamage;
                        totalAttempts++;

                        cout << "\n=============================\n";
                        cout << "  [ 강타 사용됨 ] 데미지: " << smiteDamage << "\n";
                        cout << "=============================\n";

                        if (success) {
                            monster.kill();
                            PlaySound(NULL, 0, 0);
                            cout << "처치 성공!\n";
                            successCount++;
                        }
                        else {
                            monster.decreaseHp(smiteDamage);
                            cout << "처치 실패. 남은 체력: " << monster.getHp() << "\n";
                        }

                        if (smiteWindowOpened) {
                            int elapsedMs = duration_cast<milliseconds>(smiteTime - smiteReadyTime).count();
                            int displayedElapsed = max(0, elapsedMs - 500);
                            reactionTimes.push_back(elapsedMs);
                            string grade;
                            if (displayedElapsed <= 250) grade = "개빠름";
                            else if (displayedElapsed <= 400) grade = "빠름";
                            else if (displayedElapsed <= 600) grade = "보통";
                            else if (displayedElapsed <= 900) grade = "느림";
                            else grade = "많이 느림";

                            cout << "반응 속도: " << displayedElapsed << "ms (" << grade << ")\n";
                        }
                        else {
                            cout << "※ 체력 900 이하가 되기 전에 강타가 시전되었습니다.\n";
                            reactionTimes.push_back(1500);
                        }

                        smiteUsed = true;
                    }
                    else if (key == 'i' || key == 'I') {
                        monster.info();
                        system("pause");
                    }
                }
            }

            damageThread.join();
            healThread.join();
            cout << monster.getName() << " 라운드 종료.\n";
        }
    };
}
