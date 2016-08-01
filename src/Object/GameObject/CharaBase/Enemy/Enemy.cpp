#include "Enemy.h"

Enemy::Enemy()
{


}

Enemy::~Enemy()
{


}

void Enemy::setup()
{
}

void Enemy::update()
{
	transform.position.z += 1;

}

void Enemy::draw()
{
	ci::gl::pushMatrices();
	signpostmanager->getMatrix(transform.position);
	ci::gl::drawColorCube(ci::Vec3f::zero(), ci::Vec3f::one());
	ci::gl::popMatrices();

}

void Enemy::setSignPostManager(std::shared_ptr<ar::SignPostManager> _spm)
{

	signpostmanager = _spm;
}
