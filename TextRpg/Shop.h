#pragma once

class Item;
class Player;

class Shop
{
public:
	static Shop* getInstance();
	void Init();
	void DisplayItem();
	bool IsShopEmpty();
	Item* BuyItem(int itemID);
	
private:
	static Shop* _shop;
	map<int, Item*> _items;
	Player* _player;
};

