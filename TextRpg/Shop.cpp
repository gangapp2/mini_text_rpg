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
		// static ����� ��ü���� ȣ�Ⱑ���ϹǷ� this�����Ͱ� �������� ���� >> Init(); �Ұ�
		// �׷��⿡ �ش� Ŭ������ ������ ������� ���� �� �� ����
		// **��ü �������� Init�� ȣ���ϸ� �����ϱ� ������ ������ �Ű������**
		_shop->Init(); 
		return _shop;
	}
}

void Shop::Init()
{
	_player = Player::getInstance();

	// ������ ����
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
	// ������ ���� 
	auto it = _items.find(itemID);
	if (it != _items.end()) // �������� �����ϴ� ���
	{
		
		// �÷��̾�� ����
		Item* item = it->second;

		// �ݾ� ����
		if (_player->GetGold() - item->GetItemPrice() < 0)
		{
			cout << " �ݾ��� �����մϴ�" << endl;
			return nullptr;
		}

		_player->SetGold(_player->GetGold() - item->GetItemPrice());
		// �������� ����
		_items.erase(it);

		return item;
	}
	else
	{
		return nullptr;
	}
}
