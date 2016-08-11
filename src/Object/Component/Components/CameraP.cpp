#include "CameraP.h"
#include "../../../Share/Share.h"

using namespace ci;
using namespace ci::app;

CameraP::CameraP()
{
	setup();
}

void CameraP::setup()
{
	camera = CameraPersp(WIDTH, HEIGHT,
						 60.0f,
						 1.0f, 1000.0f);
}

void CameraP::update()
{
	camera.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, 1000.0f));
	camera.setEyePoint(transform.position);

}

void CameraP::draw()
{
}

void CameraP::drawBegin()
{
	gl::setMatrices(camera);
}
