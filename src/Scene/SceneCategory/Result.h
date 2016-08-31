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

	private:
		UIPlate ui;
	};
