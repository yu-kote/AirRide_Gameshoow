#include "EnemyAI.h"


AILevel1::AILevel1(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{


	enemy->transform.position.x = 3;
	enemy->transform.position.y = 3;
	enemy->setPosition(enemy->transform.position.xy());

	c_Easing::apply(enemy->transform.position.z,
					100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
					150, EasingFunction::CubicIn, 50);
	c_Easing::stop(enemy->transform.position.z);
	terget_change_count = 0;
	changeTarget();

}

void AILevel1::stert()
{
	Params->addParam("Enemy1", &HP);
}

void AILevel1::update()
{

	if (!is_terget) {
		enemy->setSpeed(player->getSpeed());
		return;
	}
	if (!c_Easing::isEnd(enemy->transform.position.z))return;


	enemy->moving(aiterget);
	tergetMotion(180);
	tergetMove();

}

AILevel2::AILevel2(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -3;
	enemy->transform.position.y = 3;
	enemy->setPosition(enemy->transform.position.xy());
	c_Easing::apply(enemy->transform.position.z,
					100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
					200, EasingFunction::ExpoIn, 50);
	c_Easing::stop(enemy->transform.position.z);
	changeTarget();

	roll_count = 2;
}

void AILevel2::stert()
{
	Params->addParam("Enemy2 HP", &HP).group("ENEMY2");
	Params->addParam("Enemy2 avoid_count", &roll_count).group("ENEMY2");

}

void AILevel2::update()
{
	if (!is_terget) {
		enemy->setSpeed(player->getSpeed());
		return;
	}
	if (!c_Easing::isEnd(enemy->transform.position.z))return;

	/*if (roll_count > 0) {
		if (avoidPlayerDashByRoll()) {
			roll_count--;
		}
	}*/
	enemy->moving(aiterget);

	tergetMotion(120);
	tergetMove();

}

AILevel3::AILevel3(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = 3;
	enemy->transform.position.y = -3;
	enemy->setPosition(enemy->transform.position.xy());

	c_Easing::apply(enemy->transform.position.z,
					100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
					250, EasingFunction::ExpoIn, 50);
	c_Easing::stop(enemy->transform.position.z);
	avoid_count = 2;
	enemy->setIntervalTakesTime(3.f);
}

void AILevel3::stert()
{
	Params->addParam("Enemy3 HP", &HP).group("ENEMY3");
	//Params->addParam("Enemy3 avoid_count", &avoid_count).group("ENEMY3");

}

void AILevel3::update()
{
	if (!is_terget) {
		enemy->setSpeed(player->getSpeed());
		return;
	}
	if (!c_Easing::isEnd(enemy->transform.position.z))return;

	//if (avoidPlayerDashByDash())
	//{
	//	//avoid_count--;
	//}


	enemy->moving(aiterget);
	tergetMotion(60);
	tergetMove();
}

AILevel4::AILevel4(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -3;
	enemy->transform.position.y = -3;
	enemy->setPosition(enemy->transform.position.xy());

	c_Easing::apply(enemy->transform.position.z,
					100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
					300, EasingFunction::ExpoIn, 50);
	c_Easing::stop(enemy->transform.position.z);
	avoid_count = 1;
	enemy->setIntervalTakesTime(3.f);

}

void AILevel4::stert()
{
	Params->addParam("Enemy4 HP", &HP).group("ENEMY4");
	Params->addParam("Enemy4 avoid_count", &avoid_count).group("ENEMY4");

}

void AILevel4::update()
{
	if (!is_terget) {
		enemy->setSpeed(player->getSpeed());
		return;
	}
	if (!c_Easing::isEnd(enemy->transform.position.z))return;
	/*if (!avoidPlayerDashByDash()) {
		if (avoid_count > 0) {
			if (avoidPlayerDashByRoll())
			{
				avoid_count--;
			}

		}
	}
*/
	if (avoid_count > 0) {
		if (avoidPlayerDashByRoll())
		{
			avoid_count--;
		}

	}

	enemy->moving(aiterget);
	tergetMotion(180);
	tergetMove();
}

AITutorial::AITutorial(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	changeTarget();

	enemy->transform.position.x = 3;
	enemy->transform.position.y = -2.5f;

	enemy->setPosition(enemy->transform.position.xy());
}

void AITutorial::stert()
{
}

void AITutorial::update()
{

	tergetMove();
}
