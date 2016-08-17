#pragma once
#include "../../CharaBase.h"
#include "../../../../../Share/Interface/Interface.h"
#include "cinder/Rand.h"

class EnemyAIBase
{
public:
	EnemyAIBase(CharaBase* _enemy, CharaBase* _player) {
		enemy = _enemy;
		player = _player;
		is_terget = false;
		HP = 2;
		terget_change_count = 0;
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
	void goPositon(ci::Vec3f,float);

	ci::Vec2f aiterget;
	int terget_change_count;

	void changeTarget();
	void tergetMove();

	
};




