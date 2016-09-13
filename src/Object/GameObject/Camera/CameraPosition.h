#pragma once
#include "cinder/app/AppNative.h"

namespace ar {
	class CameraPos {
	public:
		static CameraPos& get() {
			static CameraPos camerapos;
			return camerapos;
		}

		ci::Vec3f position;

	};
}

#define CameraPosition ar::CameraPos::get().position