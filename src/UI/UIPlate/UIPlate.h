#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/svg/Svg.h"
#include "cinder/imageIo.h" 
#include "cinder/gl/Texture.h" 
#include "../UIManager/UIManager.h"
#include "cinder/Camera.h"
#include "../Texture.h"
class UIPlate : public UIManager
{
private:
	ci::CameraOrtho camera_o;
	ci::gl::Texture tex;
public:
	UIPlate() {
		camera_o = ci::CameraOrtho(0, 800,
			600, 0,
			1, 10);
		camera_o.setEyePoint(ci::Vec3f(0.0f, 0.0f, 0.0f));
		camera_o.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, -1000.0f));
	};
	void titleSetup();
	void titleUpdate();
	void titleDraw();

	void gameMainSetup();
	void gameMainUpdate();
	void gameMainDraw();
	
};