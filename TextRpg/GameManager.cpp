#include "pch.h"
#include "GameManager.h"
#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "Dungeon.h"
#include "Shop.h"
// static�� Ŭ���� �ܺο��� ���ǰ���
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
	// �÷��̾� ����
	_player = Player::getInstance();

	_dungeons.push(new NormalDungeon()); // ù��° ����
	_dungeons.push(new HardDungeon()); // �ι�° ����
	_dungeons.push(new BossDungeon()); // ������ ����

	_shop = Shop::getInstance();
}

void GameManager::Run()
{
	while (_dungeons.empty() == false)
	{
		// ��������
		Dungeon* dungeon = _dungeons.front(); // queue�� push �� ������ ��������
		_gameManager->EnterDungeon(dungeon); 

		_gameManager->EnterShop(); // ������



		_dungeons.pop(); // ���� Ŭ���� �� �޸� ����  
		delete dungeon;

		if (_player->IsDead())
			break;
	}
	cout << "Game Over" << endl;
}

void GameManager::EnterDungeon(Dungeon* dungeon)
{
	dungeon->Init(); // ���� ����
	BattleManager::getInstance()->StartBattle(dungeon); // ��Ʋ

}

void GameManager::EnterShop()
{
	cout << "Enter Shop" << endl;

	while (true)
	{
		if (_shop->IsShopEmpty())
		{
			cout << "------------------------- " << endl;
			cout << "������ ������ϴ�" << endl;
			cout << "����Ϸ��� �ƹ� Ű�� �����ּ���..." << endl;
			cout << "------------------------- " << endl;

			ConsoleHelper::ClearConsole();
			break;
		}

		_shop->DisplayItem();
		_player->PlayerInfo();

		cout << "�����Ϸ��� ��ǰ ��ȣ �Է�(����� -1) " << endl;
		int input;
		cin >> input;
		if (input == -1)
		{
			system("cls");
			break;
		}

		system("cls");
		// ������ ����
		Item* item =_shop->BuyItem(input);

		// �κ��丮�� ����
		if(item)
			_player->TakeItem(item);

	}
	
	_player->OpenInventory();
}

