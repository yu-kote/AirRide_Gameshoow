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


	ci::Vec3f getWorldPoisition();

	void setSignPostManager(std::shared_ptr<ar::SignPostManager> signpostmanager) { this->signpostmanager = signpostmanager; }
	ci::Matrix44f getMatrix() const { return matrix; }

	enum class RollDirection
	{
		LEFT,
		RIGHT
	};

	CharaStatus getStatus();
	float getSpeed();


	void goToRolling(ci::Vec2f);

	void moving(ci::Vec2f);
	void rolling(ci::Vec2f, RollDirection);
	void attack();
	void moveDirection(ci::Vec2f, float);



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
	float speed;

	float move_count;
	ci::Vec2f start_move_pos;
	ci::Vec2f end_move_pos;

	ci::Quatf roll_quat;
	ci::Vec3f roll_quat_normal;
	float max_roll_angle;
	float roll_angle;
	float roll_count;
	float start_roll_angle;
	float end_roll_angle;

	ci::Vec2f move_direction;

	float dash_count;
	float start_dash_pos;
	float end_dash_pos;

private:


};


ci::Vec2f QuadOut(float t, ci::Vec3f b, ci::Vec3f e);
float QuadOut(float t, float b, float e);