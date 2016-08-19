#pragma once
#include "../CharaBase.h"
#include "../../SignPost/SignPostManager.h"
#include "EnemyAI/EnemyAIBase.h"
#include "EnemyAI/EnemyAI.h"
#include "../Player/Player.h"



class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();
	void update() override;
	void draw() override;

	void setPlayer(std::shared_ptr<CharaBase>);
	void setTarget(const bool&);
	bool isEnd();

	template<class T>
	void setAI();
	void inObstacleArea();


private:
	void damage();
	std::shared_ptr<EnemyAIBase> ai;
	std::shared_ptr<CharaBase> player;
	bool is_hit;
};

template<class T>
void Enemy::setAI()
{
	ai = std::make_shared<T>(T(static_cast<CharaBase*>(this), player.get()));
	ai->stert();
}
