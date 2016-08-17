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
	transform.position = QuadOut(move_count, start_move_pos, end_move_pos);

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
	start_move_pos.z = transform.position.z;
	end_move_pos.z = transform.position.z;
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
	start_move_pos.z = transform.position.z;
	end_move_pos.z = transform.position.z;
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

ci::Vec3f CharaBase::getWorldPoisition()
{
	return matrix * ci::Vec3f::zero();
}

CharaStatus CharaBase::getStatus()
{
	return status;
}

ci::Vec3f CharaBase::getSpeed()
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
	start_move_pos = transform.position;
	end_move_pos = ci::Vec3f(_terget.x, _terget.y, transform.position.z);
}

void CharaBase::rolling(ci::Vec2f _terget, RollDirection roll_direction)
{
	status = CharaStatus::ROLL;
	roll_count = 0;

	if (roll_direction == RollDirection::LEFT)
		end_roll_angle = max_roll_angle;
	else if (roll_direction == RollDirection::RIGHT)
		end_roll_angle = -max_roll_angle;

	start_move_pos = transform.position;
	end_move_pos = ci::Vec3f(_terget.x, _terget.y, transform.position.z);
}

void CharaBase::attack()
{
	status = CharaStatus::DASH;
	dash_count = 0;
}

void CharaBase::moveDirection(ci::Vec2f _direction, float _speed)
{
	start_move_pos.z = transform.position.z;
	end_move_pos.z = transform.position.z;

	if (_direction.lengthSquared() > 0) {
		_direction.normalize();
		_direction *= _speed;
		start_move_pos = transform.position;
		end_move_pos += ci::Vec3f(_direction.x, _direction.y, 0.0f);
		move_count = 0.0f;

		move_direction = _direction;
	}

}
