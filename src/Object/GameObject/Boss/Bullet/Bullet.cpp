#include "Bullet.h"
#include "../Boss.h"
#include "cinder/Rand.h"
#include "../../../../TaskManager/ObjDataManager.h"
#include "../../../../TaskManager/TextureManager.h"
#include "../../../GameObject/CharaBase/CharaBase.h"
#include "../../../../TaskManager/SoundManager.h"
#include "../../Camera/CameraPosition.h"

void Bullets::setup()
{
	bullets.push_back(Bullet(ci::Vec3f::zero()));
}

void Bullets::update()
{
	//‚Ì‚¿‚ÉŠÖ”‰»
	{
		if (boss->isPushBullet()) {
			ci::Vec2f direction = (ci::Matrix22f::createRotation(ci::randFloat(0, M_PI * 2))
								   *ci::Vec2f::xAxis())
				*ci::randFloat(4.f);
			ci::Vec3f add = boss->getMatrcx().
				transformVec(ci::Vec3f(direction.x, direction.y, 0));
			bullets.push_back(Bullet(
				boss->getWorldpos() + add
				));
		}
	}
	{
		for (auto& it : bullets) {
			it.update();
		}
	}
	{
		bullets.remove_if([&](Bullet& _b) { return _b.isErase(); });
	}
	{
		float dif;
		for (auto& it : bullets) {
			dif = player->getWorldPoisition().distanceSquared(
				it.transform.position);
			if (dif < 1.5 * 1.5) {
				player->HitObstacle(0.5f);
				it.bomb();
				CameraInfoGet.shakeCameraCall();
			}
		}
	}



}

void Bullets::draw()
{

	for (auto& it : bullets) {
		it.draw();
	}
}

void Bullets::setBoss(std::shared_ptr<Boss> _boss)
{
	boss = _boss.get();
}

void Bullets::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player.get();
}

void Bullets::setCameraPos(ci::Vec3f camera_pos_)
{
	for (auto& it : bullets) { it.setCameraPos(camera_pos_); }
}

Bullet::Bullet(ci::Vec3f _pos)
{
	bomb_count = 0;
	count = 60 * 3;
	transform.position = _pos;
	mesh = &ObjDataGet.find("obstacle");
	tex = TextureGet.find("Obstacle");

	mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
						  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
						  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
						  80.0f,                               // Shininess
						  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));	  // Emission

	is_bomb = false;
}

void Bullet::update()
{
	if (is_bomb)
	{
		if (bomb_count == 0)
		{
			particle.push_back(std::make_shared<ar::ParticleController>
							   (ar::ParticleController(transform.position)));
			SoundGet.find("Bomb")->start();
		}

		for (auto& it : particle) { it->update(); }

		bomb_count++;
	}
	count--;
}

void Bullet::draw()
{
	ci::gl::pushModelView();
	ci::gl::translate(transform.position);

	mt.apply();
	if (is_bomb == false)
	{
		ci::gl::scale(0.03f, 0.03f, 0.03f);
		tex->enableAndBind();
		ci::gl::draw(*mesh);
		tex->disable();
	}
	else
	{
		for (auto& it : particle) { it->draw(); }
	}


	ci::gl::popModelView();

}

bool Bullet::isErase()
{
	return count < 0;
}

void Bullet::bomb()
{
	is_bomb = true;
}

void Bullet::setCameraPos(ci::Vec3f camera_pos_)
{
	for (auto& it : particle) { it->setCameraPos(camera_pos_); }
}
