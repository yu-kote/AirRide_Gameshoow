#include "EnemyHolder.h"

//EnemyHolder::EnemyHolder()
//{
//
//	
//
//}

void EnemyHolder::setup()
{
	enemys = std::list<Enemy>(4);
	for (auto& it : enemys)
	{
		it.setup();
	}

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
