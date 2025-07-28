#pragma once

enum class Rarity
{
	Normal,
	Rare,
	Unique,
};

class Item
{
public:
	Item(string itemName,Rarity itemRarity,int itemPrice)
		: _itemName(itemName),_itemRarity(itemRarity)
		, _itemID(itemIDCounter), _itemPrice(itemPrice){ itemIDCounter++; }
	virtual ~Item(){}
	
	int GetItemID() { return _itemID; }
	int GetItemPrice() { return _itemPrice; }
	string GetItemName() { return _itemName; }

protected:
	static int itemIDCounter;
	int _itemID;
	Rarity _itemRarity;
	string _itemName;
	int _itemPrice;
};

class Equipment : public Item // 장비
{
public:
	Equipment(string itemName, Rarity itemRarity, int itemPrice = 0, int durability = 100)
		: Item(itemName,itemRarity,itemPrice), _durability(durability) { }
	virtual ~Equipment() {}
	int GetDurability() { return _durability; }
protected:
	int _durability; // 내구도
};

class Weapon : public Equipment
{
public:
	Weapon(string itemName, Rarity itemRarity, int itemPrice = 0 ,int durability = 100)
		:Equipment(itemName, itemRarity, itemPrice, durability)
	{
		switch (_itemRarity)
		{
		case Rarity::Normal:
			_plusAtk = 1 + rand() % 5;
			break;

		case Rarity::Rare:
			_plusAtk = 5 + rand() % 5;
			break;

		case Rarity::Unique:
			_plusAtk = 15 + rand() % 15;
			break;
		}
	}
	int GetPlusAtk() { return _plusAtk; }
protected:
	int _plusAtk;
};

class Armor : public Equipment
{
public:
	Armor(string itemName, Rarity itemRarity, int itemPrice = 0, int durability = 100)
		:Equipment(itemName, itemRarity, itemPrice, durability)
	{
		switch (_itemRarity)
		{
		case Rarity::Normal:
			_plusDef = 1 + rand() % 3;
			break;

		case Rarity::Rare:
			_plusDef = 3 + rand() % 3;
			break;

		case Rarity::Unique:
			_plusDef = 5 + rand() % 5;
			break;
		}
	}
	int GetPlusDef() { return _plusDef; }
protected:
	int _plusDef;
};

class Consumable : public Item // 소모품
{
public:
	Consumable(string itemName, Rarity itemRarity, int itemPrice = 0) 
		: Item(itemName, itemRarity, itemPrice) { _used = false; }
	virtual ~Consumable() { }

	bool isUsed() { return _used; }
protected:
	bool _used; // 아이템 사용 여부
};

class Potion : public Consumable
{
public:
	Potion(string itemName, Rarity itemRarity, int itemPrice = 0) 
		: Consumable(itemName, itemRarity,itemPrice)
	{
		switch (_itemRarity)
		{
		case Rarity::Normal:
			_heal = 20;
			break;

		case Rarity::Rare:
			_heal = 50;
			break;

		case Rarity::Unique:
			_heal = 80;
			break;
		}
	}
	int GetHeal() { return _heal; }
protected:
	int _heal;
};

class Key : public Consumable
{
public:
	Key(string itemName, Rarity itemRarity, int itemPrice =0): Consumable(itemName, itemRarity,itemPrice) {}
protected:
};