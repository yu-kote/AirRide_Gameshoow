#include "GameObjectEntities.h"


ar::GameObjectEntities::GameObjectEntities()
{
}

ar::GameObjectEntities::~GameObjectEntities()
{
	Alldestroy();
}

void ar::GameObjectEntities::componentsUpdate()
{
	for (const auto& it : objects)
	{
		it.second->componentsUpdate();
	}
}

void ar::GameObjectEntities::drawBegin()
{
	for (const auto& it : objects)
	{
		it.second->drawBegin();
	}
}

void ar::GameObjectEntities::drawEnd()
{
	for (const auto& it : objects)
	{
		it.second->drawEnd();
	}
}

void ar::GameObjectEntities::componentsDraw()
{
	for (const auto& it : objects)
	{
		it.second->componentsDraw();
	}
}

void ar::GameObjectEntities::componentsDestory()
{
	for (const auto& it : objects)
	{
		it.second->componentsDestroy();
	}
}


void ar::GameObjectEntities::setupGameObject()
{
	for (const auto& it : objects)
	{
		it.second->setup();
	}
}

void ar::GameObjectEntities::updateGameObject()
{
	//objects.size();
	
	for (const auto& it : objects)
	{
		it.second->componentsUpdate();
		it.second->update();
	}
}

void ar::GameObjectEntities::drawGameObject()
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

void ar::GameObjectEntities::Alldestroy()
{
	for (auto it : objects)
	{
		it.second->destory();
		it.second->componentsDestroy();
	}
	objects.clear();
}
