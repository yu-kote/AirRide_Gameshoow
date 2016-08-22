#include "ObstacleManager.h"
#include "../GameObjectEntities.h"
#include "../CharaBase/Player/Player.h"
#include "../CharaBase/Enemy/EnemyHolder/EnemyHolder.h"

using namespace ci;
using namespace ci::app;

ar::ObstacleManager::ObstacleManager()
{
}

void ar::ObstacleManager::setup()
{
	loadObstacleArea();
}

void ar::ObstacleManager::update()
{
	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [](ObstaclePopArea pop_areas_) {pop_areas_.update(); });
	isEnemysInObstacleArea();
}

void ar::ObstacleManager::draw()
{
	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [](ObstaclePopArea pop_areas_) {pop_areas_.draw(); });

	gl::pushModelView();

	gl::drawSphere(Vec3f::zero(), 1, 12);

	gl::popModelView();
}

void ar::ObstacleManager::transDraw()
{
	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [](ObstaclePopArea pop_areas_) {pop_areas_.transDraw(); });
}


ar::Obstacle ar::ObstacleManager::getNearestObstacle(ci::Vec3f target_)
{
	float minvec = std::numeric_limits<float>::max();
	ObstaclePopArea nearest_pop_area;

	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [&](ObstaclePopArea pop_area)
	{
		Vec3f vec = target_ - pop_area.transform.position;
		float length = vec.length();

		if (length < minvec)
		{
			minvec = length;
			nearest_pop_area = pop_area;
		}
	});
	return nearest_pop_area.getNearestObstacle(target_);
}

void ar::ObstacleManager::isEnemysInObstacleArea()
{
	/*std::for_each(pop_areas.begin(), pop_areas.end(),
				  [&](ObstaclePopArea pop_area_)
	{
		std::for_each(enemy_holder->getEnemys().begin(), enemy_holder->getEnemys().end(),
					  [&](Enemy enemy)
		{
			if (sphereToSphere(pop_area_.transform.position, pop_area_.getPopRange(),
							   enemy.getWorldPoisition(), enemy.getCollisionCirclerad()))
			{
				enemy.inObstacleArea();
			}
		});
	});*/
}

bool ar::ObstacleManager::sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_)
{
	float x = (pos2_.x - pos1_.x) * (pos2_.x - pos1_.x);
	float y = (pos2_.y - pos1_.y) * (pos2_.y - pos1_.y);
	float z = (pos2_.z - pos1_.z) * (pos2_.z - pos1_.z);
	float total = x + y + z;

	float r = (radius1_ + radius2_) * (radius1_ + radius2_);
	return total <= r;
}

void ar::ObstacleManager::loadObstacleArea()
{
	std::ifstream ifstr(getAssetPath("StageInfo/ObstaclePoints.txt").string());

	if (!ifstr.is_open())
		assert(!"Obstacle text not find");

	while (!ifstr.eof())
	{
		Vec3f pos;
		float range;
		ifstr >> pos.x >> pos.y >> pos.z;
		ifstr >> range;
		pop_areas.push_back(ObstaclePopArea(pos, range, 1.0f, 1));
	}
}
