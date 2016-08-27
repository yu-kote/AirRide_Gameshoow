#include "GameMain.h"


#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/SignPost/SignPostManager.h"
#include "../../Object/GameObject/Obstacle/ObstacleManager.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"
#include "../../Object/GameObject/CharaBase/Enemy/Enemy.h"
#include "../../Object/GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../Share/Interface/Interface.h"
#include "../../Object/GameObject/Skydome/Skydome.h"
#include "../../Object/GameObject/Boss/Boss.h"
#include "../../Object/GameObject/Boss/Bullet/Bullet.h"
#include "../../TaskManager/SoundManager.h"

GameMain::GameMain()
{
}

void GameMain::setup()
{
	entities.setObject<ar::Light>();
	entities.setObject<ar::Camera>();

	///////////////////////////////////////////////

	entities.setObject<ar::Skydome>();
	entities.setObject<ar::SignPostManager>();
	entities.setObject<ar::ObstacleManager>();

	entities.setObject<Player>();
	entities.setObject<EnemyHolder>();

	entities.setObject<Boss>();
	entities.setObject<Bullets>();


	//////////////////////////////////////////////

	entities.getObject<Player>()->setSignPostManager(entities.getObject<ar::SignPostManager>());

	entities.getObject<EnemyHolder>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	entities.getObject<EnemyHolder>()->setPlayer(entities.getObject<Player>());

	entities.getObject<ar::ObstacleManager>()->setEnemyHolder(entities.getObject<EnemyHolder>());
	entities.getObject<ar::ObstacleManager>()->setPlayer(entities.getObject<Player>());

	entities.getObject<ar::Camera>()->setChara(entities.getObject<Player>());

	entities.getObject <ar::Skydome>()->setTerget(entities.getObject<Player>());

	entities.getObject <Boss>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	entities.getObject <Boss>()->setEnemyHolder(entities.getObject<EnemyHolder>());
	entities.getObject <Boss>()->setPlayer(entities.getObject<Player>());

	entities.getObject <Bullets>()->setBoss(entities.getObject<Boss>());
	entities.getObject <Bullets>()->setPlayer(entities.getObject<Player>());

	entities.setupGameObject();

	if (SoundGet.find("RaceBGM")->isEnabled())
		SoundGet.find("RaceBGM")->stop();
	else
		//SoundGet.find("RaceBGM")->start();
	SoundGet.find("RaceBGM")->setLoopEnabled(true);
}

void GameMain::draw()
{

	entities.drawGameObject();
	entities.transDrawGameObject();

	// ƒ‰ƒCƒg‚ª‚È‚¢•`‰æ
	entities.laterDrawGameObject();
	entities.transLaterDrawGameObject();
	//ui.titleSetup();
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
