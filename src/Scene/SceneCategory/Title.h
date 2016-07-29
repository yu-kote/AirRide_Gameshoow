#pragma once
#include "../SceneManager/SceneBase.h"
#include "../SceneManager/CreateScene.h"
#include "../../Object/GameObject/GameObjectEntities.h"
#include "../../Input/InputEvent.h"
#include "../../Object/GameObject/Camera/MainCamera.h"
#include "../../UI/UIPlate/UIPlate.h"

class Title :public SceneBase {
public:

	Title();
	void setup() override;
	void update() override;
	void draw() override;
	void shift() override;
	void shutdown() override;

	ar::GameObjectEntities entities;

	UIPlate ui;
private:

};

