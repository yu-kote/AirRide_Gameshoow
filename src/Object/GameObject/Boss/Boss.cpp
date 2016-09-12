#include "Boss.h"
#include "../../GameObject/CharaBase/CharaBase.h"
#include "../../GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../GameObject/SignPost/SignPostManager.h"
#include "../../../Share/Easing/Easing.h"
#include "../../../Share/Interface/Interface.h"

#include "../../Component/Components/Material.h"
#include "../../Component/Components/Texture.h"
#include "../../../TaskManager/ObjDataManager.h"

void Boss::setup()
{
	is_active = false;
	pushcount = 0;
	HP_max = 3;
	HP = HP_max;
	is_hit = false;

	difference = 22.f;
	maxspeed = 1.3f;
	minspeed = 0.5f;
	Params->addParam("Boss difference", &difference).group("BOSS");
	Params->addParam("Boss maxspeed", &maxspeed).step(0.1f).group("BOSS");
	Params->addParam("Boss minspeed", &minspeed).step(0.1f).group("BOSS");
	Params->addParam("Boss HP", &HP).group("BOSS");
	//Params->addParam("Boss minspeed", &minspeed).step(0.1f).group("BOSS");

	smokeSetup();

	//addComponent<ar::Material>(ar::Material(
	//	ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
	//					 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
	//					 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
	//					 80.0f,                               // Shininess
	//					 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission

	addComponent<ar::Texture>(ar::Texture("Boss"));

	damage_mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
								 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
								 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
								 80.0f,                               // Shininess
								 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
	alpha = 1.0f;

	normal_mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
								 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
								 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
								 80.0f,                               // Shininess
								 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));

	hit_mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
							  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
							  ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
							  80.0f,                               // Shininess
							  ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));

	hit_count = 0;
	is_hit_staging = false;
}

void Boss::update()
{
	if (!is_active) {
		entry();
		return;
	}
	damage();
	pushcount++;
	pushcount %= 60;
	keepDifference();
	matrix = signpostmanager->getMatrix(transform.position);

	smokeUpdate();
	hitStaging();
}

void Boss::draw()
{

}

void Boss::transDraw()
{
	if (!is_active)return;
	ci::gl::popModelView();
	ci::gl::pushModelView();
	ci::gl::enableAlphaBlending();

	ci::gl::multModelView(matrix);

	ci::gl::rotate(ci::Vec3f(0, 0, 180));
	ci::gl::scale(ci::Vec3f(0.035f, 0.035f, 0.035f));

	drawBegin();

	damage_mt.apply();

	ci::gl::draw(ObjDataGet.find("Boss"));

	ci::gl::disableAlphaBlending();
	drawEnd();

	ci::gl::popModelView();
	ci::gl::pushModelView();


	ci::gl::pushModelView();

	for (auto& it : smokes)
	{
		it->transDraw();
	}

	ci::gl::popModelView();
}

void Boss::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player.get();
}

void Boss::setEnemyHolder(std::shared_ptr<EnemyHolder> _eh)
{
	enemyholder = _eh.get();
}

void Boss::setSignPostManager(std::shared_ptr<ar::SignPostManager> _spm)
{
	signpostmanager = _spm.get();
}

void Boss::entry()
{
	if (is_active)return;
	if (!enemyholder->isEndLasstEnemy()) return;

	transform.position.z = player->transform.position.z + 100;

	is_active = true;
}


bool Boss::getIsExist() {
	return is_active;
}

bool Boss::isPushBullet()
{
	if (!is_active)return false;
	return pushcount == 0;

}

ci::Vec3f Boss::getWorldpos()
{
	return  matrix * ci::Vec3f::zero();
}

ci::Matrix44f Boss::getMatrcx()
{
	return matrix;
}

void Boss::damage()
{
	if (player->transform.position.z > transform.position.z) {
		if (is_hit) return;
		HP--;
		is_hit = true;
		hit_count = 0;
		is_hit_staging = true;
		return;
	}
	is_hit = false;

}

void Boss::keepDifference()
{
	float _difference = -player->transform.position.z + transform.position.z;

	if (_difference > difference) {
		transform.position.z += minspeed;
	}
	if (_difference < difference) {
		transform.position.z += maxspeed;
	}
}



void Boss::smokeSetup()
{
	current_damage_type = DamageType::NO_DAMAGE;
	damage_type.insert(current_damage_type);
}

void Boss::smokeUpdate()
{
	for (auto& it : smokes)
	{
		it->setCameraPos(camera_pos);
	}
	if (HP <= float(HP_max) * (2.0f / 3.0f))
		current_damage_type = DamageType::ONE_STEP;
	if (HP <= float(HP_max) * (1.0f / 3.0f))
		current_damage_type = DamageType::TWO_STEP;
	if (HP <= 0)
		current_damage_type = DamageType::THREE_STEP;

	if (damage_type.find(current_damage_type) == damage_type.end())
	{
		damage_type.clear();
		damage_type.insert(current_damage_type);

		smokePop();
		smokePop();
		smokePop();
		smokePop();

	}
	if (is_hit_staging == false)
	{
		if (current_damage_type == DamageType::TWO_STEP)
		{
			damage_mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
										 ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
										 ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
										 80.0f,                               // Shininess
										 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}
		if (current_damage_type == DamageType::THREE_STEP)
		{
			alpha -= 0.008;
			damage_mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Ambient
										 ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Diffuse
										 ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Specular
										 80.0f,                               // Shininess
										 ci::ColorA(0.5f, 0.5f, 0.5f, alpha));

			if (alpha <= 0)
				smokes.clear();
		}
	}


	for (auto& it : smokes)
	{
		it->setBossWorldPos(getWorldpos());
		it->update();
	}

}

void Boss::smokePop()
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> pop_rand(-3.5f / 2.f, 3.5f / 2.f);

	ci::Vec3f pop_pos = ci::Vec3f(pop_rand(mt), pop_rand(mt), pop_rand(mt));

	smokes.push_back(std::make_shared<Smokes>(Smokes(pop_pos)));
}

void Boss::hitStaging()
{
	if (is_hit_staging)
	{
		if (hit_count % 10 == 0)
		{
			staging_change = !staging_change;
		}
		if (staging_change)
		{
			damage_mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
										 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
										 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
										 80.0f,                               // Shininess
										 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else
		{
			damage_mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
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
	hit_count++;
}
