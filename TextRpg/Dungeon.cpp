#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include "Dungeon.h"

int Monster::monsterIDCounter = 0;

void NormalDungeon::Init()
{
	cout << "Enter Normal Dungeon" << endl;
	GenerateMonster();
}

void NormalDungeon::GenerateMonster()
{
	{
		// Monster(hp,atk,def,speed,id)
		Monster* goblin = new Goblin();
		Monster* wolf = new Wolf();
		Monster* skeleton = new Skeleton();

		_monsters.push_back(goblin);
		_monsters.push_back(wolf);
		_monsters.push_back(skeleton);
	}
}

void HardDungeon::Init()
{
	cout << "Enter Hard Dungeon" << endl;
	GenerateMonster();
}

void HardDungeon::GenerateMonster()
{
	{
		// Monster(hp,atk,def,speed,id)
		Monster* goblin = new Goblin();
		Monster* wolf = new Wolf();
		Monster* skeleton = new Skeleton();
		Monster* goblin2 = new Goblin();
		Monster* wolf2 = new Wolf();
		Monster* skeleton2 = new Skeleton();

		_monsters.push_back(goblin);
		_monsters.push_back(wolf);
		_monsters.push_back(skeleton);
		_monsters.push_back(goblin2);
		_monsters.push_back(wolf2);
		_monsters.push_back(skeleton2);
	}
}

void BossDungeon::Init()
{
	cout << "Enter Boss Dungeon" << endl;
	GenerateMonster();
}

void BossDungeon::GenerateMonster()
{
	{
		// Monster(hp,atk,def,speed,id)
		Monster* boss = new Boss();
		_monsters.push_back(boss);
	}
}