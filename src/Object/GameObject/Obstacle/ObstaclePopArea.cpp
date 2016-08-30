#include "ObstaclePopArea.h"
#include <random>
#include "../../../Share/Share.h"

using namespace ci;
using namespace ci::app;

ar::ObstaclePopArea::ObstaclePopArea(const ci::Vec3f& position_, float pop_range_, float radius_, int count_)
{
	transform.position = position_;
	pop_range = pop_range_;
	obstaclePop(radius_, count_);

	test_mt = gl::Material(ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Ambient
						   ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Diffuse
						   ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Specular
						   80.0f,                               // Shininess
						   ColorA(0.5f, 0.5f, 0.5f, 1.0f));	  // Emission
}

void ar::ObstaclePopArea::update()
{
	std::for_each(obstacles.begin(), obstacles.end(),
				  [](Obstacle obs) {obs.update(); });
}

void ar::ObstaclePopArea::draw()
{
	pushModelView();
	std::for_each(obstacles.begin(), obstacles.end(),
				  [](Obstacle obs) {obs.draw(); });
	popModelView();
}

void ar::ObstaclePopArea::transDraw()
{
	pushModelView();
	gl::enableAlphaBlending();

	test_mt.apply();
	gl::drawSphere(Vec3f::zero(), pop_range, 12);

	gl::disableAlphaBlending();
	popModelView();
}

ar::Obstacle ar::ObstaclePopArea::getNearestObstacle(ci::Vec3f target_)
{
	float minvec = std::numeric_limits<float>::max();
	Obstacle nearest_obs;
	std::for_each(obstacles.begin(), obstacles.end(),
				  [&](Obstacle obs)
	{
		Vec3f vec = target_ - obs.transform.position;
		float length = vec.length();

		if (length < minvec)
		{
			minvec = length;
			nearest_obs = obs;
		}
	});
	return nearest_obs;
}

bool ar::ObstaclePopArea::isHitObstacle(ci::Vec3f target_, float radius_)
{
	bool is_hit = false;
	std::for_each(obstacles.begin(), obstacles.end(),
				  [&](Obstacle obs)
	{
		if (sphereToSphere(target_, radius_, transform.position + obs.transform.position, obs.radius))
			is_hit = true;
	});
	return is_hit;
}

void ar::ObstaclePopArea::obstaclePop(float radius_, int count_)
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> range_rand(-pop_range / 2, pop_range / 2);

	for (int i = 0; i < count_; i++)
	{
		Vec3f pop_pos = Vec3f(range_rand(mt), range_rand(mt), range_rand(mt));
		obstacles.push_back(Obstacle(pop_pos, radius_));
	}
}

void ar::ObstaclePopArea::testObstaclePopArea()
{
}
