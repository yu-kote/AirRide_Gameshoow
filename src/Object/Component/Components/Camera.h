#pragma once
#include "cinder/app/AppNative.h"
#include "../Component.h"
#include "../../GameObject/GameObject.h"

#include "cinder/Camera.h"

namespace ar {

	// カメラのコンポーネント
	class Camera : public Component {
	public:
		Camera();

		void setup()override;
		void update()override;

		void draw()override;
		void drawBegin()override;

	private:
		ci::CameraPersp camera;

	};
}