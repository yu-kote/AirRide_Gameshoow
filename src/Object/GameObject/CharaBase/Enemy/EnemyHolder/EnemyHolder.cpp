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

}

void EnemyHolder::update()
{
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
}
