#pragma once
#include "ObstaclePopArea.h"
#include "Obstacle.h"
#include "../GameObject.h"
//#include "../CharaBase/Player/Player.h"
//#include "../CharaBase/Enemy/EnemyHolder/EnemyHolder.h"

class Player;
class EnemyHolder;

namespace ar {
	class ObstacleManager : public GameObject {
	public:

		ObstacleManager();

		void setup()override;
		void update()override;
		void draw()override;
		void transDraw()override;


	private:
		std::list<ObstaclePopArea> pop_areas;


		void loadObstacleArea();

	public:
		ar::Obstacle getNearestObstacle(ci::Vec3f target_);

		void setPlayer(std::shared_ptr<Player> player_) { player = player_; }
		void setEnemyHolder(std::shared_ptr<EnemyHolder> enemy_holder_) { enemy_holder = enemy_holder_; }


		void isEnemysInObstacleArea();
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<EnemyHolder> enemy_holder;

		bool sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_);
	};
}