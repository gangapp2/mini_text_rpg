#pragma once
// ����Ҷ��� Character Ŭ������ ���, �����Լ� ����, �޸� ũ�� �� ������ �ʿ���
#include"Character.h" // ���漱���� �ƴ� ��� ���� �ʿ�

class Item;
class Weapon;
class Armor;

class Player : public Character
{
private:
	Player(int hp, int atk, int def, int speed,int gold = 0) 
		: Character(hp, atk, def, speed, gold) { 
		cout<<"Create Player.."<<endl;
		_installed_Armor = nullptr;
		_installed_Weapon = nullptr;
	}
public:
	static Player* getInstance();
	void PlayerInfo();
	void InstallWeapon(int itemID);
	void DisArmWeapon(Item* item);
	void UseItem(int itemID);
	void TakeItem(Item* item);
	void OpenInventory();
	// ��� ȹ��
	void TakeGold(int gold) { _gold += gold; }
	// ������ ����,����
private:
	static Player* _player;
	Weapon* _installed_Weapon;
	Armor* _installed_Armor;
	map<int, Item*> _inventory;
};

