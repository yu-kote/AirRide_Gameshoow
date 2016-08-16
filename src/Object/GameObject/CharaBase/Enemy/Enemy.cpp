#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{


}



void Enemy::update()
{
	ai->update();
	matrix = signpostmanager->getMatrix(transform.position);
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
