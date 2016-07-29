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
	camera.setEyePoint(transform.position + move_distance);
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000) + lookpoint + move_distance);
}

void ar::Camera::draw()
{
}

void ar::Camera::drawBegin()
{
	gl::setMatrices(camera);
}
