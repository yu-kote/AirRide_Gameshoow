#include "EnemyAIBase.h"

void EnemyAIBase::setTerget(const bool & _is_terget)
{
	is_terget = _is_terget;
}

bool EnemyAIBase::getTerget()
{
	return is_terget;
}

void EnemyAIBase::outStop()
{
	enemy->transform.position.x = std::min(std::max(enemy->transform.position.x, -7.f), 7.f);
	enemy->transform.position.y = std::min(std::max(enemy->transform.position.y, -7.f), 7.f);

}

void EnemyAIBase::runPositon(ci::Vec3f _terget, float _r)
{
	ci::Vec2f _terget_vec = _terget.xy() - enemy->transform.position.xy();
	if (_terget_vec.lengthSquared() < _r * _r) {

		enemy->transform.position.xy();

	}
}

void EnemyAIBase::goPositon(ci::Vec3f _terget, float _speed)
{
	ci::Vec2f _terget_vec = _terget.xy() - enemy->transform.position.xy();
	_terget_vec.normalize();
	enemy->transform.position.x += _terget_vec.x * _speed;
	enemy->transform.position.y += _terget_vec.y * _speed;

}

void EnemyAIBase::tergetMotion(int _add_count)
{
	terget_change_count++;
	if (terget_change_count > _add_count
		&& aiterget.distanceSquared(enemy->transform.position.xy()) < 1) {
		terget_change_count = 0;
		changeTarget();

	}
}

void EnemyAIBase::changeTarget()
{
	aiterget = (ci::Matrix22f::createRotation(ci::randFloat(0, M_PI * 2))
		*ci::Vec2f::xAxis())
		*ci::randFloat(6.5);

}

void EnemyAIBase::tergetMove()
{
	float difference = enemy->transform.position.z - player->transform.position.z;
	if (difference > 15.f) {
		enemy->setSpeed(0.8f);
		return;
	}
	if (difference < 15.f
		&& HP > 0) {
		enemy->setSpeed(1.6f);
		return;
	}
}

bool EnemyAIBase::avoidPlayerDashByRoll()
{
	float difference = enemy->transform.position.z - player->transform.position.z;
	if (difference > 9)return false;
	if (player->isAttack()) {
		if (hit2d()) {
			enemy->setSpeed(1.6f);
			return enemy->isRolling(-enemy->transform.position.xy());

		}
	}

	return false;
}

bool EnemyAIBase::avoidPlayerDashByDash()
{
	float difference = enemy->transform.position.z - player->transform.position.z;
	if (difference > 9)return false;
	if (player->isAttack()) {
		if (hit2d()) {
			enemy->setSpeed(1);
			return enemy->isAttacking();
		}
	}


	return false;
}

bool EnemyAIBase::hit2d()
{


	return player->transform.position.xy().distanceSquared
		(enemy->transform.position.xy()) <
		(player->getCollisionCirclerad() + enemy->getCollisionCirclerad()) *
		(player->getCollisionCirclerad() + enemy->getCollisionCirclerad());
}
