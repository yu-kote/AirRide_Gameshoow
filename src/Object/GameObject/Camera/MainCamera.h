#pragma once
#include "../GameObject.h"


#include "cinder/Camera.h"


class MainCamera : public GameObject {
public:

	MainCamera();

	void setup();
	void update();
	void draw();


private:

};
