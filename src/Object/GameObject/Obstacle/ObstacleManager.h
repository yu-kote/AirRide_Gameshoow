#pragma once
#include "ObstaclePopArea.h"
#include "../GameObject.h"
#include "../SignPost/SignPostManager.h"


namespace ar {
	class ObstacleManager : public GameObject {
	public:

		ObstacleManager();

		void setup()override;
		void update()override;
		void draw()override;
		void transDraw()override;

		void setSignpostManager(std::shared_ptr<ar::SignPostManager> signpostmanager_);

		ci::Vec3f getNearObstacle(ci::Vec3f target_);

	private:

		std::list<ObstaclePopArea> pop_areas;

		std::shared_ptr<SignPostManager> signpostmanager;

		void loadObstacleArea();

	};
}