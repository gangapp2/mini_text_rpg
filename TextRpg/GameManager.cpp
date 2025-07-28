#include "pch.h"
#include "GameManager.h"
#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "Dungeon.h"
#include "Shop.h"
// static은 클래스 외부에서 정의가능
GameManager* GameManager::_gameManager = nullptr;

GameManager* GameManager::getInstance()
{
	if (_gameManager) // _gameManager != nullptr
		return _gameManager;
	else
	{
		_gameManager = new GameManager();
		_gameManager->Init();
		return _gameManager;
	}
}

void GameManager::Init()
{
	// 플레이어 생성
	_player = Player::getInstance();

	_dungeons.push(new NormalDungeon()); // 첫번째 던전
	_dungeons.push(new HardDungeon()); // 두번째 던전
	_dungeons.push(new BossDungeon()); // 마지막 던전

	_shop = Shop::getInstance();
}

void GameManager::Run()
{
	while (_dungeons.empty() == false)
	{
		// 던전입장
		Dungeon* dungeon = _dungeons.front(); // queue에 push 된 순으로 던전입장
		_gameManager->EnterDungeon(dungeon); 

		_gameManager->EnterShop(); // 재정비



		_dungeons.pop(); // 던전 클리어 후 메모리 해제  
		delete dungeon;

		if (_player->IsDead())
			break;
	}
	cout << "Game Over" << endl;
}

void GameManager::EnterDungeon(Dungeon* dungeon)
{
	dungeon->Init(); // 던전 입장
	BattleManager::getInstance()->StartBattle(dungeon); // 배틀

}

void GameManager::EnterShop()
{
	cout << "Enter Shop" << endl;

	while (true)
	{
		if (_shop->IsShopEmpty())
		{
			cout << "------------------------- " << endl;
			cout << "상점이 비었습니다" << endl;
			cout << "계속하려면 아무 키나 눌러주세요..." << endl;
			cout << "------------------------- " << endl;

			ConsoleHelper::ClearConsole();
			break;
		}

		_shop->DisplayItem();
		_player->PlayerInfo();

		cout << "구입하려면 상품 번호 입력(종료는 -1) " << endl;
		int input;
		cin >> input;
		if (input == -1)
		{
			system("cls");
			break;
		}

		system("cls");
		// 아이템 구매
		Item* item =_shop->BuyItem(input);

		// 인벤토리에 저장
		if(item)
			_player->TakeItem(item);

	}
	
	_player->OpenInventory();
}

