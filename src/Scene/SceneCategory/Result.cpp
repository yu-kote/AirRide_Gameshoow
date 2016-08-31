#include "Result.h"

Result::Result()
{
}

void Result::setup()
{
	ui.resultSetup();
}

void Result::draw()
{
	ui.resultDraw();
}

void Result::update()
{
	ui.resultUpdate();
}

void Result::shift()
{
	ci::gl::clear(ColorA(1.0f, 1.0f, 1.0f, 1.0f));
	if (!ui.ui_data["GOAL"]->isActive()) {
		Scene::createScene<Title>(new Title());
	}
}

void Result::shutdown()
{
}
