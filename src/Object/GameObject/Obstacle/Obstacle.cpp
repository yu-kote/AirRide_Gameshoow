#include "Obstacle.h"
#include "../../Component/Components/Material.h"

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
}

void ar::Obstacle::update()
{
}

void ar::Obstacle::draw()
{
	drawBegin();
	pushModelView();

	gl::drawSphere(Vec3f::zero(), radius, 12);

	popModelView();
	drawEnd();
}
