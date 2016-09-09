#pragma once
#include "../SceneManager/SceneBase.h"
#include "../SceneManager/CreateScene.h"
#include "../../TaskManager/SoundManager.h"
#include "../../Object/GameObject/GameObjectEntities.h"
#include "../../UI/UIPlate/UIPlate.h"
#include "../SceneCategory/Title.h"
class Result :public SceneBase {
public:
	Result();
	void setup() override;
	void draw() override;
	void update() override;
	void shift() override;
	void shutdown() override;
	void ending();
	des::Vec3f color;
private:
	UIPlate ui;
	ar::GameObjectEntities entities;
	int game_count;
	int end_count;
	bool end;
};
