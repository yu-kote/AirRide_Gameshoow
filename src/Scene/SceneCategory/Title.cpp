#include "Title.h"
#include "../SceneCategory/GameMain.h"


#include "../../SampleObject.h"
#include "../../Object/GameObject/Camera/MainCamera.h"
#include "../../Object/GameObject/SignPost/SignPostManager.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"


using namespace ci;
using namespace ci::app;

Title::Title()
{
}

void Title::setup()
{
	entities.setObject<ar::MainCamera>();
	entities.setObject<ar::SignPostManager>();
	entities.setObject<ar::SampleObject>();
	entities.setObject<Player>();

	entities.setupGameObject();

}

void Title::update()
{
	entities.updateGameObject();
}

void Title::draw()
{
	//ui.draw();
	entities.drawGameObject();
}

void Title::shift()
{
	if (env.isPush(KeyEvent::KEY_RETURN))
	{
		//Scene::createScene<GameMain>(new GameMain());
	}
}

void Title::shutdown()
{
	entities.Alldestroy();
}
