#pragma once
// 상속할때는 Character 클래스의 멤버, 가상함수 여부, 메모리 크기 등 정보가 필요함
#include"Character.h" // 전방선언이 아닌 헤더 포함 필요

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
	// 골드 획득
	void TakeGold(int gold) { _gold += gold; }
	// 아이템 장착,해제
private:
	static Player* _player;
	Weapon* _installed_Weapon;
	Armor* _installed_Armor;
	map<int, Item*> _inventory;
};

