#include "EnemyAI.h"



AILevel1::AILevel1(CharaBase* _enemy, CharaBase* _player) :
	EnemyAIBase(_enemy, _player)
{


}

void AILevel1::update()
{

	enemy->transform.position.z += 1;

	/*ci::app::console() <<
		player->transform.position << std::endl;*/
}

