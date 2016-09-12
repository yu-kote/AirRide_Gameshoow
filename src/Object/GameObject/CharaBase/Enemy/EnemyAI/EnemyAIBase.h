#pragma once
#include "../../CharaBase.h"
#include "../../../../../Share/Interface/Interface.h"
#include "../../../../../Share/Easing/Easing.h"
#include "cinder/Rand.h"

class EnemyAIBase
{
public:
	EnemyAIBase(CharaBase* _enemy, CharaBase* _player) {
		enemy = _enemy;
		player = _player;
		is_terget = false;
		HP = 1;
		terget_change_count = 0;
	}
	virtual void stert() {};
	virtual void update() {};
	virtual void go() { c_Easing::start(enemy->transform.position.z); };

	void setTerget(const bool&);
	bool getTerget();

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
	
	void tergetMotion(int);
	void changeTarget();
	void tergetMove();
	bool avoidPlayerDashByRoll();
	bool avoidPlayerDashByDash();

	bool hit2d();

	
};




