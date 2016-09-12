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

void CharaBase::init()
{
	addComponent<ar::Color>();

	window_size = ci::Vec3f(10.0f * 100.0f / 171.0f * 2.0f,
		10.0f * 100.0f / 171.0f * 2.0f,
		0.0f);

	transform.position = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.angle = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.scale = ci::Vec3f(1.0f, 1.0f, 1.0f);

	status = CharaStatus::NORMAL;
	speed = 1.0f;

	collision_circle_rad = 0.5f;

	move_count = 0.0f;
	move_count_takes_time = 1.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	max_roll_angle = (float)M_PI * 2.0f * 3.0f;
	roll_count = 1.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;
	start_speed = 3.0f;
	end_speed = 1.0f;

	clash_count = 1.0f;
	max_clash_count = 2.0f;
	clash_speed = 3.0f;
	start_clash_speed = 2.5f;
	end_clash_speed = 0.5f;

	interval_count = 1.0f;
	interval_takes_time = 2.0f;

	is_stop = false;
}

void CharaBase::restart()
{
	transform.position = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.angle = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.scale = ci::Vec3f(1.0f, 1.0f, 1.0f);

	status = CharaStatus::NORMAL;
	speed = 1.0f;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	roll_count = 1.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;

	clash_count = 1.0f;
	clash_speed = 3.0f;

	interval_count = 1.0f;

	is_stop = false;
}

void CharaBase::setup()
{
	init();
}

void CharaBase::update() {}

void CharaBase::draw() {}

ci::Vec3f CharaBase::getWorldPoisition()
{
	return matrix * ci::Vec3f::zero();
}

void CharaBase::moving(ci::Vec2f _terget)
{
	if (status != CharaStatus::NORMAL)
		return;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;
}

bool CharaBase::isRolling(ci::Vec2f _terget)
{
	if (status != CharaStatus::NORMAL)
		return false;

	status = CharaStatus::ROLL;
	move_count = 0.0f;
	roll_count = 0.0f;

	if (transform.position.x < _terget.x)
		end_roll_angle = -max_roll_angle;
	else if (transform.position.x > _terget.x)
		end_roll_angle = max_roll_angle;

	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = _terget;

	SoundGet.find("Role")->start();

	return true;
}

bool CharaBase::isAttacking()
{
	if (status != CharaStatus::NORMAL)
		return false;

	if (!isAction())
		return false;

	status = CharaStatus::DASH;
	dash_count = 0.0f;
	interval_count = 0.0f;

	// ƒ_ƒbƒVƒ…Žž‚É‰ñ‚é‚ç‚µ‚¢
	roll_count = 0.0f;
	end_roll_angle = -max_roll_angle;

	SoundGet.find("Dash")->start();

	return true;
}

void CharaBase::HitObstacle(const float &clash_speed)
{
	if (clash_count < 1.0f)
		return;

	status = CharaStatus::CLASH;
	speed = clash_speed;
	start_clash_speed = clash_speed;
	clash_count = 0.0f;
	start_move_pos = transform.position.xy();
	end_move_pos = transform.position.xy();
	move_count = 0.0f;
	roll_count = 1.0f;
	transform.angle.z = 0.0f;

	if (SoundGet.find("Dash")->isEnabled())
		SoundGet.find("Dash")->stop();
	if (SoundGet.find("Role")->isEnabled())
		SoundGet.find("Role")->stop();

	SoundGet.find("Damage")->start();
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
	if (is_stop == true)
		return;

	roll();
	dash();
	clash();
	interval();

	move_count += TIME.getDeltaTime() / move_count_takes_time;
	if (move_count >= 1.0f)
		move_count = 1.0f;

	ci::Vec2f move_pos = QuadOut(move_count, start_move_pos, end_move_pos);
	transform.position = ci::Vec3f(move_pos.x, move_pos.y, transform.position.z + speed);
}

void CharaBase::roll()
{
	if (roll_count == 1.0f)
		return;

	roll_count += TIME.getDeltaTime();
	if (roll_count >= 1.0f)
	{
		roll_count = 1.0f;
		transform.angle.z = 0.0f;
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

	clash_count += TIME.getDeltaTime() / max_clash_count;
	if (clash_count >= 1.0f)
	{
		clash_count = 1.0f;
		speed = end_speed;
		status = CharaStatus::NORMAL;
	}

	speed = QuadOut(clash_count, start_clash_speed, end_clash_speed);
	transform.angle.z = std::sin(clash_count * max_clash_count * (float)M_PI * 4.0f ) * ((float)M_PI / 4.0f);

	if (clash_count >= 1.0f)
		speed = end_speed;
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

void CharaBase::interval()
{
	if (interval_count >= 1.0f)
		return;

	interval_count += TIME.getDeltaTime() / interval_takes_time;
	if (interval_count >= 1.0f)
		interval_count = 1.0f;
}
