#include "GameObject.h"

ar::GameObject::GameObject()
{
	is_active = true;
}

ar::GameObject::GameObject(const std::string & name_) :
	Object(name_)
{
	is_active = true;
}

void ar::GameObject::pushModelView()
{
	ci::gl::pushModelView();
	ci::gl::translate(transform.position);
	//ci::gl::rotate(transform.angle);
	ci::gl::multModelView(transform.rotation.toMatrix44());
	ci::gl::scale(transform.scale);
}

void ar::GameObject::popModelView()
{
	ci::gl::popModelView();
}

void ar::GameObject::componentsUpdate()
{
	for (auto it : components)
	{
		it.second->update();
	}
}

void ar::GameObject::drawBegin()
{
	for (auto it : components)
	{
		it.second->drawBegin();
	}
}

void ar::GameObject::drawEnd()
{
	for (auto it : components)
	{
		it.second->drawEnd();
	}
}

void ar::GameObject::componentsDraw()
{
	for (auto it : components)
	{
		it.second->draw();
	}
}

void ar::GameObject::componentsDestroy()
{
	for (auto it : components)
	{
		it.second->destory();
	}
	components.clear();
}

