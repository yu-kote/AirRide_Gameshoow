#include "GameMain.h"


#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/SignPost/SignPostManager.h"
#include "../../Object/GameObject/Obstacle/ObstacleManager.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"
#include "../../Object/GameObject/CharaBase/Enemy/Enemy.h"
#include "../../Object/GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../Share/Interface/Interface.h"

GameMain::GameMain()
{
}

void GameMain::setup()
{
	entities.setObject<ar::Light>();
	entities.setObject<ar::Camera>();

	////////////////////////////////////////////

	entities.setObject<ar::SignPostManager>();
	entities.setObject<ar::ObstacleManager>();
	entities.getObject<ar::ObstacleManager>()->setSignpostManager(entities.getObject<ar::SignPostManager>());

	entities.setObject<Player>();
	entities.setObject<EnemyHolder>();

	entities.getObject<Player>()->setSignPostManager(entities.getObject<ar::SignPostManager>());

	entities.getObject<EnemyHolder>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	entities.getObject<EnemyHolder>()->setPlayer(entities.getObject<Player>());

	entities.getObject<ar::Camera>()->setChara(entities.getObject<Player>());

	entities.setupGameObject();
}

void GameMain::draw()
{
	//ui.draw();
	entities.drawGameObject();
	entities.transDrawGameObject();

	// ƒ‰ƒCƒg‚ª‚È‚¢•`‰æ
	entities.laterDrawGameObject();
	entities.transLaterDrawGameObject();
}

void GameMain::update()
{
	entities.updateGameObject();
	entities.laterUpdateGameObject();
}

void GameMain::shift()
{
}

void GameMain::shutdown()
{
	entities.Alldestroy();
}
