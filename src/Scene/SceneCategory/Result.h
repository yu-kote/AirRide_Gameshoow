#pragma once
#include "../SceneManager/SceneBase.h"


	class Result :public SceneBase {
	public:

		Result();
		void setup() override;
		void draw() override;
		void update() override;
		void shift() override;
		void shutdown() override;

	private:

	};
