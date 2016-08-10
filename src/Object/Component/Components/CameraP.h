#pragma once
#include "cinder/app/AppNative.h"
#include "../Component.h"
#include "../../GameObject/GameObject.h"

#include "cinder/Camera.h"


// �J�����̃R���|�[�l���g
class CameraP : public Component {
public:
	CameraP();

	void setup()override;
	void update()override;

	void draw()override;
	void drawBegin()override;

private:
	ci::CameraPersp camera;

};