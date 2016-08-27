#include "Obstacle.h"
#include "../../Component/Components/Material.h"
#include "../../../TaskManager/ObjDataManager.h"
#include "../../Component/Components/Texture.h"

using namespace ci;
using namespace ci::app;

ar::Obstacle::Obstacle(const ci::Vec3f& position_, float radius_)
{
	radius = radius_;
	transform.position = position_;
	setup();
}

void ar::Obstacle::setup()
{
	addComponent<ar::Material>(ar::Material(
		gl::Material(ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
					 ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
					 ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
					 80.0f,                               // Shininess
					 ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission
	addComponent<ar::Texture>(ar::Texture("Obstacle"));
}

void ar::Obstacle::update()
{
}

void ar::Obstacle::draw()
{
	drawBegin();
	pushModelView();

	gl::scale(0.04, 0.04, 0.04);
	gl::draw(ObjDataGet.find("obstacle"));

	popModelView();
	drawEnd();
}
