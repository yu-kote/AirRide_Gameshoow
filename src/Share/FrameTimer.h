#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/Camera.h"
#include <chrono>

#include "Share.h"


class FrameTimer {
public:

	void setup() {
		using namespace ci;
		using namespace ci::app;
		font = Font("Hiragino Maru Gothic ProN W4", 60.0f);

		// 平行投影カメラの初期化
		camera = CameraOrtho(0, WIDTH,        // 画面左の座標、画面右の座標
							 HEIGHT, 0,       // 画面下端の座標、画面上端の座標
							 1, 10);                 // 画面手前の座標、画面奥の座標

		camera.setEyePoint(Vec3f(0.0f, 0.0f, 0.0f));
		camera.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, -1000.0f));

		is_stop = false;
		stop_frame = 0;
	}


	void start(bool is_world = false) {
		mstart = std::chrono::system_clock::now();

		if (worldcount > stop_frame)
			is_stop = false;
		else
			is_stop = true;

		if (is_world == true)
			worldcount++;
	}

	void end() {
		mend = std::chrono::system_clock::now();
		sec = std::chrono::duration_cast<std::chrono::milliseconds>(mend - mstart).count();
	}

	void consoleLook() {
		ci::app::console() << "point sec : " << sec << std::endl;
	}

	void draw() {
		using namespace ci;
		using namespace ci::app;
		gl::setMatrices(camera);
		gl::pushModelView();
		Vec3f t = Vec3f(0, 0, -5.0);
		gl::translate(t);
		gl::drawString(std::to_string(sec), Vec2f(WIDTH - 200, HEIGHT - 50), Color(1.0f, 1.0f, 1.0f), font);
		gl::popModelView();
	}

	void stopTheWorld(const int& stopframe_ = 1) {
		stop_frame = stopframe_;
		worldcount = 0;
	}

	bool getIsStop() {
		return is_stop;
	}
	long long getWorldCount() {
		return worldcount;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> mstart, mend;
	long long sec;

	ci::Font font;
	ci::CameraOrtho camera;

	ci::Vec3f pos;

	bool is_stop;
	int stop_frame;
	long long worldcount = 1;

};
