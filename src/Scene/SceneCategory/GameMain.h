#pragma once
#include "../SceneManager/SceneBase.h"

	class GameMain :public SceneBase {
	public:

		GameMain();
		void setup() override;
		void draw() override;
		void update() override;
		void shift() override;
		void shutdown() override;

	private:

	};


