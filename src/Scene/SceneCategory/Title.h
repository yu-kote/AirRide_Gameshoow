#pragma once
#include "../SceneManager/SceneBase.h"
#include "../SceneManager/CreateScene.h"
#include "../../TaskManager/SoundManager.h"
#include "../../Object/GameObject/GameObjectEntities.h"
#include "../../UI/UIPlate/UIPlate.h"

class Player;
class EnemyHolder;

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
	bool tutorial;

	void gameSetup();
	void gameUpdate();
	void gameDraw();

	bool tutorial_flag[3] = {
		tutorial_flag[0] = false,
		tutorial_flag[1] = false,
		tutorial_flag[2] = false,
	};

	std::shared_ptr<Player> player;
	std::shared_ptr<EnemyHolder> enemyholder;


};

