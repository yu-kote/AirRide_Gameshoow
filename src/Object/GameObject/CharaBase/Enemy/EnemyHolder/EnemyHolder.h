#pragma once
#include "../Enemy.h"
#include "../../CharaBase.h"

class EnemyHolder : public ar::GameObject
{
public:


	//EnemyHolder();

	void setup() override;
	void update() override;
	void draw() override;


	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);
	void setPlayer(std::shared_ptr<CharaBase>);

private:
	std::list<Enemy> enemys;
};

