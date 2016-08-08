#pragma once
#include "cinder/app/AppNative.h"
#include "../../../Input/InputEvent.h"
#include "../../Component/Component.h"
#include "cinder/gl/Material.h"


namespace ar {

	class SignPost : public Component {
	public:

		SignPost();
		SignPost(ci::Vec3f position_, ci::Vec3f size_ = ci::Vec3f(0.3f, 0.3f, 0.3f));
		SignPost(ci::Vec3f position_, ci::Vec3f _direction, ci::Vec3f size_ = ci::Vec3f(0.3f, 0.3f, 0.3f));

		void setup();
		void update();
		void draw();

		ci::Vec3f direction;
		float length;
	};




}