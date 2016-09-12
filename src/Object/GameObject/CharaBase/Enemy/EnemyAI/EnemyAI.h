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
	

};



class AILevel2 : public EnemyAIBase
{
public:
	AILevel2(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:
	int roll_count;
};




class AILevel3 : public EnemyAIBase
{
public:
	AILevel3(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:
	int avoid_count;
};




class AILevel4 : public EnemyAIBase
{
public:
	AILevel4(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:
	int avoid_count;
};


class AITutorial : public EnemyAIBase
{
public:
	AITutorial(CharaBase*, CharaBase*);
	void stert() override;

	void update() override;

private:


};