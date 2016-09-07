#pragma once
#include "../SceneManager/SceneBase.h"
#include "../SceneManager/CreateScene.h"
#include "../../TaskManager/SoundManager.h"
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
	float color_r;
	float color_g;
	float color_b;
	int update_count;
	int end_count;
	int next_count;
	bool end_flag;

};

