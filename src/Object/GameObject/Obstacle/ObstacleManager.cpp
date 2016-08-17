#include "ObstacleManager.h"
#include "../GameObjectEntities.h"

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
}

void ar::ObstacleManager::draw()
{
	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [](ObstaclePopArea pop_areas_) {pop_areas_.draw(); });

	gl::pushModelView();
	gl::multModelView(signpostmanager->getMatrix(signpostmanager->getStagePos(
		pop_areas.begin()->transform.position)));

	gl::drawSphere(Vec3f::zero(), 1, 12);

	gl::popModelView();
}

void ar::ObstacleManager::transDraw()
{
	std::for_each(pop_areas.begin(), pop_areas.end(),
				  [](ObstaclePopArea pop_areas_) {pop_areas_.transDraw(); });
}

void ar::ObstacleManager::setSignpostManager(std::shared_ptr<ar::SignPostManager> signpostmanager_)
{
	signpostmanager = signpostmanager_;
}

ci::Vec3f ar::ObstacleManager::getNearObstacle(ci::Vec3f target_)
{
	return Vec3f::zero();
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
