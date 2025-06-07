#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <locale>
#include "GameBase.h"
namespace movebox{

    const int MAP_SIZE = 20;
    const int STAGES = 3;
    using namespace std;

    class movebox : public GameBase{
        
        char map[MAP_SIZE][MAP_SIZE];
        pair<int, int> player;
        vector<pair<int, int>> boxes;
        vector<pair<int, int>> goals;
        int currentStage = 1;
        bool cheatMode = false;

        void DrawMap() {
            system("cls");
            for (int y = 0; y < MAP_SIZE; ++y) {
                for (int x = 0; x < MAP_SIZE; ++x) {
                    if (player.first == y && player.second == x) {
                        cout << "@";
                    }
                    else {
                        bool printed = false;

                        // �ڽ��� ���� ��ħ �켱 üũ
                        for (int i = 0; i < boxes.size(); ++i) {
                            if (boxes[i].first == y && boxes[i].second == x) {
                                bool isGoal = false;
                                for (auto& g : goals) {
                                    if (g.first == y && g.second == x) {
                                        cout << "*";
                                        isGoal = true;
                                        break;
                                    }
                                }
                                if (!isGoal) {
                                    cout << (cheatMode ? '$' : char('A' + i));
                                }
                                printed = true;
                                break;
                            }
                        }

                        // ���۸� ���
                        if (!printed) {
                            for (int i = 0; i < goals.size(); ++i) {
                                if (goals[i].first == y && goals[i].second == x) {
                                    cout << (cheatMode ? '&' : char('1' + i));
                                    printed = true;
                                    break;
                                }
                            }
                        }

                        // �⺻ �� Ÿ�� ���
                        if (!printed) {
                            cout << map[y][x];
                        }
                    }
                }
                cout << "\n";
            }

            cout << "\n[WASD] �̵� | [Q] ����\n";
            if (cheatMode) {
                cout << "ġƮ���: �������� ������ ��� ���� ���� �� �ֽ��ϴ�. $ -> &\n";
            }
            else {
                cout << "���� ����: �ڽ��� ���ĺ�(A, B, C...) ������� ���� ����(1, 2, 3...)�� ��������!\n";
            }
        }

        bool IsValid(int y, int x) {
            return y >= 0 && y < MAP_SIZE && x >= 0 && x < MAP_SIZE && map[y][x] != '#';
        }

        void InitStage(int stage) {
            srand(time(0) + stage);
            for (int y = 0; y < MAP_SIZE; ++y)
                for (int x = 0; x < MAP_SIZE; ++x)
                    map[y][x] = ' ';

            // ��
            for (int i = 0; i < MAP_SIZE; ++i) {
                map[0][i] = '#';
                map[MAP_SIZE - 1][i] = '#';
                map[i][0] = '#';
                map[i][MAP_SIZE - 1] = '#';
            }

            int boxCount = stage + 2;
            boxes.clear();
            goals.clear();

            // �÷��̾� ��ġ
            do {
                player = { rand() % MAP_SIZE, rand() % MAP_SIZE };
            } while (map[player.first][player.second] == '#');

            // �ڽ� ��ġ
            while (boxes.size() < boxCount) {
                int y = rand() % (MAP_SIZE - 2) + 1;
                int x = rand() % (MAP_SIZE - 2) + 1;
                if (map[y][x] == ' ') {
                    bool nearWall = map[y + 1][x] == '#' || map[y - 1][x] == '#' || map[y][x + 1] == '#' || map[y][x - 1] == '#';
                    bool overlap = (make_pair(y, x) == player);
                    for (auto& b : boxes)
                        if (b == make_pair(y, x)) overlap = true;
                    if (!nearWall && !overlap) {
                        boxes.push_back({ y, x });
                    }
                }
            }

            // ���� ��ġ
            while (goals.size() < boxCount) {
                int y = rand() % (MAP_SIZE - 2) + 1;
                int x = rand() % (MAP_SIZE - 2) + 1;
                pair<int, int> pos = { y, x };
                if (map[y][x] == ' ' && pos != player && find(boxes.begin(), boxes.end(), pos) == boxes.end()) {
                    goals.push_back(pos);
                }
            }
        }

        bool CheckClear() {
            if (cheatMode) {
                for (auto& goal : goals) {
                    if (find(boxes.begin(), boxes.end(), goal) == boxes.end())
                        return false;
                }
            }
            else {
                for (int i = 0; i < boxes.size(); ++i) {
                    if (boxes[i] != goals[i])
                        return false;
                }
            }
            return true;
        }

        void MovePlayer(char dir) {
            int dy = 0, dx = 0;
            if (dir == 'w') dy = -1;
            else if (dir == 's') dy = 1;
            else if (dir == 'a') dx = -1;
            else if (dir == 'd') dx = 1;
            else return;

            int ny = player.first + dy;
            int nx = player.second + dx;

            if (!IsValid(ny, nx)) return;

            for (int i = 0; i < boxes.size(); ++i) {
                if (boxes[i].first == ny && boxes[i].second == nx) {
                    int nny = ny + dy;
                    int nnx = nx + dx;
                    if (!IsValid(nny, nnx)) return;
                    for (auto& b : boxes) {
                        if (b == make_pair(nny, nnx)) return;
                    }
                    boxes[i] = { nny, nnx };
                    break;
                }
            }

            player = { ny, nx };
        }
        void Init() {
            system("cls");
        }

        void Play() {
            setlocale(LC_ALL, "");

            cout << "������ �����մϴ�. ġƮŰ�� �Է��Ϸ��� 'ġƮŰ'�� �Է��ϼ���. �׳� Enter �� �Ϲ� ��� ����.\n";
            string inputStart;
            getline(cin, inputStart);
            if (inputStart.find("ġƮŰ") != string::npos) {
                cheatMode = true;
            }

            while (currentStage <= STAGES) {
                InitStage(currentStage);
                while (true) {
                    DrawMap();
                    if (CheckClear()) {
                        cout << " �������� " << currentStage << " Ŭ����!\n";
                        system("pause");
                        currentStage++;
                        break;
                    }

                    char input;
                    cin >> input;
                    if (input == 'q' || input == 'Q') {
                        cout << "������ �����մϴ�.\n";
                        return;
                    }
                    MovePlayer(tolower(input));
                }
            }
        }

        void End() {};

    };

};