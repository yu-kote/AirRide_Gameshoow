#pragma once
#include "cinder/app/AppNative.h"
#include "../../../Input/InputEvent.h"
#include "../../Component/Component.h"
#include "cinder/gl/Material.h"


namespace ar {

	class SignPost {
	public:

		SignPost(ci::Vec3f);

		void setDirection(ci::Vec3f);
		void setRingQuat(ci::Vec3f);

		void setLength(float);
		float getLength();
		ci::Vec3f getDirection();
		ci::Matrix44f getMatrix();

		ci::Vec3f getPos();

		void draw();
		void ringDraw();

	private:
		ci::Matrix44f matrix;
		ci::Quatf ring_quat;
		ci::Vec3f direction;
		float length;
		ci::Vec3f pos;

		
	};
}