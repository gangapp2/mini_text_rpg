#pragma once

class Player;
class Monster;
class Dungeon;
class Shop;

class GameManager
{
private:
	GameManager() {}
public:
	static GameManager* getInstance(); // singleton

	void Init(); // ������� �ʱ�ȭ
	void Run(); // ���� ����

	void EnterDungeon(Dungeon* dungeon);
	void EnterShop();

 private:
	static GameManager* _gameManager;
	Player* _player;
	queue<Dungeon*> _dungeons;
	Shop* _shop;
};



