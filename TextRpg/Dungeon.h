#pragma once

#include <iostream>
using namespace std;

class Monster;

class Dungeon // �߻� Ŭ����
{
public:
	Dungeon(){}
	virtual ~Dungeon() {}

	virtual void Init() = 0;
	virtual void GenerateMonster() = 0; // ���� ��ȯ
	
	vector<Monster*>& GetMonsters() { return _monsters; }
	void Clear() { _isClear = true; }
protected:
	bool _isClear = false;
	vector<Monster*> _monsters;
};

class NormalDungeon : public Dungeon
{
public:
	NormalDungeon() { cout << "NormalDungeon()" << endl; }
	~NormalDungeon() 
	{
		cout << "~NormalDungeon()" << endl;
		for (Monster* monster : _monsters)
			delete monster;
		_monsters.clear();
	}
	virtual void Init();
	virtual void GenerateMonster();

public:
	
};

class HardDungeon : public Dungeon
{
public:
	HardDungeon() { cout << "HardDungeon()" << endl; }
	~HardDungeon()
	{
		cout << "~HardDungeon()" << endl;
		for (Monster* monster : _monsters)
			delete monster;
		_monsters.clear();
	}

	virtual void Init(); // ���� �ʿ�
	virtual void GenerateMonster();

public:
};

class BossDungeon : public Dungeon
{
public:
	BossDungeon() { cout << "BossDungeon()" << endl; }
	~BossDungeon()
	{
		cout << "~BossDungeon()" << endl;
		for (Monster* monster : _monsters)
			delete monster;
		_monsters.clear();
	}

	virtual void Init();
	virtual void GenerateMonster();
public:
};

