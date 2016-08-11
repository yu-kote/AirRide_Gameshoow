#include "MainCamera.h"
#include "../../Component/Components/Camera.h"
#include "../../../Share/Share.h"


using namespace ci;
using namespace ci::app;
ar::MainCamera::MainCamera()
{
}

void ar::MainCamera::setup()
{
	addComponent<ar::Camera>();
}

void ar::MainCamera::update()
{

}

void ar::MainCamera::draw()
{

}

void ar::MainCamera::move()
{
}
