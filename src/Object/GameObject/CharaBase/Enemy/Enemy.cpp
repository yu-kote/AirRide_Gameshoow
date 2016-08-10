#include "Enemy.h"

Enemy::Enemy()
{


}

Enemy::~Enemy()
{


}

void Enemy::setup()
{
	player->transform.position;
	ai = std::make_shared<AILevel1>(AILevel1(static_cast<CharaBase*>(this), player.get()));

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

void Enemy::setSignPostManager(std::shared_ptr<ar::SignPostManager> _spm)
{
	signpostmanager = _spm;
}

void Enemy::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player;
}
