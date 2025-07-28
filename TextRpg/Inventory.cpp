#include "pch.h"
#include "Inventory.h"
#include "Player.h"
#include "Item.h"
Inventory* Inventory::_inventory = nullptr;
Inventory* Inventory::getInstance()
{
	if (_inventory)
		return _inventory;
	else
	{
		_inventory = new Inventory();
		_inventory->Init();
		return _inventory;
	}
}

void Inventory::Init()
{
	_player = Player::getInstance();

	Item* item1 = new Weapon("Normal Sword", Rarity::Normal);
	Item* item2 = new Armor("Normal Shield", Rarity::Normal);

	_items.insert(make_pair(item1->GetItemID(), item1));
	_items.insert(make_pair(item2->GetItemID(), item2));
}

void Inventory::DisplayItem()
{
	cout << "Open Inventory" << endl;

	cout << "---------Item List---------" << endl;
	for (auto& pair : _items)
	{
		cout << pair.second->GetItemName() << endl;
	}
}

bool Inventory::AddItem(Item* item)
{
	return false;
}

bool Inventory::RemoveItem(Item* item)
{
	return false;
}

Item* Inventory::GetItem(int id)
{
	auto it = _items.find(id);
	if (it != _items.end()) // 아이템을 찾은 경우
	{
		Item* item = it->second;
		_items.erase(it);
		return item;
	}
	else
	{
		return nullptr;
	}
}
