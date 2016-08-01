#pragma once
#include "../SceneManager/SceneBase.h"

#include "../../Object/GameObject/GameObjectEntities.h"
#include "../../UI/UIPlate/UIPlate.h"

class Title :public SceneBase {
public:

	Title();
	void setup() override;
	void update() override;
	void draw() override;
	void shift() override;
	void shutdown() override;

private:
	ar::GameObjectEntities entities;

	UIPlate ui;

};

