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
			setResizeCamera();
			setOrthoCameraResize();
		}


		std::function<void()> setResizeCamera = []() {};
		std::function<void()> setOrthoCameraResize = []() {};
	};
}


#define ResizeGet ar::Resize::get()