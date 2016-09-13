#include "Enemy.h"
#include "../../../Component/Components/Material.h"
#include "../../../Component/Components/Texture.h"
#include "cinder/gl/Material.h"


Enemy::Enemy()
{
	is_hit = false;
	mesh = &ObjDataGet.find("Enemy");
}

Enemy::~Enemy()
{


}

void Enemy::setup()
{
	init();

	collision_circle_rad = 1.2f;

	addComponent<ar::Texture>(ar::Texture("Enemy"));
	mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
						  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
						  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
						  80.0f,                               // Shininess
						  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
	smokeSetup();
	hitStagingSetup();
}



void Enemy::update()
{
	ai->update();

	move();
	damage();
	updateStageMatrix();
	smokeUpdate();
	hitStaging();
}

void Enemy::draw()
{
	ci::gl::popMatrices();

	drawBegin();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);

	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(transform.angle);
	ci::gl::multModelView(mrotate);
	ci::gl::scale(0.07f, 0.07f, 0.07f);
	mt.apply();
	ci::gl::draw(*mesh);

	ci::gl::popMatrices();

	drawEnd();

	ci::gl::pushMatrices();

}

void Enemy::transDraw()
{
	smokeDraw();
}



void Enemy::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player;
}

void Enemy::setTarget(const bool & _is_terget)
{
	ai->setTerget(_is_terget);
}

bool Enemy::getTarget()
{
	return ai->getTerget();
}

bool Enemy::isEnd()
{
	return ai->HP <= 0;
}

void Enemy::inObstacleArea()
{
	//isRolling(transform.position.xy().inverse());
}

void Enemy::start()
{
	ai->go();
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
				if (!is_hit) {
					ai->HP--;
					HitObstacle(2.5f);
					is_hit_staging = true;
					hit_count = 0;
				}
				is_hit = true;
				return;
			}
		}
	}
	is_hit = false;
}














































void Enemy::smokeSetup()
{
	current_damage_type = DamageType::NO_DAMAGE;
	damage_type.insert(current_damage_type);
}

void Enemy::smokeUpdate()
{
	if (isEnd())
		current_damage_type = DamageType::ONE_STEP;

	if (damage_type.find(current_damage_type) == damage_type.end())
	{
		damage_type.clear();
		damage_type.insert(current_damage_type);

		smokePop();
		smokePop();
		smokePop();
		smokePop();

	}

	for (auto& it : smokes)
	{
		it->setBossWorldPos(getWorldPoisition());
		it->update();
	}
}

void Enemy::smokeDraw()
{
	ci::gl::pushModelView();

	for (auto& it : smokes)
	{
		it->transDraw();
	}

	ci::gl::popModelView();
}

void Enemy::smokePop()
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> pop_rand(-0.5f, 0.5f);

	ci::Vec3f pop_pos = ci::Vec3f(pop_rand(mt), pop_rand(mt), pop_rand(mt));

	smokes.push_back(std::make_shared<Smokes>(Smokes(pop_pos)));
}

void Enemy::hitStagingSetup()
{
	hit_count = 0;
	is_hit_staging = false;
	staging_change = false;
}

void Enemy::hitStaging()
{
	if (is_hit_staging)
	{
		if (hit_count % 10 == 0)
		{
			staging_change = !staging_change;
		}
		if (staging_change)
		{
			mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
								  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
								  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
								  80.0f,                               // Shininess
								  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else
		{
			mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
								  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
								  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
								  80.0f,                               // Shininess
								  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}

		if (hit_count >= 60)
		{
			is_hit_staging = false;
		}
	}
	else
	{
		if (isEnd())
		{
			mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
								  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
								  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
								  80.0f,                               // Shininess
								  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}
	hit_count++;
}
