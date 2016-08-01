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

		std::vector<ci::Vec3f> postPositions();

		ci::Matrix44f getMatrix(ci::Vec3f);


	private:
		std::vector<std::shared_ptr<SignPost>> signpost;
		std::vector<ci::Quatf> postquat;
	private:
		void signPostDraw();
		void singPostLineDraw();
		void ringDraw();

	private:

		void postLoad();

		void postQuatDecide();

	};
}