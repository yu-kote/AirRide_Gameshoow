#include "EnemyAI.h"



AILevel1::AILevel1(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	 
	enemy->transform.position.x = 1;
	enemy->transform.position.y = 1;

	//c_Easing::apply(enemy->transform.position.z,
	//	100, EasingFunction::ExpoOut, 100);

}

void AILevel1::update()
{

	enemy->transform.position.z += 0.4f;

	

}

AILevel2::AILevel2(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -1;
	enemy->transform.position.y = 1;
}

void AILevel2::update()
{
	enemy->transform.position.z += 0.6f;

}

AILevel3::AILevel3(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = 1;
	enemy->transform.position.y = -1;
}

void AILevel3::update()
{
	enemy->transform.position.z += 0.8f;

}

AILevel4::AILevel4(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	enemy->transform.position.x = -1;
	enemy->transform.position.y = -1;
}

void AILevel4::update()
{
	enemy->transform.position.z += 1.f;

}
