#include "Title.h"
#include "../SceneCategory/GameMain.h"
#include "../../Input/InputEvent.h"

using namespace ci;
using namespace ci::app;

Title::Title()
{
}

void Title::setup()
{
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
