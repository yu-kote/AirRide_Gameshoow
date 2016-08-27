#pragma once
#include "Obstacle.h"
#include "cinder/gl/Material.h"


namespace ar {
	class ObstaclePopArea : public ar::GameObject {
	public:

		// —N‚«ˆÊ’u ”ÍˆÍ ‹@—‹‚Ì”¼Œa ŒÂ”
		ObstaclePopArea(const ci::Vec3f& position_,
						float pop_range_,
						float radius_,
						int count_);
		ObstaclePopArea() {}

		void update()override;
		void draw()override;
		void transDraw()override;

		std::list<Obstacle> getObstacles() {
			return obstacles;
		}

		// ˆê”Ô‹ß‚¢áŠQ•¨‚ğ•Ô‚·
		Obstacle getNearestObstacle(ci::Vec3f target_);

		// “–‚½‚Á‚½‚©‚Ç‚¤‚©
		bool isHitObstacle(ci::Vec3f target_, float radius_);

		float getPopRange() {
			return pop_range;
		}

	private:

		std::list<Obstacle> obstacles;

		// —N‚«”ÍˆÍ’¼Œa
		float pop_range;

		void obstaclePop(float radius_, int count_);


	private:// ƒfƒoƒbƒO—p‚Ì”ÍˆÍ
		void testObstaclePopArea();
		ci::gl::Material test_mt;

	};
}