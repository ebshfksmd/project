#pragma once
#include <vector>
#include <string>
#include "GameLogic.h"

namespace defense {
	void drawScreen(const std::vector<std::vector<Unit*>>& unitMap, const std::vector<Monster>& monsters, int gold, int playerHP, bool gameClear, bool gameOver);
	std::string getAsciiUnit(char type);
	std::string getAsciiMonster(char type);

}