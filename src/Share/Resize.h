#pragma once
#include "cinder/app/AppNative.h"
#include <iostream>

namespace ar
{
	class Resize {
	public:
		static Resize& get() {
			static Resize resize;
			return resize;
		}

		void resize() {
			setPerspCameraResize();
			setOrthoCameraResize();
		}


		std::function<void()> setPerspCameraResize = []() {};
		std::function<void()> setOrthoCameraResize = []() {};
	};
}


#define ResizeGet ar::Resize::get()