#pragma once
#include "../GameObject.h"
#include "Signpost.h"

namespace ar {

	class SignPostManager : public GameObject {
	public:
		SignPostManager();

		void setup();
		void update();
		void draw();

		
		ci::Matrix44f getMatrix(ci::Vec3f);


	private:
		std::vector<SignPost> signposts;
		
		void postLoad();
		void setDirection();
		void setRingQuat();
		void setLength();

		void ringDraw();
		void pointDraw();
		float round_length;
	};
}