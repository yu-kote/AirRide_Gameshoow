#pragma once
#include "../GameObject.h"
#include "../../Component/Components/Color.h"
#include "../../../Share/Easing/Easing.h"
#include "../../../Share/Time.h"
#include "../SignPost/SignPostManager.h"
#include "../Obstacle/ObstacleManager.h"

enum class CharaStatus
{
	NORMAL,
	ROLL,
	DASH,
	CLASH
};


class CharaBase : public ar::GameObject
{
public:

	CharaBase();
	~CharaBase();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;


	ci::Vec3f getWorldPoisition();

	void setSignPostManager(std::shared_ptr<ar::SignPostManager> signpostmanager) { this->signpostmanager = signpostmanager; }
	ci::Matrix44f getMatrix() const { return matrix; }

	CharaStatus getStatus() { return status; }
	float getSpeed() const { return speed; }
	void setSpeed(const float speed) {

		if (status != CharaStatus::NORMAL)
			return;

		float distance_speed = start_speed - end_speed;

		start_speed = speed + distance_speed;
		end_speed = speed;
		this->speed = speed;
	}

	float getCollisionCirclerad() const { return collision_circle_rad; }
	void setPosition(const ci::Vec2f &position) {

		if (status != CharaStatus::NORMAL)
			return;

		start_move_pos = position;
		end_move_pos = position;
		move_count = 0.0f;
	}

	void moving(ci::Vec2f);
	void rolling(ci::Vec2f);
	void attack();
	void moveDirection(ci::Vec2f, float);

	void HitObstacle();

protected:

	void debugCourseOutStop();

	void move();
	void roll();
	void dash();
	void collisionToWindow();
	void clash();
	void updateStageMatrix();


	std::shared_ptr<ar::SignPostManager> signpostmanager;
	ci::Matrix44f matrix;

	ci::Vec3f window_size;

	CharaStatus status;
	float speed;

	float collision_circle_rad;

	float move_count;
	ci::Vec2f start_move_pos;
	ci::Vec2f end_move_pos;

	ci::Quatf roll_quat;
	ci::Vec3f roll_quat_normal;
	float max_roll_angle;
	float roll_count;
	float start_roll_angle;
	float end_roll_angle;

	ci::Vec2f move_direction;

	float dash_count;
	float start_speed;
	float end_speed;

	float clash_count;
	float clash_speed;
	float start_clash_angle;
	float end_clash_angle;

private:

};


ci::Vec2f QuadOut(float t, ci::Vec2f b, ci::Vec2f e);
float QuadOut(float t, float b, float e);