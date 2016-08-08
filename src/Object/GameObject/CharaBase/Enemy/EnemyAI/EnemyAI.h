#pragma once
#include "EnemyAIBase.h"
#include "../../../../../Share/Easing/Easing.h"

class AILevel1 : public EnemyAIBase
{
public:
	AILevel1(CharaBase*, CharaBase*);
	void update() override;


private:

};


