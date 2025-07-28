#pragma once
class Character
{
public:
	Character(int hp, int atk, int def, int speed, int gold=0)
		: _hp(hp),_atk(atk),_def(def),_speed(speed),_gold(gold){ }

	virtual ~Character() {}

	int GetHp() { return _hp; }
	void SetHp(int hp) { _hp = hp; }

	int GetAtk() { return _atk; }
	void SetAtk(int atk) { _atk = atk; }

	int GetDef() { return _def; }
	void SetDef(int def) { _def = def; }

	int GetSpeed() { return _speed; }
	void SetSpeed(int speed) { _speed = speed; }

	int GetGold() { return _gold; }
	void SetGold(int gold) { _gold = gold; }

	void takeDamage(int damage)
	{
		if (damage - _def <= 0)
			_hp -= 0;
		else
			_hp -= (damage - _def);

		if (_hp <= 0)
			_hp = 0;
	}
	bool IsDead() { return _hp == 0; }

protected:
	int _hp;
	int _atk;
	int _def;
	int _speed; // 선공 여부 결정
	int _gold;
};

