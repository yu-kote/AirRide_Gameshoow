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

	//エネミーの動きを止める関数
	void stop();
	//エネミーたちを動かす関数
	void start();


	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);
	void setPlayer(std::shared_ptr<CharaBase>);
	int getRanking();
	std::vector<Enemy>& getEnemys();

	//アクティブなエネミーだけを返す関数
	std::vector<Enemy*> getActiveEnemys();
	//一応リストバージョンも用意
	std::list<Enemy*> getActiveEnemysList();

	



	bool isEndLasstEnemy();


private:
	std::vector<Enemy> enemys;

	CharaBase* player;
	ar::SignPostManager* signPostM;
	int target_number;

	void targetChange();
	bool is_start;
};

