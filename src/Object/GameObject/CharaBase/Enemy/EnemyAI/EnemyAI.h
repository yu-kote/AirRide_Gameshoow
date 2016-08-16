#pragma once
#include "EnemyAIBase.h"
#include "../../../../../Share/Easing/Easing.h"
#include "cinder/Rand.h"


class AILevel1 : public EnemyAIBase
{
public:
	AILevel1(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:
	ci::Vec2f aiterget;
	int terget_change_count;


};



class AILevel2 : public EnemyAIBase
{
public:
	AILevel2(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:

};




class AILevel3 : public EnemyAIBase
{
public:
	AILevel3(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:

};




class AILevel4 : public EnemyAIBase
{
public:
	AILevel4(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:

};


