#include "EnemyAI.h"


AILevel1::AILevel1(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	
	HP = 1;
	enemy->transform.position.x = 3;
	enemy->transform.position.y = 3;

	c_Easing::apply(enemy->transform.position.z,
		100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
		150, EasingFunction::CubicIn,50);
	terget_change_count = 0;
	aiterget = ci::Vec2f(ci::randFloat(-7.f, 7.f), ci::randFloat(-7.f, 7.f));
	
}

void AILevel1::stert()
{
	Params->addParam("Enemy1", &HP);
}

void AILevel1::update()
{
	//
	if (!is_terget) {
		enemy->transform.position.z += 1;
		return;
	}

	if(!c_Easing::isEnd(enemy->transform.position.z))return;
	goPositon(aiterget.xyx());
	terget_change_count++;
	if (terget_change_count > 60 * 1
		|| aiterget.distanceSquared(enemy->transform.position.xy()) < 1) {
		terget_change_count = 0;
		aiterget = ci::Vec2f(ci::randFloat(-7.f, 7.f), ci::randFloat(-7.f, 7.f));

	}
	float difference = enemy->transform.position.z - player->transform.position.z;
	if (difference > 3.f) {
		enemy->transform.position.z += 0.8;
		return;
	}
	if (difference < 3.f
		&& HP > 0) {
		enemy->transform.position.z += 1.2f;
		return;
	}
	enemy->transform.position.z += 0.8f;

}

AILevel2::AILevel2(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -3;
	enemy->transform.position.y = 3;
	c_Easing::apply(enemy->transform.position.z,
		100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
		400, EasingFunction::ExpoIn, 50);
}

void AILevel2::stert()
{
	Params->addParam("Enemy2", &HP);
}

void AILevel2::update()
{
	if (!is_terget) {
		enemy->transform.position.z += 1;
		return;
	}
	if (!c_Easing::isEnd(enemy->transform.position.z))return;

}

AILevel3::AILevel3(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = 3;
	enemy->transform.position.y = -3;
	c_Easing::apply(enemy->transform.position.z,
		100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
		500, EasingFunction::ExpoIn, 50);
}

void AILevel3::stert()
{
	Params->addParam("Enemy3", &HP);
}

void AILevel3::update()
{
	//
	if (!is_terget) {
		enemy->transform.position.z += 1;
		return;
	}
}

AILevel4::AILevel4(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -3;
	enemy->transform.position.y = -3;
	c_Easing::apply(enemy->transform.position.z,
		100, EasingFunction::CircOut, 50);
	c_Easing::apply(enemy->transform.position.z,
		600, EasingFunction::ExpoIn, 50);
}

void AILevel4::stert()
{
	Params->addParam("Enemy4", &HP);
}

void AILevel4::update()
{
	//
	if (!is_terget) {
		enemy->transform.position.z += 1;
		return;
	}


}
