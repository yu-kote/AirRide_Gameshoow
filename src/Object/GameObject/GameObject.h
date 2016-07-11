#pragma once

#include "cinder/app/AppNative.h"

#include "../Object.h"
#include "../Component/Component.h"
#include "../Component/Components/Transform.h"
#include <unordered_map>
#include <string>
#include <typeinfo>

// ï`âÊÇ≥ÇÍÇÈÇ‡ÇÃÇ…åpè≥Ç≥ÇÍÇÈÉNÉâÉX
class GameObject : public Object {
public:

	GameObject();
	GameObject(const std::string& name_);

	void setIsActive(const int& is_active_) { is_active = is_active_; }
	bool getIsActive() { return is_active; }

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	void componentsUpdate();

	void drawBegin();
	void drawEnd();
	void componentsDraw();

	void componentsDestroy();

public:

	void pushModelView();
	void popModelView();

public:

	Transform transform;

private:
	bool is_active;

public:

	template<typename T>
	void addComponent() {
		const type_info& id = typeid(T);
		std::string componentname = createComponentName<T>();

		if (components.find(componentname) == components.end())
			components.insert(std::make_pair(componentname, std::make_shared<T>()));
	}

	template<typename T>
	void addComponent(T) {
		const type_info& id = typeid(T);
		std::string componentname = createComponentName<T>();

		if (components.find(componentname) == components.end())
			components.insert(std::make_pair(componentname, std::make_shared<T>()));
	}

	template<typename T>
	std::shared_ptr<T> getComponent() {
		int script_size = sizeof(T);

		std::string componentname = createComponentName<T>();
		if (components.find(componentname) == components.end())
		{
			components.insert(std::make_pair(componentname, std::make_shared<T>()));
		}

		if (script_size > 128)
		{
			return std::dynamic_pointer_cast<T>(components.find(componentname)->second);
		}
		else
		{
			return std::static_pointer_cast<T>(components.find(componentname)->second);
		}
	}

private:
	template<typename T>
	static std::string createComponentName() {
		const type_info& id = typeid(T);

		std::string class_name = id.name();
		class_name.erase(0, 6);

		return class_name;
	}

private:

	std::unordered_map<std::string, std::shared_ptr<Component>> components;
};