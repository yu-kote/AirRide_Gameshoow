#pragma once
#include "cinder/app/AppNative.h"

namespace ar {
	class CameraInfo {
	public:
		static CameraInfo& get() {
			static CameraInfo camerapos;
			return camerapos;
		}

		ci::Vec3f position;

		std::function<void()> shakeCamera = []() {};
		void shakeCameraCall() {
			shakeCamera();
		}

	};
}

#define CameraPosition ar::CameraInfo::get().position
#define CameraInfoGet ar::CameraInfo::get()