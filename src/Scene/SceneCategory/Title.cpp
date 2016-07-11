#include "Title.h"
#include "../SceneCategory/GameMain.h"


#include "../../SampleObject.h"
#include "../../Object/GameObject/Camera/MainCamera.h"

using namespace ci;
using namespace ci::app;

Title::Title()
{
}

void Title::setup()
{
	entities.setObject<MainCamera>();
	entities.setObject<SampleObject>();

	entities.setupGameObject();

}

void Title::update()
{
	entities.updateGameObject();
}

void Title::draw()
{
	entities.drawGameObject();
}

void Title::shift()
{
	if (env.isPush(KeyEvent::KEY_a))
	{
		Scene::createScene<GameMain>(new GameMain());
	}
}

void Title::shutdown()
{
	entities.Alldestroy();
}
