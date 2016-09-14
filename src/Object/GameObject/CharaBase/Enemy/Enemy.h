#pragma once
#include "../CharaBase.h"
#include "../../SignPost/SignPostManager.h"
#include "EnemyAI/EnemyAIBase.h"
#include "EnemyAI/EnemyAI.h"
#include "../Player/Player.h"
#include "cinder/TriMesh.h"
#include "../../Boss/Smoke/Smoke.h"


class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();
	void setup() override;
	void update() override;
	void draw() override;

	void transDraw()override;

	void setPlayer(std::shared_ptr<CharaBase>);
	void setTarget(const bool&);
	bool getTarget();


	bool isEnd();

	template<class T>
	void setAI();
	void inObstacleArea();

	void start();

	bool is_waiting;

private:
	void damage();
	std::shared_ptr<EnemyAIBase> ai;
	std::shared_ptr<CharaBase> player;
	bool is_hit;

	ci::TriMesh* mesh;

private: // êHÇÁÇ¡ÇΩéûÇÃââèo

	std::list<std::shared_ptr<Smokes>> smokes;
	void smokeSetup();
	void smokeUpdate();
	void smokeDraw();
	void smokePop();

	enum DamageType {
		NO_DAMAGE,
		ONE_STEP,
		TWO_STEP,
		THREE_STEP,
	};
	std::set<DamageType> damage_type;
	DamageType current_damage_type;

private:

	ci::gl::Material mt;

	int hit_count;
	bool is_hit_staging;
	bool staging_change;

	void hitStagingSetup();
	void hitStaging();
	ci::Vec3f shake_translate;
};

template<class T>
void Enemy::setAI()
{
	ai = std::make_shared<T>(T(static_cast<CharaBase*>(this), player.get()));
	ai->stert();
}
