#include "pch.h"
#include"GameManager.h"
#include"BattleManager.h"
#include <iostream>

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	GameManager* gameManager = GameManager::getInstance();
	BattleManager* battleManager = BattleManager::getInstance();

	gameManager->Run();
	
}
