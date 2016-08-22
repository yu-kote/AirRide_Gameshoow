#include "Enemy.h"

Enemy::Enemy()
{
	is_hit = false;
	
}

Enemy::~Enemy()
{


}



void Enemy::update()
{
	ai->update();


	move();
	damage();
	updateStageMatrix();
}

void Enemy::draw()
{
	ci::gl::popMatrices();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);

	ci::gl::multModelView(ci::Matrix44f::createRotation(transform.angle));


	ci::gl::drawColorCube(ci::Vec3f::zero(), ci::Vec3f::one());
	ci::gl::popMatrices();

	ci::gl::pushMatrices();

}



void Enemy::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player;
}

void Enemy::setTarget(const bool & _is_terget)
{
	ai->setTerget(_is_terget);
}

bool Enemy::isEnd()
{
	return ai->HP <= 0;
}

void Enemy::inObstacleArea()
{
	isRolling(transform.position.xy().inverse());

}

void Enemy::damage()
{

	if (player->isAttack()) {
		if (!isInvincible()) {
			if (player->transform.position.distanceSquared(
				transform.position) <
				(player->getCollisionCirclerad() + collision_circle_rad)
				*(player->getCollisionCirclerad() + collision_circle_rad)
				) {
				if (!is_hit)ai->HP--;
				is_hit = true;
				return;
			}
		}
	}
	is_hit = false;
}
