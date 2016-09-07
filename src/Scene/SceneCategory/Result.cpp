#include "Result.h"

Result::Result()
{
	setup();
}

void Result::setup()
{
	game_count = 0;
	ui.resultSetup();
	entities.setupGameObject();
	SoundGet.find("Result")->start();
}

void Result::draw()
{
	ci::gl::clear(ColorA(1.0f, 1.0f, 1.0f, 1.0f));
	ui.resultDraw();
}

void Result::update()
{
	game_count++;
	ui.resultUpdate();
	entities.updateGameObject();
}

void Result::shift()
{
	
	if (game_count == 600) {
		UIType::is_loop = true;
		UIType::erase();
		UIObjects::erase();
		UIState::erase();
		EasingType::erase();
		Scene::createScene<Title>(new Title());
	}
}

void Result::shutdown()
{
	entities.Alldestroy();
}
