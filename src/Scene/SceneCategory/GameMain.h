#pragma once
#include "../SceneManager/SceneBase.h"
#include "../SceneManager/CreateScene.h"
#include "../../Object/GameObject/GameObjectEntities.h"
#include "../../UI/UIPlate/UIPlate.h"


class GameMain :public SceneBase {
public:

	GameMain();
	
	// overrideをつけるのはいいけど
	// これ以上継承しないのであればfinalをつけてあげよう
	void setup() override;
	void draw() override;
	void update() override;
	void shift() override;
	void shutdown() override;
private:
	ar::GameObjectEntities entities;
	int end_count;
	bool is_setup = false;
	UIPlate ui;
};


