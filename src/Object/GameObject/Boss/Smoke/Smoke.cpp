#include "Smoke.h"
#include "../../../Component/Components/Texture.h"
#include "../../../Component/Components/Material.h"
#include <random>
#include "../../Camera/CameraPosition.h"

using namespace ci;
using namespace ci::app;



Smoke::Smoke(ci::Vec3f pop_pos_)
{
	setup();
	transform.position = pop_pos_;

	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> vec_rand(-0.1f, 0.1f);
	std::uniform_real_distribution<float> upvec_rand(-0.0f, 0.6f);

	vec = Vec3f(vec_rand(mt), upvec_rand(mt), vec_rand(mt));

	std::uniform_real_distribution<float> rotate_rand(-1.0f, 1.0f);
	rotate_speed = rotate_rand(mt);
}

void Smoke::setup()
{
	speed = 0.01;
	erase_count = 80;
	count = 0;

	addComponent<ar::Texture>(ar::Texture("Smoke"));

	addComponent<ar::Material>(ar::Material(
		gl::Material(ColorA(0.8f, 0.8f, 0.8f, 1.0f),      // Ambient
					 ColorA(0.8f, 0.8f, 0.8f, 1.0f),      // Diffuse
					 ColorA(0.8f, 0.8f, 0.8f, 1.0f),      // Specular
					 80.0f,                               // Shininess
					 ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission
	translate_value = Vec3f::zero();
}

void Smoke::update()
{
	translate_value += vec;
	transform.position += vec;

	transform.scale = Vec3f(2, 2, 0);

	Vec3f direction = Vec3f(0, 0, 1);
	Vec3f target_pos = CameraPosition;
	Vec3f vector = target_pos - transform.position;

	//vector.normalize();
	Vec3f cross = direction.cross(vector);

	if (cross.lengthSquared() > 0.0f)
	{
		Quatf tempquat(cross.normalized(), cross.length());
		rotate = rotate * tempquat;
	}

	Quatf vecquat(vector.normalized(),Vec3f(0.5, 0.5, 0.5));
	rotate = vecquat;

	count++;
}

void Smoke::transDraw()
{
	drawBegin();
	pushModelView();

	gl::multModelView(rotate.toMatrix44());

	gl::enableAlphaBlending();

	gl::drawCube(Vec3f::zero(), Vec3f(1, 1, 0));

	gl::disableAlphaBlending();
	popModelView();
	drawEnd();

	gl::pushModelView();

	//gl::Material m = gl::Material(ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
	//							  ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
	//							  ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
	//							  80.0f,                               // Shininess
	//							  ColorA(1.0f, 0.0f, 0.0f, 1.0f));
	//m.apply();
	//gl::drawVector(CameraPosition, transform.position);


	//gl::drawSphere(CameraPosition + Vec3f(0, 0, 4), 0.5);
	//gl::drawSphere(transform.position, 0.5);

	gl::popModelView();
}

bool Smoke::isErase()
{
	return count >= erase_count;
}

Smokes::Smokes(ci::Vec3f pop_pos_)
{
	setup();
	rand_value = pop_pos_;
}

void Smokes::setup()
{
	count = 0;
}

void Smokes::update()
{
	count++;
	if (count % 10 == 0)
	{
		smokes.push_back(std::make_shared<Smoke>(Smoke(transform.position + rand_value)));
	}
	for (auto& it : smokes)
	{
		it->update();
	}

	/*std::remove_if(smokes.begin(p), smokes.end(),
				   [&](std::shared_ptr<Smoke> smokes_) {
		return smokes_->isErase();
	});*/

	smokes.remove_if([&](std::shared_ptr<Smoke> smokes_) {
		return smokes_->isErase();
	});

}

void Smokes::transDraw()
{
	//pushModelView();

	for (auto& it : smokes)
	{
		it->transDraw();
	}

	//popModelView();
}

void Smokes::setBossWorldPos(ci::Vec3f boss_pos_)
{
	transform.position = boss_pos_;
}
