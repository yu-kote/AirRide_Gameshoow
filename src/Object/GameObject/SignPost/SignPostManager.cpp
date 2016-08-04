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
	postQuatDecide();
	for (auto& it = signpost.begin(); it != signpost.end() - 1; it++)
	{
		ci::Vec3f dir = (*(it + 1))->transform.position
			- (*it)->transform.position;
		(*it)->direction = dir;
	}
	for (auto& it = signpost.begin() + 1; it != signpost.end(); it++)
	{
		(*it)->length =
			(*(it - 1))->length + (*(it - 1))->direction.length();
	}

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
	signPostDraw();
	ringDraw();
}

std::vector<ci::Vec3f> ar::SignPostManager::postPositions()
{
	std::vector<ci::Vec3f> positions;

	for (int i = 0; i < signpost.size(); i++)
	{
		positions.push_back(signpost[i]->transform.position);
	}
	return positions;
}

ci::Matrix44f ar::SignPostManager::getMatrix(ci::Vec3f _pos)
{
	ci::Matrix44f matr = ci::Matrix44f::identity();
	if (_pos.z < 0) return matr;
	if (_pos.z > signpost.back()->length) return matr;

	for (auto& it = signpost.begin(); it != signpost.end() - 1; it++)
	{
		if ((*it)->length < _pos.z && (*(it + 1))->length >= _pos.z) {
			matr *= ci::Matrix44f::createTranslation((*it)->transform.position);
			matr *= ci::Quatf(
				ci::Vec3f::zAxis(),
				(*it)->direction.normalized()
				).toMatrix44();
			matr *= ci::Matrix44f::createTranslation(
				ci::Vec3f(_pos.x, _pos.y, _pos.z - (*it)->length));
			//ci::gl::multModelView(matr);
			return matr;
		}
	}

}

void ar::SignPostManager::signPostDraw()
{
	std::for_each(signpost.begin(), signpost.end(),
				  [&](std::shared_ptr<SignPost> post) {post->draw(); });
	singPostLineDraw();
}

void ar::SignPostManager::singPostLineDraw()
{
	for (int i = 1; i < signpost.size(); i++)
	{
		Vec3f start = signpost[i - 1]->transform.position;
		Vec3f end = signpost[i]->transform.position;
		gl::drawVector(start, end, 0.1f);
	}
}

void ar::SignPostManager::ringDraw()
{
	int i = 0;
	std::for_each(signpost.begin(), signpost.end(),
				  [&](std::shared_ptr<SignPost> post)
	{
		gl::pushModelView();
		gl::translate(post->transform.position);
		gl::rotate(postquat[i].toMatrix44());
		gl::drawTorus(3.0f, 0.3f, 12, 12);
		gl::popModelView();
		i++;
	});
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
		signpost.push_back(std::make_shared<SignPost>(SignPost(pos)));
	}
}

void ar::SignPostManager::postQuatDecide()
{
	postquat.push_back(Quatf());
	for (int i = 1; i < signpost.size() - 1; i++)
	{
		Vec3f currentpos = signpost[i]->transform.position;
		Vec3f vec_a = currentpos - signpost[i - 1]->transform.position;
		Vec3f vec_b = signpost[i + 1]->transform.position - currentpos;
		Vec3f postvec = vec_a + vec_b;

		Quatf postquat_ = Quatf(Vec3f(0, 0, 1), postvec);
		postquat.push_back(Quatf(postquat_));
	}
	postquat[0] = postquat[1];
	postquat.push_back(postquat[postquat.size() - 1]);
}


