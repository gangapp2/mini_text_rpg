#include "pch.h"
#include "GameManager.h"
#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "Dungeon.h"

BattleManager* BattleManager::_battleManager = nullptr;
BattleManager* BattleManager::getInstance()
{
	if (_battleManager)
		return _battleManager;
	else
	{
		_battleManager = new BattleManager();
		_battleManager->Init();
		return _battleManager;
	}
}

void BattleManager::Init()
{
	_player = Player::getInstance();
}

void BattleManager::StartBattle(Dungeon* dungeon)
{
	vector<Monster*>& monsters = dungeon->GetMonsters();
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr))); // 난수 시드 생성
	std::shuffle(monsters.begin(), monsters.end(), rng); // 추출한 키값을 랜덤으로 섞음


	// 전투
	for (Monster*& monster : monsters)
	{
		BattleInfo(monster);
		// 스피드 비교 후 선공 결정
		bool isPlayerFast = (_player->GetSpeed() > monster->GetSpeed()) ? true : false;
		while (true)
		{
			if (_player->IsDead()) // 사망체크
			{
				cout << "You died" << endl;
				return;
			}

			// 플레이어 선공, hp check
			if (isPlayerFast)
			{
				bool isPlayerRun = false; // 플레이어 도망 여부
				cout << "   << Player Turn >>	" << endl<<endl;
				cout << "1 공격 2 인벤토리 3 도망" << endl<<endl;
				cout << "------------------------- " << endl;


				int input;
				cin >> input;

				system("cls");
	

				switch (input)
				{
				case 1:
					BattleInfo(monster);
					cout << "   << Battle ing... >>	" << endl << endl;
					PlayerAttack(monster);
					break;
				case 2:
					BattleInfo(monster);
					_player->OpenInventory();
					break;
				case 3:
					isPlayerRun = true;
					break;
				default:
					cout << "잘못된 키 입니다" << endl;
				}
				
				if (isPlayerRun)
				{
					system("cls");
					cout << "플레이어는 도망쳤다!!" << endl;
					break;
				}

				if (monster->IsDead()) // 사망체크
				{
					cout << monster->GetMonsterName() << " is dead" << endl;
					_player->TakeGold(monster->GetGold());
					cout << "Player get " << monster->GetGold() << " Gold " << endl;
					cout << "계속하려면 아무키나 눌러주세요..." << endl << endl;
					cout << "------------------------- " << endl;

					int input;
					cin >> input;
					system("cls");
					break;
				}

				MonsterAttack(monster);
				cout << "------------------------- " << endl << endl;
			}
			else
			{
				if (monster->IsDead()) // 사망체크
				{
					cout << monster->GetMonsterName() << " is dead" << endl;
					_player->TakeGold(monster->GetGold());
					cout << "Player get " << monster->GetGold() << " Gold " << endl;
					break;
				}

				MonsterAttack(monster);

				if (_player->IsDead()) // 사망체크
				{
					cout << "You died" << endl;
					return;
				}

				bool isPlayerRun = false; // 플레이어 도망 여부

				cout << "-----Player turn!!-------" << endl;
				cout << "1 공격 2 인벤토리 3 도망" << endl;
				cout << "------------------------- " << endl;
				int input;
				cin >> input;
				system("cls");
				switch (input)
				{
				case 1:
					PlayerAttack(monster);
					break;
				case 2:
					_player->OpenInventory();
					break;
				case 3:
					isPlayerRun = true;
					break;
				default:
					cout << "잘못된 키 입니다" << endl;
				}

				if (isPlayerRun)
				{
					system("cls");
					break;
				}
			}
		}
	}

	cout << "------------------------- " << endl<< endl;
	cout << "   You Cleared Dungeon!!	" << endl<< endl;
	cout << "계속하려면 아무키나 눌러주세요..." << endl << endl;
	cout << "------------------------- " << endl << endl;
	int input;
	cin >> input;
	system("cls");
}

void BattleManager::BattleInfo(Monster* monster)
{
	cout << "------------------------- " << endl << endl;

	cout << "-Player-" << endl;
	cout << "HP: " << _player->GetHp() << endl;
	cout << "Atk: " << _player->GetAtk() << endl;
	cout << "Def: " << _player->GetDef() << endl;
	cout << "Speed: " << _player->GetSpeed() << endl<< endl;
	
	cout << "-" << monster->GetMonsterName() << "-" << endl;
	cout << "HP: " << monster->GetHp() << endl;
	cout << "Atk: " << monster->GetAtk() << endl;
	cout << "Def: " << monster->GetDef() << endl;
	cout << "Speed: " << monster->GetSpeed() << endl<<endl;
	cout << "------------------------- " << endl << endl;

}

void BattleManager::PlayerAttack(Monster* monster)
{
	cout << "Player Attack" << endl;

	monster->takeDamage(_player->GetAtk()); // 공격 뎀지체크

	cout << monster->GetMonsterName() << " HP : " << monster->GetHp() << endl << endl;
}

void BattleManager::MonsterAttack(Monster* monster)
{
	// 보스몬스터인 경우
	if (Boss* boss = dynamic_cast<Boss*>(monster))
	{
		// hp가 50이하로 떨어진 최초경우 격노상태로 변경
		if (!(boss->isRange()) && boss->GetHp() < boss->GetMaxHp() / 2)
		{
			cout << "Boss get ranged!!" << endl;

			boss->SetRange(true);
			boss->Range();
		}

		int randVal = rand() % 100;

		if (randVal < 15)
		{
			cout << "Boss Critical Attack!!" << endl;

			_player->takeDamage(boss->GetCriticalAtk());

			cout << "Player HP : " << _player->GetHp() << endl << endl;

		}
		else if (randVal < 40)
		{
			cout << "Boss Heal!!" << endl;

			boss->SetHp(boss->GetHeal());

			cout << "Boss HP : " << _player->GetHp() << endl << endl;
		}
		else
		{
			cout << "Boss Attack!!" << endl;

			_player->takeDamage(boss->GetAtk());

			cout << "Player HP : " << _player->GetHp() << endl << endl;

		}

	}

	else
	{
		cout << "Monster Attack!!" << endl;

		_player->takeDamage(monster->GetAtk()); // 공격 뎀지체크

		cout << "Player HP : " << _player->GetHp() << endl << endl;
	}
	
}
