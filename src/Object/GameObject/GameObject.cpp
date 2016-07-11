#include "GameObject.h"

GameObject::GameObject()
{
	is_active = true;
}

GameObject::GameObject(const std::string & name_) :
	Object(name_)
{
	is_active = true;
}

void GameObject::pushModelView()
{
	ci::gl::pushModelView();
	ci::gl::translate(transform.position);
	//ci::gl::rotate(transform.angle);
	ci::gl::multModelView(transform.rotation.toMatrix44());
	ci::gl::scale(transform.scale);
}

void GameObject::popModelView()
{
	ci::gl::popModelView();
}

void GameObject::componentsUpdate()
{
	for (auto it : components)
	{
		it.second->update();
	}
}

void GameObject::drawBegin()
{
	for (auto it : components)
	{
		it.second->drawBegin();
	}
}

void GameObject::drawEnd()
{
	for (auto it : components)
	{
		it.second->drawEnd();
	}
}

void GameObject::componentsDraw()
{
	for (auto it : components)
	{
		it.second->draw();
	}
}

void GameObject::componentsDestroy()
{
	for (auto it : components)
	{
		it.second->destory();
	}
	components.clear();
}

