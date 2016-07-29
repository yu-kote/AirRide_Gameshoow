#pragma once
#include "cinder/app/AppNative.h"
#include "../Component.h"
#include "../../GameObject/GameObject.h"

#include "cinder/Camera.h"

namespace ar {

	class Camera : public Component {
	public:
		Camera();

		void setup()override;
		void update()override;

		void draw()override;
		void drawBegin()override;

		void setMoveDistance(const ci::Vec3f& move_distance_) { move_distance = move_distance_; }
		void setAngleDistance(const ci::Vec3f& angle_distance_) { angle_distance = angle_distance_; }


	private:
		ci::CameraPersp camera;

		ci::Vec3f move_distance;
		ci::Vec3f angle_distance;
		ci::Vec3f lookpoint;

		ci::Vec3f look_vec;
		ci::Vec3f root_vec;

	};
}