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
	void setup() override;
	void update() override;
	void draw() override;

	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);
	void setPlayer(std::shared_ptr<CharaBase>);

private:
	std::shared_ptr<EnemyAIBase> ai;
	ci::Matrix44f matrix;


	std::shared_ptr<ar::SignPostManager> signpostmanager;
	std::shared_ptr<CharaBase> player;



};

