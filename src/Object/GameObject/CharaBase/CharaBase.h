#pragma once
#include "../GameObject.h"
#include "../../Component/Components/Color.h"
#include "../../../Share/Easing/Easing.h"
#include "../../../Share/Time.h"
#include "../SignPost/SignPostManager.h"

enum class CharaStatus
{
	NORMAL,
	ROLL,
	DASH
};


class CharaBase : public ar::GameObject
{
public:

	CharaBase();
	~CharaBase();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;

	void setSignPostManager(std::shared_ptr<ar::SignPostManager> signpostmanager) { this->signpostmanager = signpostmanager; }
	ci::Matrix44f getMatrix() const { return matrix; }

	enum class RollDirection
	{
		LEFT,
		RIGHT
	};

	CharaStatus getStatus();
	ci::Vec3f getSpeed();


	void goToRolling(ci::Vec2f);
	void rolling(ci::Vec2f, RollDirection);
	void attack();


protected:

	void debugCourseOutStop();


	void move();

	// ç°ÇÃÇ∆Ç±ÇÎégÇÌÇ»Ç¢
	void moveRollAxis();

	void roll();
	void dash();
	void collisionToWindow();
	void updateStageMatrix();


	std::shared_ptr<ar::SignPostManager> signpostmanager;
	ci::Matrix44f matrix;

	ci::Vec3f window_size;

	CharaStatus status;
	ci::Vec3f speed;

	float move_count;
	ci::Vec3f start_move_pos;
	ci::Vec3f end_move_pos;

	ci::Quatf roll_quat;
	ci::Vec3f roll_quat_normal;
	const float max_roll_angle = M_PI * 2.0f * 4.0f;
	float roll_angle;
	float roll_count;
	float start_roll_angle;
	float end_roll_angle;

	ci::Vec2f move_direction;

	float dash_count;
	ci::Vec3f start_dash_pos;
	ci::Vec3f end_dash_pos;

private:


};


ci::Vec3f QuadOut(float t, ci::Vec3f b, ci::Vec3f e);