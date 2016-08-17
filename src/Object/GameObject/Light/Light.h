#pragma once
#include "cinder/gl/Light.h"        // ライティング
#include "cinder/gl/Material.h"     // マテリアル(材質)
#include "../GameObject.h"

namespace ar {
	class Light : public ar::GameObject
	{
	public:
		Light();
		~Light();


		void setup()override;
		void update()override;
		void draw()override;
		void laterDraw()override;

		void Off();
		void On();

		void directionalLightSetup();
		void pointLightSetup();
		void spotLightSetup();

		void shutdown();
	private:
		ci::gl::Light* light;

		ci::Vec3f directionallight_direction;

	};

}