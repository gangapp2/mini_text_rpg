#pragma once
#include "Character.h"

class Item;

enum class MonsterType
{
	None,
	Human,
	Animal,
	Undead,
};

class Monster : public Character
{
public:
	Monster(int hp, int atk, int def, int speed, int gold = 0) 
		: Character(hp, atk, def, speed, gold), _monsterID(monsterIDCounter) 
	{
		monsterIDCounter++;
	}
	virtual ~Monster(){}

	int GetMonsterID() { return _monsterID; }
	MonsterType GetMonsterType() { return _monsterType; }
	string GetMonsterName() { return _name; }

protected:
	static int monsterIDCounter;
	int _monsterID;
	MonsterType _monsterType = MonsterType::None;
	string _name;
};

class Goblin : public Monster
{
public:
	Goblin(int hp = 20, int atk = 10, int def = 3, int speed = 5, int gold = 100)
		: Monster(hp, atk, def, speed, gold)
	{ 
		_monsterType = MonsterType::Human;
		_name = "Golbin";
	}
};

class Wolf : public Monster
{
public:
	Wolf(int hp = 30, int atk = 15, int def =3, int speed = 8, int gold = 300)
		: Monster(hp, atk, def, speed, gold) {
		_monsterType = MonsterType::Animal;
		_name = "Wolf";
	}
};

class Skeleton : public Monster
{
public:
	Skeleton(int hp = 50, int atk = 20, int def = 3, int speed = 3, int gold = 500)
		: Monster(hp, atk, def, speed, gold) {
		_monsterType = MonsterType::Undead;
		_name = "Skeleton";
	}
};

class Boss : public Monster
{
public:
	Boss(int hp = 150, int atk = 20, int def = 8, int speed = 9, int gold = 2000)
		:Monster(hp, atk, def, speed, gold) { 
		_monsterType = MonsterType::Undead;
		_name = "Boss";
		_heal = 20;
		_maxHp = hp;
		_isRange = false;
	}
	int GetCriticalAtk() { return _atk * 2; } // 치명타
	int GetHeal() { return _heal; } // 회복
	int GetMaxHp() { return _maxHp; }
	void Range() { SetAtk(_atk * 2); SetDef(_def * 2); } // 상태변경
	void SetRange(bool isRange) { _isRange = isRange; }
	bool isRange() { return _isRange; }
private:
	int _maxHp;
	int _heal;
	bool _isRange;
};
