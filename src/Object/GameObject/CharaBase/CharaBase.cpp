#include "CharaBase.h"

ci::Vec2f QuadOut(float t, ci::Vec2f b, ci::Vec2f e) {
	return ci::Vec2f(-(e.x - b.x) * t * (t - 2) + b.x,
		-(e.y - b.y) * t * (t - 2) + b.y);
}

float QuadOut(float t, float b, float e){
	return -(e - b) * t * (t - 2) + b;
}

CharaBase::CharaBase()
{

}

CharaBase::~CharaBase()
{

}

void CharaBase::debugCourseOutStop()
{

	ci::Vec2f _pos = transform.position.xy();

	if (_pos.lengthSquared() < 6.f * 6.f)return;

	_pos.normalize();
	_pos *= 6.f;
	transform.position.x = _pos.x;
	transform.position.y = _pos.y;


}

void CharaBase::move()
{
	roll();
	dash();

	move_count += TIME.getDeltaTime();
	if (move_count >= 1.0f)
		move_count = 1.0f;

	// ‰¡ˆÚ“®
	ci::Vec2f move_pos = QuadOut(move_count, start_move_pos, end_move_pos);
	transform.position = ci::Vec3f(move_pos.x, move_pos.y, transform.position.z);

	// ZŽ²ˆÚ“®
	transform.position += speed;
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
		transform.position.x = -window_size.x / 2.0f;
	if (transform.position.x > window_size.x / 2.0f)
		transform.position.x = window_size.x / 2.0f;
	if (transform.position.y < -window_size.y / 2.0f)
		transform.position.y = -window_size.y / 2.0f;
	if (transform.position.y > window_size.y / 2.0f)
		transform.position.y = window_size.y / 2.0f;
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
	speed = 0.0f;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	max_roll_angle = (float)M_PI * 2.0f * 4.0f;
	roll_angle = 0.0f;
	roll_count = 0.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;
	start_dash_pos = 0.0f;
	end_dash_pos = 0.0f;
}

void CharaBase::update()
{

}

void CharaBase::draw()
{

}

ci::Vec3f CharaBase::getWorldPoisition()
{
	return matrix * ci::Vec3f::zero();
}

CharaStatus CharaBase::getStatus()
{
	return status;
}

float CharaBase::getSpeed()
{
	return speed;
}

void CharaBase::goToRolling(ci::Vec2f _terget)
{
	if (start_move_pos.x > _terget.x) {
		rolling(_terget, RollDirection::LEFT);
	}
	else
	{
		rolling(_terget, RollDirection::RIGHT);
	}

}

void CharaBase::moving(ci::Vec2f _terget)
{
	move_count = 0.0f;
	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;
}

void CharaBase::rolling(ci::Vec2f _terget, RollDirection roll_direction)
{
	status = CharaStatus::ROLL;
	roll_count = 0;

	if (roll_direction == RollDirection::LEFT)
		end_roll_angle = max_roll_angle;
	else if (roll_direction == RollDirection::RIGHT)
		end_roll_angle = -max_roll_angle;

	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;
}

void CharaBase::attack()
{
	status = CharaStatus::DASH;
	dash_count = 0;
}

void CharaBase::moveDirection(ci::Vec2f _direction, float _speed)
{
	if (_direction.lengthSquared() > 0) {
		_direction.normalize();
		_direction *= _speed;
		start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
		end_move_pos += _direction;
		move_count = 0.0f;

		move_direction = _direction;
	}
}
