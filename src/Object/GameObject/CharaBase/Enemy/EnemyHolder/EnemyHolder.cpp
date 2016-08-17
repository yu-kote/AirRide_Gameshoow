#include "EnemyHolder.h"

//EnemyHolder::EnemyHolder()
//{
//
//	
//
//}

EnemyHolder::EnemyHolder()
{
	enemys = std::vector<Enemy>(4);
}

void EnemyHolder::setup()
{
	for (auto& it : enemys)
	{
		it.setup();
	}
	enemys[0].setAI<AILevel1>();
	enemys[1].setAI<AILevel2>();
	enemys[2].setAI<AILevel3>();
	enemys[3].setAI<AILevel4>();

	target_number = 0;
	enemys[target_number].setTarget(true);

}

void EnemyHolder::update()
{
	targetChange();
	for (auto& it : enemys)
	{
		it.update();
	}
}

void EnemyHolder::draw()
{
	for (auto& it : enemys)
	{
		it.draw();
	}
}

void EnemyHolder::setSignPostManager(std::shared_ptr<ar::SignPostManager> _spm)
{
	for (auto& it : enemys)
	{
		it.setSignPostManager(_spm);
	}
}

void EnemyHolder::setPlayer(std::shared_ptr<CharaBase> _player)
{
	for (auto& it : enemys)
	{
		it.setPlayer(_player);
	}
	player = _player.get();
}

int EnemyHolder::getRanking()
{
	return 0;
}


void EnemyHolder::targetChange()
{
	if (target_number == enemys.size()-1)return;
	if (enemys[target_number].isEnd()) {
		target_number++;
		target_number = std::min(target_number, (int)enemys.size()-1);
		enemys[target_number].setTarget(true);
	}
}
