#include "GameObjectEntities.h"


GameObjectEntities::GameObjectEntities()
{
}

GameObjectEntities::~GameObjectEntities()
{
	Alldestroy();
}

void GameObjectEntities::componentsUpdate()
{
	for (const auto& it : objects)
	{
		it.second->componentsUpdate();
	}
}

void GameObjectEntities::drawBegin()
{
	for (const auto& it : objects)
	{
		it.second->drawBegin();
	}
}

void GameObjectEntities::drawEnd()
{
	for (const auto& it : objects)
	{
		it.second->drawEnd();
	}
}

void GameObjectEntities::componentsDraw()
{
	for (const auto& it : objects)
	{
		it.second->componentsDraw();
	}
}

void GameObjectEntities::componentsDestory()
{
	for (const auto& it : objects)
	{
		it.second->componentsDestroy();
	}
}


void GameObjectEntities::setupGameObject()
{
	for (const auto& it : objects)
	{
		it.second->setup();
	}
}

void GameObjectEntities::updateGameObject()
{
	for (const auto& it : objects)
	{
		it.second->componentsUpdate();
		it.second->update();
	}
}

void GameObjectEntities::drawGameObject()
{
	ci::gl::pushModelView();
	for (const auto& it : objects)
	{

		it.second->drawBegin();
		it.second->pushModelView();

		it.second->componentsDraw();
		it.second->draw();

		it.second->popModelView();
		it.second->drawEnd();

	}
	ci::gl::popModelView();
}

void GameObjectEntities::Alldestroy()
{
	for (auto it : objects)
	{
		it.second->destory();
		it.second->componentsDestroy();
	}
	objects.clear();
}
