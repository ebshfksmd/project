#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "GameBase.h"

namespace Gacha {
    class GachaGame :public GameBase {
        Menu menu;
        int choice;
        void Init() {
            choice = 0;
        }

        void Play() {
            while (true) {
                choice = menu.Show();

                switch (choice) {
                case 1:
                    menu.ShowDescription();
                    break;
                case 2: {
                    Game game(menu.GetSelectedPlane(), menu.GetSelectedWeapon(), menu.GetJewelsRef());
                    bool gameRunning = true;
                    while (gameRunning) {
                        game.Run();

                        if (game.IsGameOver()) {
                            int postChoice;
                            std::cout << "\n1. �ٽ��ϱ�\n2. ����ȭ������ ���ư���\n����: ";
                            std::cin >> postChoice;
                            if (postChoice == 2) {
                                system("cls");
                                gameRunning = false;
                            }
                            else {
                                game.Reset();
                            }
                        }
                    }
                    break;
                }
                case 3:
                    menu.GachaMenu();
                    break;
                case 4:
                    menu.HandleChangeOrStats();
                    break;
                case 5:
                    std::cout << "������ �����մϴ�.\n";
                    return;
                default:
                    std::cout << "�߸��� �Է��Դϴ�.\n";
                }
            }
            return;
        }
        void End() {};
    };
}