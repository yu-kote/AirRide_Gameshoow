#include "CharaBase.h"

ci::Vec3f QuadOut(float t, ci::Vec3f b, ci::Vec3f e) {
	return ci::Vec3f(-(e.x - b.x) * t * (t - 2) + b.x, 
		-(e.y - b.y) * t * (t - 2) + b.y, 
		-(e.z - b.z) * t * (t - 2) + b.z);
}

CharaBase::CharaBase()
{

}

CharaBase::~CharaBase()
{

}

void CharaBase::move()
{
	// Ž©•ª‚Å‘‚«‚Ü‚µ‚å‚¤

	/*if (end_move_pos != transform.position)
	{
		start_move_pos = transform.position;
	}

	transform.position = QuadOut(move_count, start_move_pos, end_move_pos);*/
}

void CharaBase::moveRollAxis()
{
	
}

void CharaBase::roll()
{
	if (status != CharaStatus::ROLL)
		return;

	roll_count += TIME.getDeltaTime();
	if (roll_count >= 1.0f)
	{
		roll_count = 1.0f;
		status = CharaStatus::NORMAL;
	}

	roll_angle = EasingFunction::QuadOut(roll_count, start_roll_angle, end_roll_angle);
}

void CharaBase::dash()
{
	if (status != CharaStatus::DASH)
		return;

	dash_count += TIME.getDeltaTime();
	if (dash_count >= 1.0f)
	{
		dash_count = 1.0f;
		status = CharaStatus::NORMAL;
	}

	speed = QuadOut(dash_count, start_dash_pos, end_dash_pos);
}

void CharaBase::collisionToWindow()
{
	if (transform.position.x < -window_size.x / 2.0f)
	{
		transform.position.x = -window_size.x / 2.0f;

		/*if (status == CharaStatus::ROLL)
			end_move_pos.x = -window_size.x / 2.0f;*/
	}
	if (transform.position.x > window_size.x / 2.0f)
	{
		transform.position.x = window_size.x / 2.0f;

		/*if (status == CharaStatus::ROLL)
			end_move_pos.x = window_size.x / 2.0f;*/
	}
	if (transform.position.y < -window_size.y / 2.0f)
	{
		transform.position.y = -window_size.y / 2.0f;

		/*if (status == CharaStatus::ROLL)
			end_move_pos.y = -window_size.y / 2.0f;*/
	}
	if (transform.position.y > window_size.y / 2.0f)
	{
		transform.position.y = window_size.y / 2.0f;

		/*if (status == CharaStatus::ROLL)
			end_move_pos.y = window_size.y / 2.0f;*/
	}
}

void CharaBase::updateStageMatrix()
{
	matrix = signpostmanager->getMatrix(transform.position);
}

void CharaBase::setup()
{
	transform.position = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.angle = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.scale = ci::Vec3f(1.0f, 1.0f, 1.0f);

	addComponent<ar::Color>();

	status = CharaStatus::NORMAL;
	speed = ci::Vec3f::zero();

	move_count = 0.0f;
	start_move_pos = ci::Vec3f::zero();
	end_move_pos = ci::Vec3f::zero();

	roll_angle = 0.0f;
	roll_count = 0.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;
	start_dash_pos = ci::Vec3f::zero();
	end_dash_pos = ci::Vec3f::zero();
}

void CharaBase::update()
{

}

void CharaBase::draw()
{

}
