#include "GameMain.h"


#include "../../SampleObject.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/SignPost/SignPostManager.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"
#include "../../Object/GameObject/CharaBase/Enemy/Enemy.h"
#include "../../Object/GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"

GameMain::GameMain()
{
}

void GameMain::setup()
{
	entities.setObject<ar::Camera>();
	entities.setObject<ar::SignPostManager>();
	entities.setObject<Player>();
	//entities.setObject<EnemyHolder>();



	entities.setObject<Enemy>();
	entities.getObject<Enemy>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	entities.getObject<Enemy>()->setPlayer(entities.getObject<Player>());

	entities.setupGameObject();

	//entities.getObject<EnemyHolder>()->setSignPostManager(entities.getObject<ar::SignPostManager>());


}

void GameMain::draw()
{
	//ui.draw();
	entities.drawGameObject();
}

void GameMain::update()
{
	entities.updateGameObject();
}

void GameMain::shift()
{
}

void GameMain::shutdown()
{
	entities.Alldestroy();
}
