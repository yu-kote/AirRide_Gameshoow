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
class AILevel2 : public EnemyAIBase
{
public:
	AILevel2(CharaBase*, CharaBase*);
	void update() override;

private:

};
class AILevel3 : public EnemyAIBase
{
public:
	AILevel3(CharaBase*, CharaBase*);
	void update() override;

private:

};
class AILevel4 : public EnemyAIBase
{
public:
	AILevel4(CharaBase*, CharaBase*);
	void update() override;

private:

};


