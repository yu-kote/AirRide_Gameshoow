#include "CharaBase.h"

ci::Vec2f QuadOut(float t, ci::Vec2f b, ci::Vec2f e) {
	return ci::Vec2f(-(e.x - b.x) * t * (t - 2) + b.x,
		-(e.y - b.y) * t * (t - 2) + b.y);
}

float QuadOut(float t, float b, float e) {
	return -(e - b) * t * (t - 2) + b;
}

CharaBase::CharaBase() {}

CharaBase::~CharaBase() {}

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
	clash();

	move_count += TIME.getDeltaTime();
	if (move_count >= 1.0f)
		move_count = 1.0f;

	ci::Vec2f move_pos = QuadOut(move_count, start_move_pos, end_move_pos);
	transform.position = ci::Vec3f(move_pos.x, move_pos.y, transform.position.z + speed);
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

	transform.angle.z = EasingFunction::QuadOut(roll_count, start_roll_angle, end_roll_angle);
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

	speed = QuadOut(dash_count, start_speed, end_speed);
}

void CharaBase::clash()
{
	if (status != CharaStatus::CLASH)
		return;

	clash_count += TIME.getDeltaTime();
	if (clash_count >= 1.0f)
	{
		clash_count = 1.0f;
		status = CharaStatus::NORMAL;
	}

	//transform.angle.z = std::sin(clash_count / 2.0f * M_PI * 4.0f ) * ((float)M_PI / 4.0f);
	transform.angle.z = clash_count;
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
	speed = 1.0f;

	collision_circle_rad = 1.0f;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	max_roll_angle = (float)M_PI * 2.0f * 4.0f;
	roll_count = 0.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;
	start_speed = 3.0f;
	end_speed = 1.0f;

	clash_count = 0.0f;
	clash_speed = 0.2f;
}

void CharaBase::update() {}

void CharaBase::draw() {}

ci::Vec3f CharaBase::getWorldPoisition()
{
	return matrix * ci::Vec3f::zero();
}

void CharaBase::moving(ci::Vec2f _terget)
{
	move_count = 0.0f;
	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;
}

void CharaBase::rolling(ci::Vec2f _terget)
{
	if (status != CharaStatus::NORMAL)
		return;

	status = CharaStatus::ROLL;
	move_count = 0.0f;
	roll_count = 0.0f;

	if (transform.position.x < _terget.x)
		end_roll_angle = max_roll_angle;
	else if (transform.position.x > _terget.x)
		end_roll_angle = -max_roll_angle;

	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;
}

void CharaBase::attack()
{
	if (status != CharaStatus::NORMAL)
		return;

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

void CharaBase::HitObstacle()
{
	status = CharaStatus::CLASH;
	speed = clash_speed;
	clash_count = 0.0f;
}