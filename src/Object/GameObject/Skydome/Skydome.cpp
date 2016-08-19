#include "Skydome.h"

void Skydome::setup()
{
	addComponent<ar::Texture("Skydome")>();
	transform.scale = ci::Vec3f::one() * 500;
}

void Skydome::update()
{
	if (terget != nullptr)return;
	transform.position = (*terget).transform.position;

}

void Skydome::draw()
{
	glCullFace(GL_FRONT);

	ci::gl::drawSphere(ci::Vec3f::zero(), 1, 30);


	glCullFace(GL_BACK);

}
