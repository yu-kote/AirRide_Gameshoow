#include "EnemyAI.h"



AILevel1::AILevel1(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
	 

	//c_Easing::apply(enemy->transform.position.z,
	//	100, EasingFunction::ExpoOut, 100);

}

void AILevel1::update()
{

	enemy->transform.position.z += 1.f;

	

}

AILevel2::AILevel2(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
}

void AILevel2::update()
{
}

AILevel3::AILevel3(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
}

void AILevel3::update()
{
}

AILevel4::AILevel4(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{
}

void AILevel4::update()
{
}
