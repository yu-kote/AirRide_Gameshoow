#pragma once
#include "../../CharaBase.h"


class EnemyAIBase
{
public:
	EnemyAIBase(CharaBase* _enemy, CharaBase* _player) {
		enemy = _enemy;
		player = _player;
	}
	virtual void update() {};

protected:
	CharaBase* enemy;
	CharaBase* player;

};




