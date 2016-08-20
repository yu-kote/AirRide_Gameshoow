#include "Skydome.h"
#include "../../Component/Components/Material.h"
#include "cinder/gl/Material.h"

using namespace ci;
using namespace ci::app;

void ar::Skydome::setup()
{
	addComponent<ar::Texture>(ar::Texture("Skydome"));
	addComponent<ar::Material>(ar::Material(ar::Material(
		gl::Material(ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
					 ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
					 ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
					 80.0f,                               // Shininess
					 ColorA(0.5f, 0.5f, 0.5f, 1.0f)))));	  // Emission

	transform.scale = ci::Vec3f::one() * 500;
}

void ar::Skydome::update()
{
	if (target == nullptr)return;
	transform.position = (*target).getWorldPoisition();

}

void ar::Skydome::draw()
{
	glCullFace(GL_FRONT);

	ci::gl::drawSphere(ci::Vec3f::zero(), 1, 30);


	glCullFace(GL_BACK);

}

void ar::Skydome::setTerget(std::shared_ptr<CharaBase> target_)
{
	target = target_.get();
}
