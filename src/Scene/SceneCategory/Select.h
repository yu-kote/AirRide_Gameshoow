#pragma once
#include "../SceneManager/SceneBase.h"

class Select :public SceneBase {
public:

	Select();
	void setup() override;
	void draw() override;
	void update() override;
	void shift() override;
	void shutdown() override;

private:

};