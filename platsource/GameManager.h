#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "GameBase.h"

class GameManager {
private:
    std::vector<GameBase*> Games;
    size_t currentGameIndex = 0;
public:
    void Init();
    void start();
    void End();
    void SelectGame(int index);
};

#endif
