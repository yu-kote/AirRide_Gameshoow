#pragma once
#include "cinder/app/AppNative.h"
#include "../../GameObject.h"


class Smoke : public ar::GameObject {
public:

	Smoke(ci::Vec3f pop_pos_);

	void setup()override final;
	void update()override final;
	void transDraw()override final;

	bool isErase();
	void setCameraPos(ci::Vec3f camera_pos_) { camera_pos = camera_pos_; }

private:

	float speed;
	float rotate_speed;

	int erase_count;
	int count;
	ci::Vec3f vec;

	ci::Vec3f camera_pos;
	ci::Quatf rotate;

};



class Smokes : public ar::GameObject {
public:

	Smokes(ci::Vec3f pop_pos_);

	void setup()override final;
	void update()override final;
	void transDraw()override final;

	void setBossWorldPos(ci::Vec3f boss_pos_);

	void setCameraPos(ci::Vec3f camera_pos_) {
		for (auto& it : smokes)
		{
			it->setCameraPos(camera_pos_);
		}
	}

	ci::Vec3f rand_value;

private:
	std::list<std::shared_ptr<Smoke>> smokes;

	int count;


};