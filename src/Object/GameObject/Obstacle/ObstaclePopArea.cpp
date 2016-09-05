#include "ObstaclePopArea.h"
#include <random>
#include "../../../Share/Share.h"

using namespace ci;
using namespace ci::app;

ar::ObstaclePopArea::ObstaclePopArea(const ci::Vec3f& position_, float pop_range_, float radius_, int count_)
{
	transform.position = position_;
	pop_range = pop_range_;
	radius = radius_;
	count = count_;
	obstaclePop();

	test_mt = gl::Material(ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Ambient
						   ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Diffuse
						   ColorA(1.0f, 0.3f, 0.3f, 0.5f),      // Specular
						   80.0f,                               // Shininess
						   ColorA(0.5f, 0.5f, 0.5f, 1.0f));	  // Emission
}

void ar::ObstaclePopArea::update()
{
	for (auto it : obstacles) {
		it->update();
	}
	/*std::for_each(obstacles.begin(), obstacles.end(),
				  [](std::shared_ptr<Obstacle> obs) {obs->update(); });*/

	eraseObstacle();
	//respawnObstacle();

}

void ar::ObstaclePopArea::draw()
{
	pushModelView();
	std::for_each(obstacles.begin(), obstacles.end(),
				  [](std::shared_ptr<Obstacle> obs) {obs->draw(); });
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

void ar::ObstaclePopArea::setCameraPos(const ci::Vec3f & camera_pos_)
{
	std::for_each(obstacles.begin(), obstacles.end(),
				  [&](std::shared_ptr<Obstacle> obs) {obs->setCameraPos(camera_pos_ - transform.position + obs->transform.position); });
}

std::shared_ptr<ar::Obstacle> ar::ObstaclePopArea::getNearestObstacle(ci::Vec3f target_)
{
	float minvec = std::numeric_limits<float>::max();
	std::shared_ptr<Obstacle> nearest_obs;

	std::for_each(obstacles.begin(), obstacles.end(),
				  [&](std::shared_ptr<Obstacle> obs)
	{
		Vec3f vec = target_ - obs->transform.position;
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
				  [&](std::shared_ptr<Obstacle> obs)
	{
		if (sphereToSphere(target_, radius_, transform.position + obs->transform.position, obs->radius))
		{
			is_hit = true;
			obs->bomb();
			//console() << obstacles.size() << std::endl;
		}
	});
	return is_hit;
}

void ar::ObstaclePopArea::obstaclePop()
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> range_rand(-pop_range / 2, pop_range / 2);

	for (int i = 0; i < count; i++)
	{
		Vec3f pop_pos = Vec3f(range_rand(mt), range_rand(mt), range_rand(mt));
		obstacles.push_back(std::make_shared<Obstacle>(Obstacle(pop_pos, radius)));
	}
}

void ar::ObstaclePopArea::eraseObstacle()
{
	if (obstacles.size() == 0)
		return;

	for (auto it = obstacles.begin(); it != obstacles.end(); it++)
	{
		if ((*it)->is_erase)
		{
			obstacles.erase(it);
			//obstaclePop();
			//console() << it->is_erase << std::endl;
			return;
		}
	}


	/*std::remove_if(obstacles.begin(), obstacles.end(),
				   [&](std::shared_ptr<ar::Obstacle> obs_) {
		return obs_->is_erase;
	});*/
	/*std::for_each(obstacles.begin(), obstacles.end(),
				  [&](std::shared_ptr<ar::Obstacle> obs_)
	{
		if (obs_->is_erase)
			obstacles.clear();
	});*/
	/*obstacles.remove_if([&](std::shared_ptr<ar::Obstacle> obs_) {
		return obs_->is_erase; });*/

		/*for (auto it = obstacles.begin(); it != obstacles.end();)
		{
			if ((*it)->is_erase == true)
			{
				it = obstacles.erase(it);
				continue;
			}
			it++;
		}*/
}

void ar::ObstaclePopArea::respawnObstacle()
{
	std::for_each(obstacles.begin(), obstacles.end(),
				  [&](std::shared_ptr<ar::Obstacle> obs_)
	{
		if (obs_->is_erase)
		{
			obstaclePop();
		}
	});
}

void ar::ObstaclePopArea::testObstaclePopArea()
{
}


