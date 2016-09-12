#pragma once
#include "../GameObject.h"
#include "Smoke/Smoke.h"
#include <set>
#include "cinder/gl/Material.h"

class CharaBase;
class EnemyHolder;
namespace ar {
	class SignPostManager;
}


class Boss : public ar::GameObject
{
public:
	void setup() override;
	void update()override;
	void draw()override;
	void transDraw() override;

	//É{ÉXÇ™èoÇƒÇ¢ÇÈÇ∆Ç´Ç…trueÇï‘ÇµÇ‹Ç∑
	bool getIsExist();

	void setPlayer(std::shared_ptr<CharaBase>);
	void setEnemyHolder(std::shared_ptr<EnemyHolder>);
	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);


	bool isPushBullet();
	ci::Vec3f getWorldpos();
	ci::Matrix44f getMatrcx();


	bool isDead() { return HP <= 0; }
	int getHp() { return HP; }
	int getMaxHp() { return HP_max; }

private:


	void damage();

	void keepDifference();
	void entry();



	EnemyHolder* enemyholder;
	ar::SignPostManager* signpostmanager;
	CharaBase* player;
	bool is_active;
	ci::Matrix44f matrix;

	int pushcount;

	int HP;
	int HP_max;
	int difference;
	float maxspeed;
	float minspeed;

	bool is_hit;


private:

	std::list<std::shared_ptr<Smokes>> smokes;

	void smokeSetup();
	void smokeUpdate();
	void smokePop();

	enum DamageType {
		NO_DAMAGE,
		ONE_STEP,
		TWO_STEP,
		THREE_STEP,
	};
	std::set<DamageType> damage_type;
	DamageType current_damage_type;
	ci::Vec3f camera_pos;
public:

	void setCameraPos(ci::Vec3f camera_pos_) {
		camera_pos = camera_pos_;
	}

private:

	ci::gl::Material normal_mt;
	ci::gl::Material hit_mt;
	ci::gl::Material damage_mt;
	float alpha;
	int hit_count;
	bool is_hit_staging;
	bool staging_change = false;

	void hitStaging();

};



