#pragma once
#include "../GameObject.h"


#include "cinder/Camera.h"


namespace ar {

	class MainCamera : public GameObject {
	public:

		MainCamera();

		void setup();
		void update();
		void draw();

		//void setPlayer(std::shared_ptr<Player> player_);

	private:

		ci::Vec3f target_position;

		void move();


	};

}