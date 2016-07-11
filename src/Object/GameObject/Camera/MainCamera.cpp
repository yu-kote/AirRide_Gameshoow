#include "MainCamera.h"
#include "../../Component/Components/CameraP.h"
#include "../../../Share/Share.h"


using namespace ci;
using namespace ci::app;
MainCamera::MainCamera()
{
}

void MainCamera::setup()
{
	addComponent<CameraP>();

}

void MainCamera::update()
{

}

void MainCamera::draw()
{

}
