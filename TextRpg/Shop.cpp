#include "pch.h"
#include "Shop.h"
#include "Item.h"
#include "Player.h"
Shop* Shop::_shop = nullptr;

Shop* Shop::getInstance()
{
	if (_shop)
		return _shop;
	else
	{
		_shop = new Shop();
		// static 멤버는 객체없이 호출가능하므로 this포인터가 존재하지 않음 >> Init(); 불가
		// 그렇기에 해당 클래스의 비정적 멤버에는 접근 할 수 없다
		// **객체 생성전에 Init을 호출하면 위험하기 때문에 순서를 신경써주자**
		_shop->Init(); 
		return _shop;
	}
}

void Shop::Init()
{
	_player = Player::getInstance();

	// 아이템 진열
	Item* item1 = new Weapon("Sword", Rarity::Normal, 300);
	Item* item2 = new Armor("Shield", Rarity::Unique, 300);
	Item* item3 = new Potion("Potion", Rarity::Normal, 100);
	Item* item4 = new Weapon("Unique Sword", Rarity::Unique, 300);

	_items.insert(make_pair(item1->GetItemID(), item1));
	_items.insert(make_pair(item2->GetItemID(), item2));
	_items.insert(make_pair(item3->GetItemID(), item3));
	_items.insert(make_pair(item4->GetItemID(), item4));
}

void Shop::DisplayItem()
{
	cout << "------------------------- " << endl;
	cout << "   << Item List >>	" << endl << endl;

	for (auto& pair : _items)
		cout << pair.second->GetItemID() << " " << pair.second->GetItemName() << endl;
	cout << "------------------------- " << endl;

}

bool Shop::IsShopEmpty()
{
	return _items.empty();
}

Item* Shop::BuyItem(int itemID)
{
	// 아이템 구매 
	auto it = _items.find(itemID);
	if (it != _items.end()) // 아이템이 존재하는 경우
	{
		
		// 플레이어에게 전달
		Item* item = it->second;

		// 금액 지불
		if (_player->GetGold() - item->GetItemPrice() < 0)
		{
			cout << " 금액이 부족합니다" << endl;
			return nullptr;
		}

		_player->SetGold(_player->GetGold() - item->GetItemPrice());
		// 상점에서 삭제
		_items.erase(it);

		return item;
	}
	else
	{
		return nullptr;
	}
}
