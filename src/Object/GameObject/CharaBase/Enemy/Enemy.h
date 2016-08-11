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

	template<class T>
	void setAI();

private:
	std::shared_ptr<EnemyAIBase> ai;
	std::shared_ptr<CharaBase> player;
};

template<class T>
void Enemy::setAI()
{
	ai = std::make_shared<T>(T(static_cast<CharaBase*>(this), player.get()));
}
