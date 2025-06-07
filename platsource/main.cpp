#include <iostream>
#include "GameManager.h"
#include "SplashScreen.h"
#include "StageSelector.h"
#include "conio.h"

GameManager* Init() {
	GameManager* gameManager = new GameManager;
	gameManager->Init();
	return gameManager;
}

int main() {
	GameManager* gameManager = Init();

	SplashScreen SplashScreen;
	SplashScreen.Run();

	while (true) {
		StageSelector stageSelector(4);
		stageSelector.Run();
		gameManager->SelectGame(stageSelector.getCurrentStage());
		gameManager->start();
	}

	return 0;
}
