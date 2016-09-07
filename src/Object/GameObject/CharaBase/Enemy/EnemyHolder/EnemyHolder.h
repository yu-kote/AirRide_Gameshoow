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

	//�G�l�~�[�̓������~�߂�֐�
	void stop();
	//�G�l�~�[�����𓮂����֐�
	void start();


	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);
	void setPlayer(std::shared_ptr<CharaBase>);
	int getRanking();
	std::vector<Enemy>& getEnemys();

	//�A�N�e�B�u�ȃG�l�~�[������Ԃ��֐�
	std::vector<Enemy*> getActiveEnemys();
	//�ꉞ���X�g�o�[�W�������p��
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

