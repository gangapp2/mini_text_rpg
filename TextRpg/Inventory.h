#pragma once

class Player;
class Item;

class Inventory
{
private:

public:
	static Inventory* getInstance();
	void Init();
	void DisplayItem();

	bool AddItem(Item* item);
	bool RemoveItem(Item* item);
	Item* GetItem(int id); // ¹«±â²¨³¿
	
private:
	static Inventory* _inventory;
	map<int, Item*> _items;
	Player* _player;
};

