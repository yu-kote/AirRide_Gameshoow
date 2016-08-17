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
	damage();

	
	end_move_pos = transform.position;
	move();
	/*roll();
	dash();
	*/updateStageMatrix();
}

void Enemy::draw()
{
	ci::gl::popMatrices();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);

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

void Enemy::damage()
{

	if (player->getStatus() == CharaStatus::DASH) {
		if (player->transform.position.distanceSquared(
			transform.position) < 1 * 1) {
			if (!is_hit)ai->HP--;
			is_hit = true;
			return;
		}
	}
	is_hit = false;
}
