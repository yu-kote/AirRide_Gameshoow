#include "SignPostManager.h"
#include "../../Component/Components/Light.h"
#include "../../Component/Components/Material.h"


using namespace ci;
using namespace ci::app;

ar::SignPostManager::SignPostManager()
{
}

void ar::SignPostManager::setup()
{
	postLoad();
	setDirection();
	setRingQuat();
	setLength();
	round_length = signposts.back().getLength()
		+ signposts.back().getDirection().length();


	addComponent<ar::Light>();
	addComponent<ar::Material>(ar::Material(
		gl::Material(ColorA(0.6f, 1.0f, 0.6f, 1.0f),      // Ambient
			ColorA(0.6f, 1.0f, 0.6f, 1.0f),      // Diffuse
			ColorA(0.6f, 1.0f, 0.6f, 1.0f),      // Specular
			80.0f,                               // Shininess
			ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission
}

void ar::SignPostManager::update()
{

}

void ar::SignPostManager::draw()
{
	pointDraw();
	ringDraw();
}



ci::Matrix44f ar::SignPostManager::getMatrix(ci::Vec3f _pos)
{
	
	_pos.z = fmod(_pos.z,round_length);

	ci::Matrix44f matr = ci::Matrix44f::identity();
	
	for (auto& it = signposts.begin(); it != signposts.end()-1; it++) {
		if (it->getLength() <= _pos.z && _pos.z < (it+1)->getLength()) {
			matr *= ci::Matrix44f::createTranslation(it->getPos());
			matr *= it->getMatrix();
			matr *= ci::Matrix44f::createTranslation(
				ci::Vec3f(_pos.x, _pos.y, _pos.z - it->getLength()));
			return matr;
		}
	}
	matr *= ci::Matrix44f::createTranslation(signposts.back().getPos());
	matr *= signposts.back().getMatrix();
	matr *= ci::Matrix44f::createTranslation(
		ci::Vec3f(_pos.x, _pos.y, _pos.z - signposts.back().getLength()));
	return matr;
}


void ar::SignPostManager::ringDraw()
{
	for (auto& it : signposts) {
		it.ringDraw();
	}
}

void ar::SignPostManager::pointDraw()
{
	for (auto& it : signposts) {
		it.draw();
	}
}

void ar::SignPostManager::postLoad()
{
	std::ifstream ifstr(getAssetPath("StageInfo/StageVertex.txt").string());

	if (!ifstr.is_open())
		assert(!"Stage text not find");

	while (!ifstr.eof())
	{
		Vec3f pos;
		ifstr >> pos.x >> pos.y >> pos.z;
		signposts.push_back(SignPost(pos));
	}
}

void ar::SignPostManager::setDirection()
{
	for (auto& it = signposts.begin(); it != signposts.end() - 1; it++)
	{
		it->setDirection((it + 1)->getPos());
	}
	signposts.back().setDirection(signposts.front().getPos());
}

void ar::SignPostManager::setRingQuat()
{
	for (auto& it = signposts.begin() + 1; it != signposts.end(); it++)
	{
		it->setRingQuat((it - 1)->getPos());
	}
	signposts.front().setRingQuat(signposts.back().getPos());
}

void ar::SignPostManager::setLength()
{
	float _length = 0;
	for (auto& it: signposts)
	{
		it.setLength(_length);
		_length += it.getDirection().length();
	}
}


