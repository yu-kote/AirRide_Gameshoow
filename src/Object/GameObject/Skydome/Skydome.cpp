#include "Skydome.h"

void Skydome::setup()
{
	//tex = テクスチャマネージャーからもらう予定

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
	tex->enableAndBind();
	ci::gl::drawSphere(ci::Vec3f::zero(), 1, 30);

	tex->disable();
	glCullFace(GL_BACK);
}

void Skydome::setTerget(std::shared_ptr<ar::GameObject> _terget)
{
	terget = _terget.get();
}
