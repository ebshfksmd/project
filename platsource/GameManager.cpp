#include "GameManager.h"
#include "conio.h"
#include "movebox.h"
#include "GachaGame.h"
#include "defense.h"
#include "smite.h"

void GameManager::Init() {
    Games.push_back(new movebox::movebox());
    Games.push_back(new Gacha::GachaGame());
    Games.push_back(new defense::defense());
    Games.push_back(new smite::smite());
}

void GameManager::start() {
    Games[currentGameIndex]->Init();
    Games[currentGameIndex]->Play();
}

void GameManager::End() {
    Games[currentGameIndex]->End();
}

void GameManager::SelectGame(int index) {
    currentGameIndex = index;
}
