#pragma once
#include "cinder/app/AppNative.h"
#include "../GameObject.h"


namespace ar {
	class Obstacle : public ar::GameObject {
	public:
		// ‹@—‹‚Ì”¼Œa
		Obstacle(const ci::Vec3f& position_, float radius_);

		void setup();
		void update();
		void draw();

	private:
		// ”¼Œa
		float radius;

	};
}