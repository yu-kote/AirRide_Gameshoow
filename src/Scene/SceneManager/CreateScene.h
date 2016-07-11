#pragma once
#include "SceneBase.h"
#include <memory>

class Scene
{
public:
	template<typename T>
	static void createScene(T* _scene) {
		scene = std::make_shared<T>(*_scene);
	};

	static SceneBase& get() {
		return *scene;
	}

private:
	static std::shared_ptr<SceneBase> scene;
};
