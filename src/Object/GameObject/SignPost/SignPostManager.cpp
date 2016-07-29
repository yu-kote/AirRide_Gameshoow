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


