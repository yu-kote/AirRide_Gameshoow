#pragma once
#include "../Enemy.h"
#include "../../CharaBase.h"
#include "../EnemyAI/EnemyAI.h"
#include "../../../SignPost/SignPostManager.h"

class EnemyHolder : public ar::GameObject
{
public:


	EnemyHolder();

	void instance();
	void setup() override;
	void update() override;
	void draw() override;


	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);
	void setPlayer(std::shared_ptr<CharaBase>);
	int getRanking();

private:
	std::vector<Enemy> enemys;

	CharaBase* player;
	ar::SignPostManager* signPostM;
	int target_number;

	void targetChange();

};

