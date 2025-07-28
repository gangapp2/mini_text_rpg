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
			if (Weapon* weapon = dynamic_cast<Weapon*>(item)) // weapon이 아닐경우 null을 반환
			{
				// 무기가 장착되어있는 경우 기존 무기 해제
				if (_installed_Weapon)
					DisArmWeapon(_installed_Weapon);

				_installed_Weapon = weapon;
				_atk += _installed_Weapon->GetPlusAtk();
				_inventory.erase(it); // 인벤토리에서 무기 해제

			}
			else if(Armor* armor = dynamic_cast<Armor*>(item))
			{
				if(_installed_Armor)
					DisArmWeapon(_installed_Armor);

				_installed_Armor = armor;
				_def += _installed_Armor->GetPlusDef();
				_inventory.erase(it); // 인벤토리에서 무기 해제
			}
			else
			{
				cout << "장착할 수 없는 아이템입니다." << endl;
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
			_atk -= weapon->GetPlusAtk(); // 공격력 초기화
			_inventory.insert(make_pair(item->GetItemID(), item)); // 인벤토리에 무기 넣음
			_installed_Weapon = nullptr; // 장착 해제
		}
		else if (Armor* armor = dynamic_cast<Armor*>(item))
		{
			_def -= armor->GetPlusDef();
			_inventory.insert(make_pair(item->GetItemID(), item));
			_installed_Armor = nullptr;
		}
		else
		{
			cout << "유효하지 않은 장비입니다" << endl;
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
			if (Potion* potion = dynamic_cast<Potion*>(item)) // 포션이면 힐
			{
				SetHp(GetHp() + potion->GetHeal());
				cout << "Hp가 " << potion->GetHeal() << "회복되었습니다" << endl<< endl;
				_inventory.erase(it);
			}
			else if (Key* key = dynamic_cast<Key*>(item))
			{
				cout << "Key 사용" << endl;
				_inventory.erase(it);
			}
			else
			{
				cout << "유효하지 않은 아이템입니다" << endl;
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
			cout << "계속하려면 아무 키나 눌러주세요..." << endl;
			cout << "------------------------- " << endl << endl;
			ConsoleHelper::ClearConsole();
			return;
		}

		for (auto& pair : _inventory)
		{
			cout << pair.first << " : " << pair.second->GetItemName() << endl;
		}
		cout << "------------------------- " << endl;
		

		cout << " 아이템을 선택하세요(종료는 -1)" << endl;
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
				InstallWeapon(itemID); // 무기 장착
			else if (dynamic_cast<Consumable*>(item))
				UseItem(itemID);
		}

	}	
}
