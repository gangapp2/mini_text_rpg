#pragma once
class BattleManager
{
private:
	BattleManager() {}
public:
	static BattleManager* getInstance();
	void Init();

	void StartBattle(Dungeon* dungeon);
	void BattleInfo(Monster* monster);
	void PlayerAttack(Monster* monster);
	void MonsterAttack(Monster* monster);

private:
	static BattleManager* _battleManager;
	Player* _player;
};

