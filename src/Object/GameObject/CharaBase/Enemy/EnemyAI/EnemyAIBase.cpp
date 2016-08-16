#include "EnemyAIBase.h"

void EnemyAIBase::setTerget(const bool & _is_terget)
{
	is_terget = _is_terget;
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

void EnemyAIBase::goPositon(ci::Vec3f _terget)
{
	ci::Vec2f _terget_vec = _terget.xy() - enemy->transform.position.xy();
	_terget_vec.normalize();
	enemy->transform.position.x += _terget_vec.x * 0.1f;
	enemy->transform.position.y += _terget_vec.y * 0.1f;

}
