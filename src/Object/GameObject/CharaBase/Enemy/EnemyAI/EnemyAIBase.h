#pragma once
#include "../../CharaBase.h"
#include "../../../../../Share/Interface/Interface.h"


class EnemyAIBase
{
public:
	EnemyAIBase(CharaBase* _enemy, CharaBase* _player) {
		enemy = _enemy;
		player = _player;
		is_terget = false;
		HP = 1;
	}
	virtual void stert() {};
	virtual void update() {};
	void setTerget(const bool&);
	int HP;
protected:
	CharaBase* enemy;
	CharaBase* player;
	bool is_terget;

	void outStop();
	void runPositon(ci::Vec3f, float = 1);
	void goPositon(ci::Vec3f);

	
};




