#include "Camera.h"
#include "../../../Share/Share.h"

using namespace ci;
using namespace ci::app;

ar::Camera::Camera()
{
	setup();
}

void ar::Camera::setup()
{
	camera = CameraPersp(WIDTH, HEIGHT,
						 60.0f,
						 1.0f, 1000.0f);
}

void ar::Camera::update()
{
	camera.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, 1000.0f));
	camera.setEyePoint(transform.position);

}

void ar::Camera::draw()
{
}

void ar::Camera::drawBegin()
{
	gl::setMatrices(camera);
}
