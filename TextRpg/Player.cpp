#include "pch.h"
#include "Player.h"
#include "Item.h"
Player* Player::_player = nullptr;

Player* Player::getInstance()
{
	if (_player)
		return _player;
	else
	{
		_player = new Player(100, 20, 5, 10);
		return _player;
	}
}

void Player::PlayerInfo()
{
	cout << "------------------------- " << endl;
	cout << "   << Player Info >>	" << endl << endl;
	cout << "HP : " << _player->GetHp() << endl;
	cout << "Atk : " << _player->GetAtk() << endl;
	cout << "Def : " << _player->GetDef() << endl;
	cout << "Gold : " << _player->GetGold() << endl;
	cout << "------------------------- " << endl;

}

void Player::InstallWeapon(int itemID)
{
	auto it = _inventory.find(itemID);
	if (it != _inventory.end())
	{
		Item* item = it->second;
		if (item) // nullptr check
		{
			if (Weapon* weapon = dynamic_cast<Weapon*>(item)) // weapon�� �ƴҰ�� null�� ��ȯ
			{
				// ���Ⱑ �����Ǿ��ִ� ��� ���� ���� ����
				if (_installed_Weapon)
					DisArmWeapon(_installed_Weapon);

				_installed_Weapon = weapon;
				_atk += _installed_Weapon->GetPlusAtk();
				_inventory.erase(it); // �κ��丮���� ���� ����

			}
			else if(Armor* armor = dynamic_cast<Armor*>(item))
			{
				if(_installed_Armor)
					DisArmWeapon(_installed_Armor);

				_installed_Armor = armor;
				_def += _installed_Armor->GetPlusDef();
				_inventory.erase(it); // �κ��丮���� ���� ����
			}
			else
			{
				cout << "������ �� ���� �������Դϴ�." << endl;
			}
		}
	}
}

void Player::DisArmWeapon(Item* item)
{
	if (item)
	{
		if (Weapon* weapon = dynamic_cast<Weapon*>(item))
		{
			_atk -= weapon->GetPlusAtk(); // ���ݷ� �ʱ�ȭ
			_inventory.insert(make_pair(item->GetItemID(), item)); // �κ��丮�� ���� ����
			_installed_Weapon = nullptr; // ���� ����
		}
		else if (Armor* armor = dynamic_cast<Armor*>(item))
		{
			_def -= armor->GetPlusDef();
			_inventory.insert(make_pair(item->GetItemID(), item));
			_installed_Armor = nullptr;
		}
		else
		{
			cout << "��ȿ���� ���� ����Դϴ�" << endl;
		}
	}
}

void Player::UseItem(int itemID)
{
	auto it = _inventory.find(itemID);
	if (it != _inventory.end())
	{
		Item* item = it->second;
		if (item)
		{
			if (Potion* potion = dynamic_cast<Potion*>(item)) // �����̸� ��
			{
				SetHp(GetHp() + potion->GetHeal());
				cout << "Hp�� " << potion->GetHeal() << "ȸ���Ǿ����ϴ�" << endl<< endl;
				_inventory.erase(it);
			}
			else if (Key* key = dynamic_cast<Key*>(item))
			{
				cout << "Key ���" << endl;
				_inventory.erase(it);
			}
			else
			{
				cout << "��ȿ���� ���� �������Դϴ�" << endl;
			}
		}
	}
}

void Player::TakeItem(Item* item)
{
	_inventory.insert(make_pair(item->GetItemID(), item));
}

void Player::OpenInventory()
{

	while (true)
	{
		PlayerInfo();

		cout << "   << Inventory >>	" << endl << endl;

		if (_inventory.empty())
		{
			cout << "NO ITEM" << endl << endl;
			cout << "����Ϸ��� �ƹ� Ű�� �����ּ���..." << endl;
			cout << "------------------------- " << endl << endl;
			ConsoleHelper::ClearConsole();
			return;
		}

		for (auto& pair : _inventory)
		{
			cout << pair.first << " : " << pair.second->GetItemName() << endl;
		}
		cout << "------------------------- " << endl;
		

		cout << " �������� �����ϼ���(����� -1)" << endl;
		int itemID;
		cin >> itemID;
		system("cls");
		if (itemID == -1)
			break;
		
		Item* item = nullptr;

		auto it = _inventory.find(itemID);
		if (it != _inventory.end())
		{
			item = it->second;

			if (dynamic_cast<Equipment*>(item))
				InstallWeapon(itemID); // ���� ����
			else if (dynamic_cast<Consumable*>(item))
				UseItem(itemID);
		}

	}	
}
