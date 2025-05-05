#include "GameManager.h"
#include "simplegame.h"
#include "simplegame2.h"
#include "conio.h"

void GameManager::Init() {
    Games.push_back(new SimpleGame());
    Games.push_back(new SimpleGame2());
}

void GameManager::start() {
    Games[currentGameIndex]->Init();
}

void GameManager::End() {
    Games[currentGameIndex]->End();
}

void GameManager::SelectGame(int index) {
    currentGameIndex = index;
}
