#pragma once
#include "cinder/gl/Light.h"        // ���C�e�B���O
#include "cinder/gl/Material.h"     // �}�e���A��(�ގ�)
#include "../Component.h"

namespace ar {
	class Light : public Component
	{
	public:
		Light();
		~Light();


		void setup()override;
		void update()override;
		void drawBegin()override;
		void drawEnd()override;

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