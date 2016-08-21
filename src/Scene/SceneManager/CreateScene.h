#pragma once
#include "SceneBase.h"
#include <memory>

class Scene
{
public:
        // templateはなんでも受け付けてしまうので注意
        // SceneBaceのポインタを仮引数に設定してあげれば
        // シーンのみ受け付ける関数が作成できる
	template<typename T>
	static void createScene(T* _scene) {
		scene = std::make_shared<T>(*_scene);
	};

	static SceneBase& get() {
		return *scene;
	}

private:
        // unique_ptrを検討しよう
	static std::shared_ptr<SceneBase> scene;
};
