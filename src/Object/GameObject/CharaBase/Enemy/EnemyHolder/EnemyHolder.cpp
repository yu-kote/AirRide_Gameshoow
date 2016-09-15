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
	is_start = false;
	is_tutorial = false;
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

	is_start = false;
	is_tutorial = false;
}

bool EnemyHolder::isDistant()
{
	float distance = -player->transform.position.z + (*getActiveEnemys().begin())->transform.position.z;
	if (distance < 30)
		return false;
	return true;
}

void EnemyHolder::tutorialSetup()
{
	for (auto& it : enemys)
	{
		it.setup();
	}
	enemys[0].setAI<AITutorial>();

	target_number = 0;
	enemys[target_number].setTarget(true);

	is_start = true;
	is_tutorial = true;
	enemys[0].is_waiting = false;
}

int EnemyHolder::remainingEnemy()
{
	int remaining_enemy = 0;
	for (auto& it : enemys)
	{
		if (it.isEnd())
		{
			remaining_enemy++;
		}
	}
	return 4 - remaining_enemy;
}

void EnemyHolder::update()
{
	if (!is_start) return;


	targetChange();
	for (auto& it : enemys)
	{
		it.update();
	}
}

void EnemyHolder::draw()
{
	if (is_tutorial)
		enemys[0].draw();
	else
	{
		for (auto& it : enemys)
		{
			it.draw();
		}
	}
}

void EnemyHolder::transDraw()
{
	for (auto& it : enemys)
	{
		it.transDraw();
	}
}

void EnemyHolder::stop()
{
	is_start = false;
}

void EnemyHolder::start()
{
	if (!is_start) {
		for (auto& it : enemys) it.start();
		is_start = true;
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
	int rank = 1;
	for (auto& it : enemys)
	{
		if (it.transform.position.z > player->transform.position.z) {
			rank++;
		}
	}
	return rank;
}

std::vector<Enemy>& EnemyHolder::getEnemys()
{
	return enemys;
}

std::vector<Enemy*> EnemyHolder::getActiveEnemys()
{
	std::vector<Enemy*> _ene;
	for (auto& it : enemys)
	{
		if (it.isEnd() == false) {
			_ene.push_back(&it);
		}
	}

	if (_ene.begin() == _ene.end())
	{
		_ene.push_back(new Enemy());
	}

	return _ene;
}

std::list<Enemy*> EnemyHolder::getActiveEnemysList()
{
	std::list<Enemy*> _ene;
	for (auto& it : enemys)
	{
		if (it.getTarget()) {
			_ene.push_back(&it);
		}
	}

	return _ene;
}

bool EnemyHolder::isEndLasstEnemy()
{
	return enemys.back().isEnd();
}

void EnemyHolder::targetChange()
{
	if (target_number == enemys.size() - 1)return;
	if (enemys[target_number].isEnd()) {
		target_number++;
		target_number = std::min(target_number, (int)enemys.size() - 1);
		enemys[target_number].setTarget(true);
	}
}
